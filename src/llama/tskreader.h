#pragma once

#include <map>
#include <memory>
#include <stack>
#include <vector>

#include <tsk/libtsk.h>

#include "direntstack.h"
#include "filerecord.h"
#include "hex.h"
#include "inodeandblocktracker.h"
#include "inodeandblocktrackerimpl.h"
#include "inputhandler.h"
#include "inputreader.h"
#include "outputhandler.h"
#include "recordhasher.h"
#include "tsk.h"
#include "tskimgassembler.h"
#include "tskreaderhelper.h"
#include "tsktimestamps.h"
#include "util.h"

class BlockSequence;

template <class Provider>
class TskReader: public InputReader {
public:
  TskReader(const std::string& imgPath):
    ImgPath(imgPath),
    Img(nullptr, nullptr),
    Input(),
    Output(),
    Tsk(),
    Asm(),
    Tsg(nullptr),
    Tracker(new InodeAndBlockTrackerImpl()),
    RecHasher(),
    Dirents(RecHasher)
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
    Asm.addImage(Tsk.convertImg(*Img));

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
      // wrap up the walk
      while (!Dirents.empty()) {
        Output->outputDirent(Dirents.pop());
      }

      Output->outputImage(Asm.dump());

      // teardown
      Input->flush();
    }
    return ret;
  }

private:
  // callbacks
  TSK_FILTER_ENUM filterVs(const TSK_VS_INFO* vs_info) {
    Asm.addVolumeSystem(Tsk.convertVS(*vs_info));
    return TSK_FILTER_CONT;
  }

  TSK_FILTER_ENUM filterVol(const TSK_VS_PART_INFO* vs_part) {
    Asm.addVolume(Tsk.convertVol(*vs_part));
    return TSK_FILTER_CONT;
  }

  TSK_FILTER_ENUM filterFs(TSK_FS_INFO* fs_info) {
    Asm.addFileSystem(Tsk.convertFS(*fs_info));
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

  bool addToBatch(TSK_FS_FILE* fs_file) {
    if (!fs_file || !fs_file->meta) {
      // TODO: Can we have a nonull fs_file->name in this case?
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
      const TSK_INUM_T par_addr =  fs_file->name->par_addr;

      while (!Dirents.empty() && par_addr != Dirents.top()["meta_addr"]) {
        Output->outputDirent(Dirents.pop());
      }

      std::cerr << par_addr << " -> " << fs_file->meta->addr << '\n';
      Dirents.push(fs_file->name->name, Tsk.convertName(*fs_file->name));
    }

    //
    // handle the meta
    //
    jsoncons::json jmeta = Tsk.convertMeta(meta, *Tsg);

    //
    // handle the attrs
    //

    Tsk.populateAttrs(fs_file);

    TskReaderHelper::handleAttrs(
      meta, CurFsOffset, CurFsBlockSize, inum, Tsk, *Tracker, jmeta["attrs"]
    );

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
  TskImgAssembler Asm;
  std::unique_ptr<TimestampGetter> Tsg;
  std::unique_ptr<InodeAndBlockTracker> Tracker;

  RecordHasher RecHasher;
  DirentStack Dirents;

  uint64_t CurFsOffset;
  uint64_t CurFsBlockSize;
};
