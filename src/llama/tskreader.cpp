#include "tskreader.h"

#include "filerecord.h"
#include "inputhandler.h"
#include "llamatskauto.h"
#include "outputhandler.h"
#include "tskwalkerimpl.h"
#include "util.h"

TskReader::TskReader(const std::string& imgName):
  ImgName(imgName),
  Img(nullptr, nullptr),
  Input(),
  Output(),
  LastFS(nullptr),
  Wrapper(new TskWrapper()),
  Ass(),
  Tsg(TskUtils::makeTimestampGetter(TSK_FS_TYPE_DETECT)),
  Walker(new TskWalkerImpl())
{
}

bool TskReader::open() {
  return bool(Img = Wrapper->openImg(ImgName.c_str()));
}

void TskReader::setInputHandler(std::shared_ptr<InputHandler> in) {
  Input = in;
}

void TskReader::setOutputHandler(std::shared_ptr<OutputHandler> out) {
  Output = out;
}

bool TskReader::startReading() {
  Ass.addImage(TskUtils::convertImg(*Img));

  // tell TskAuto to start giving files to processFile
  // std::cerr << "Image is " << getImageSize() << " bytes in size" << std::endl;

  const bool ret = Walker->walk(
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

TSK_FILTER_ENUM TskReader::filterVs(const TSK_VS_INFO* vs_info) {
  Ass.addVolumeSystem(TskUtils::convertVS(*vs_info));
  return TSK_FILTER_CONT;
}

TSK_FILTER_ENUM TskReader::filterVol(const TSK_VS_PART_INFO* vs_part) {
  Ass.addVolume(TskUtils::convertVol(*vs_part));
  return TSK_FILTER_CONT;
}

TSK_FILTER_ENUM TskReader::filterFs(TSK_FS_INFO* fs_info) {
  Ass.addFileSystem(TskUtils::convertFS(*fs_info));
  Tsg = TskUtils::makeTimestampGetter(fs_info->ftype);
  return TSK_FILTER_CONT;
}

TSK_RETVAL_ENUM TskReader::processFile(TSK_FS_FILE* fs_file, const char* /* path*/) {
  // std::cerr << "processFile " << path << "/" << fs_file->name->name << std::endl;
  if (fs_file->fs_info != LastFS) {
    LastFS = fs_file->fs_info;
    setInodeRange(LastFS->first_inum, LastFS->last_inum);
  }
  addToBatch(fs_file);
  return TSK_OK;
}

void TskReader::setBlockRange(uint64_t begin, uint64_t end) {
// FIXME: unclear if we can rely on end - begin + 1 to be the actual count
  BlockBegin = begin;
  BlockEnd = end;
  Allocated.clear();
  Allocated.resize(end+1);
}

void TskReader::setInodeRange(uint64_t begin, uint64_t end) {
  InumBegin = begin;
  InumEnd = end;
// FIXME: Apparently "first_inum" is first in some way other than the usual
// meaning of first, because it's 2 on DadeMurphy but we still see inode 0
// there. WTF? For the time being, just waste a few bits at the start of the
// encountered vector.
//  InodeEncountered.resize(end - begin);

  InodeEncountered.clear();
  InodeEncountered.resize(end+1);
}

bool TskReader::markInodeSeen(uint64_t inum) {
  // TODO: bounds checking? inum could be bogus
  if (InodeEncountered[inum]) {
    return true;
  }
  else {
    InodeEncountered[inum] = true;
    return false;
  }
}

void dummy_del(TSK_FS_INFO*) {}

std::shared_ptr<BlockSequence> TskReader::makeBlockSequence(TSK_FS_FILE* fs_file) {
  TSK_FS_INFO* their_fs = fs_file->fs_info;

  // open our own copy of the fs, since TskAuto closes the ones it opens
  auto p = Fs.emplace(their_fs->offset, make_unique_del(nullptr, dummy_del));
  if (p.second) {
    p.first->second = Wrapper->openFS(
      Img.get(), their_fs->offset, their_fs->ftype
    );
  }

  TSK_FS_INFO* our_fs = p.first->second.get();

  // open our own copy of the file, since TskAuto closes the ones it opens
  return std::static_pointer_cast<BlockSequence>(
    std::make_shared<TskBlockSequence>(
      Wrapper->openFile(our_fs, fs_file->meta->addr)
    )
  );
}

bool TskReader::addToBatch(TSK_FS_FILE* fs_file) {
  if (!fs_file || !fs_file->meta) {
    return false;
  }

//  const uint64_t index = fs_file->meta->addr - InumBegin;
  const uint64_t inum = fs_file->meta->addr;

//  std::cerr << fs_file->meta->addr << ' ' << InumBegin << ' ' << index << ' ' << InodeEncountered.size() << std::endl;

  if (markInodeSeen(inum)) {
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
    Path.push(fs_file->meta->addr);

    std::cerr << fs_file->name->par_addr << " -> " << Path.top() << '\n';

    Output->outputDirent(TskUtils::convertName(*fs_file->name));
  }

  //
  // handle the meta
  //
  jsoncons::json meta = TskUtils::convertMeta(*fs_file->meta, *Tsg);
  jsoncons::json& attrs = meta["attrs"];

  // ridiculous bullshit to force attrs to be populated
  Wrapper->populateAttrs(fs_file);

  // handle the attrs
  if (fs_file->meta->attr) {
    for (const TSK_FS_ATTR* a = fs_file->meta->attr->head; a; a = a->next) {
      if (a->flags & TSK_FS_ATTR_INUSE) {
        attrs.push_back(TskUtils::convertAttr(*a));
      }
    }
  }

  Input->push({std::move(meta), makeBlockSequence(fs_file)});

  return true;
}
