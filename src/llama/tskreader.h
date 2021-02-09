#pragma once

#include <map>
#include <memory>
#include <stack>
#include <vector>

#include <tsk/libtsk.h>

#include "filerecord.h"
#include "inodeandblocktracker.h"
#include "inodeandblocktrackerimpl.h"
#include "inputhandler.h"
#include "inputreader.h"
#include "outputhandler.h"
#include "tsk.h"
#include "tskimgassembler.h"
#include "util.h"

class BlockSequence;
class TimestampGetter;

template <class Provider>
class TskReader: public InputReader {
public:
  TskReader(const std::string& imgPath):
    ImgPath(imgPath),
    Img(nullptr, nullptr),
    Input(),
    Output(),
    Tsk(),
    Ass(),
    Tsg(nullptr),
    Tracker(new InodeAndBlockTrackerImpl())
  {
  }

  virtual ~TskReader() {}

  bool open() {
    return bool(Img = Tsk.openImg(ImgPath.c_str()));
  }

  virtual void setInputHandler(std::shared_ptr<InputHandler> in) override {
    Input = in;
  }

  virtual void setOutputHandler(std::shared_ptr<OutputHandler> out) override {
    Output = out;
  }

  virtual bool startReading() override {
    Ass.addImage(Tsk.convertImg(*Img));

    // tell TskAuto to start giving files to processFile
    // std::cerr << "Image is " << getImageSize() << " bytes in size" << std::endl;

    const bool ret = Tsk.walk(
      Img.get(),
      [this](const TSK_VS_INFO* vs_info) { return filterVs(vs_info); },
      [this](const TSK_VS_PART_INFO* vs_part) { return filterVol(vs_part); },
      [this](TSK_FS_INFO* fs_info) { return filterFs(fs_info); },
      [this](TSK_FS_FILE* fs_file, const char* path) { return processFile(fs_file, path); }
    );

    if (ret) {
      while (!Path.empty()) {
        std::cerr << Path.top() << " done\n";
        Path.pop();
      }

      Output->outputImage(Ass.dump());

      // teardown
      Input->flush();
    }
    return ret;
  }

private:
  // callbacks
  TSK_FILTER_ENUM filterVs(const TSK_VS_INFO* vs_info) {
    Ass.addVolumeSystem(Tsk.convertVS(*vs_info));
    return TSK_FILTER_CONT;
  }

  TSK_FILTER_ENUM filterVol(const TSK_VS_PART_INFO* vs_part) {
    Ass.addVolume(Tsk.convertVol(*vs_part));
    return TSK_FILTER_CONT;
  }

  TSK_FILTER_ENUM filterFs(TSK_FS_INFO* fs_info) {
    Ass.addFileSystem(Tsk.convertFS(*fs_info));
    Tsg = Tsk.makeTimestampGetter(fs_info->ftype);
    Tracker->setInodeRange(fs_info->first_inum, fs_info->last_inum + 1);
    Tracker->setBlockRange(fs_info->first_block * fs_info->block_size, (fs_info->last_block + 1) * fs_info->block_size);
    CurFsOffset = fs_info->offset;
    CurFsBlockSize = fs_info->block_size;
    return TSK_FILTER_CONT;
  }

  TSK_RETVAL_ENUM processFile(TSK_FS_FILE* fs_file, const char* /* path */) {
    // std::cerr << "processFile " << path << "/" << fs_file->name->name << std::endl;
    addToBatch(fs_file);
    return TSK_OK;
  }

  void markAllocatedRun(uint64_t inum, uint64_t begin, uint64_t end) {
    Tracker->markBlocksAllocated(begin, end);
  }

  void markDeletedRun(uint64_t inum, uint64_t begin, uint64_t end) {
    Tracker->markBlocksClaimed(inum, begin, end);
  }

  void handleRuns(
    const TSK_FS_ATTR& a,
    uint64_t fsOffset,
    uint64_t blockSize,
    uint64_t inum,
    void (TskReader::*markDataRun)(uint64_t inum, uint64_t begin, uint64_t end),
    jsoncons::json& jnrd_runs)
  {
    uint64_t skipBytes = a.nrd.skiplen;
    const uint64_t mainSize = (a.flags & TSK_FS_ATTR_COMP) ? a.nrd.allocsize: a.nrd.initsize;

    uint64_t fileOffset = 0;
    uint64_t slackOffset = 0;

    for (auto r = a.nrd.run; r; r = r->next) {
      if (r->flags == TSK_FS_ATTR_RUN_FLAG_FILLER) {
        // TODO: check on the exact semantics of this flag
        continue;
      }

      jnrd_runs.push_back(Tsk.convertRun(*r));

      // Determine absolute offsets for the run
      uint64_t beg = fsOffset + r->addr * blockSize;
      const uint64_t runEnd = beg + r->len * blockSize;
      uint64_t end = runEnd;

      // Ensure that we've advanced past the initial skip.

      // The TSK structs are capable of representing an intial skip
      // which could exceed the length of one or more runs. Can that
      // ever happen? No idea.
      if (skipBytes > 0) {
        const uint64_t toSkip = std::min(end - beg, skipBytes);
        beg += toSkip;
        skipBytes -= toSkip;
      }

      if (beg < end) {
        // we've reached data
        bool trueSlack = false;
        uint64_t bytesRemaining = mainSize - fileOffset;
        if (beg + bytesRemaining < end) {
          // end is the start of true slack
          end = beg + bytesRemaining;
          trueSlack = true;
        }

        if (beg < end) {
          if (r->flags == TSK_FS_ATTR_RUN_FLAG_NONE) {
            // just normal data; sparse blocks will be made available
            // as unallocated (FIXME: still true?)
            (this->*markDataRun)(inum, beg, end);
          }
          // advance offset (even if data run is sparse)
          fileOffset += (end - beg);
        }

        if (trueSlack) {
          // mark slack at end of allocated space
          if (r->flags == TSK_FS_ATTR_RUN_FLAG_NONE) {
            // but only if not sparse (sparse slack is a thing!)

            // TODO: We're not marking slack right now because we
            // don't know what should claim it.
          }
          slackOffset += (runEnd - end);
        }
      }

      if (r == a.nrd.run_end) {
        // This is hopefully unnecessary, but what if
        // r->nrd.run_end.next isn't null?
        // paranoia is a feature
        // FIXME: Maybe we should throw here instead?
        break;
      }
    }
  }

  void handleAttrs(
    const TSK_FS_META& meta,
    uint64_t fsOffset,
    uint64_t blockSize,
    uint64_t inum,
    jsoncons::json& jattrs)
  {
    const bool deleted = meta.flags & TSK_FS_META_FLAG_UNALLOC;
    const auto markDataRun = deleted ? &TskReader::markDeletedRun
                                     : &TskReader::markAllocatedRun;

    for (const TSK_FS_ATTR* a = meta.attr->head; a; a = a->next) {
      if (!(a->flags & TSK_FS_ATTR_INUSE)) {
        // This is an artifact of TSK's data structures, not a real run.
        continue;
      }

      jsoncons::json jattr = Tsk.convertAttr(*a);

      if (a->flags & TSK_FS_ATTR_NONRES) {
        handleRuns(*a, fsOffset, blockSize, inum, markDataRun, jattr["nrd_runs"]);
      }

      jattrs.push_back(std::move(jattr));
    }
  }

  bool addToBatch(TSK_FS_FILE* fs_file) {
    if (!fs_file || !fs_file->meta) {
      // nothing to process
      return false;
    }

    const TSK_FS_META& meta = *fs_file->meta;

    const uint64_t inum = meta.addr;
    if (Tracker->markInodeSeen(inum)) {
      // been here, done that
      return false;
    }

    //
    // handle the name
    //
    if (fs_file->name) {
      while (!Path.empty() && fs_file->name->par_addr != Path.top()) {
        std::cerr << Path.top() << " done\n";
        Path.pop();
      }
      Path.push(inum);

      std::cerr << fs_file->name->par_addr << " -> " << Path.top() << '\n';

      Output->outputDirent(Tsk.convertName(*fs_file->name));
    }

    //
    // handle the meta
    //
    jsoncons::json jmeta = Tsk.convertMeta(meta, *Tsg);

    //
    // handle the attrs
    //
    jsoncons::json& jattrs = jmeta["attrs"];

    // ridiculous bullshit to force attrs to be populated
    Tsk.populateAttrs(fs_file);

    if (meta.attr) {
      handleAttrs(meta, CurFsOffset, CurFsBlockSize, inum, jattrs);
    }

    Input->push({std::move(jmeta), makeBlockSequence(fs_file)});

    return true;
  }

  std::shared_ptr<BlockSequence> makeBlockSequence(TSK_FS_FILE* fs_file) {
    TSK_FS_INFO* their_fs = fs_file->fs_info;

    // open our own copy of the fs, since TskAuto closes the ones it opens
    auto [i, absent] = Fs.try_emplace(their_fs->offset, nullptr, nullptr);
    if (absent) {
      i->second = Tsk.openFS(
        Img.get(), their_fs->offset, their_fs->ftype
      );
    }

    TSK_FS_INFO* our_fs = i->second.get();

    // open our own copy of the file, since TskAuto closes the ones it opens
    return std::static_pointer_cast<BlockSequence>(
      std::make_shared<TskBlockSequence>(
        Tsk.openFile(our_fs, fs_file->meta->addr)
      )
    );
  }

  std::string ImgPath;
  std::unique_ptr<TSK_IMG_INFO, void(*)(TSK_IMG_INFO*)> Img;
  std::map<TSK_OFF_T, std::unique_ptr<TSK_FS_INFO, void(*)(TSK_FS_INFO*)>> Fs;

  std::shared_ptr<InputHandler> Input;
  std::shared_ptr<OutputHandler> Output;

  Provider Tsk;
  TskImgAssembler Ass;
  std::unique_ptr<TimestampGetter> Tsg;
  std::unique_ptr<InodeAndBlockTracker> Tracker;

  std::stack<TSK_INUM_T> Path;

  uint64_t CurFsOffset;
  uint64_t CurFsBlockSize;
};
