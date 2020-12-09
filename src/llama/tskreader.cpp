#include "tskreader.h"

#include "filerecord.h"
#include "inputhandler.h"
#include "llamatskauto.h"
#include "outputhandler.h"
#include "util.h"

TSKReader::TSKReader(const std::string& imgName):
  ImgName(imgName),
  Img(nullptr, nullptr),
  Input(),
  Output(),
  LastFS(nullptr),
  Conv()
{
}

bool TSKReader::open() {
  const char* nameHolder = ImgName.c_str();
  Img = make_unique_del(
    tsk_img_open_utf8(1, &nameHolder, TSK_IMG_TYPE_DETECT, 0),
    tsk_img_close
  );

  return bool(Img);
}

void TSKReader::setInputHandler(std::shared_ptr<InputHandler> in) {
  Input = in;
}

void TSKReader::setOutputHandler(std::shared_ptr<OutputHandler> out) {
  Output = out;
}

bool TSKReader::startReading() {
  // tell TskAuto to start giving files to processFile
  // std::cerr << "Image is " << getImageSize() << " bytes in size" << std::endl;
  const bool ret = recurseDisk();
  // std::cerr << "recurseDisk returned " << ret;
  if (ret) {
    while (!Path.empty()) {
      std::cerr << Path.top() << " done\n";
      Path.pop();
    }

    // teardown
    Input->flush();
  }
  return ret;
}

bool TSKReader::recurseDisk() {
  LlamaTskAuto walker(
    Img.get(),
    [this](const TSK_VS_INFO* vs_info) { return filterVs(vs_info); },
    [this](const TSK_VS_PART_INFO* vs_part) { return filterVol(vs_part); },
    [this](TSK_FS_INFO* fs_info) { return filterFs(fs_info); },
    [this](TSK_FS_FILE* fs_file, const char* path) { return processFile(fs_file, path); }
  );

  return walker.findFilesInImg() == 0;
}

TSK_FILTER_ENUM TSKReader::filterVs(const TSK_VS_INFO* vs_info) {
  return TSK_FILTER_CONT;
}

TSK_FILTER_ENUM TSKReader::filterVol(const TSK_VS_PART_INFO* vs_part) {
  return TSK_FILTER_CONT;
}

TSK_FILTER_ENUM TSKReader::filterFs(TSK_FS_INFO* fs_info) {
  return TSK_FILTER_CONT;
}

TSK_RETVAL_ENUM TSKReader::processFile(TSK_FS_FILE* fs_file, const char* path) {
  // std::cerr << "processFile " << path << "/" << fs_file->name->name << std::endl;
  if (fs_file->fs_info != LastFS) {
    LastFS = fs_file->fs_info;
    setInumRange(LastFS->first_inum, LastFS->last_inum);
  }
  addToBatch(fs_file);
  return TSK_OK;
}

void TSKReader::setInumRange(uint64_t begin, uint64_t end) {
  InumBegin = begin;
  InumEnd = end;
// FIXME: Apparently "first_inum" is first in some way other than the usual
// meaning of first, because it's 2 on DadeMurphy but we still see inode 0
// there. WTF? For the timebeing, just waste a few bits at the start of the
// encountered vector.
//  InodeEncountered.resize(end - begin);
  InodeEncountered.resize(end+1);
}

bool TSKReader::addToBatch(TSK_FS_FILE* fs_file) {
  if (!fs_file || !fs_file->meta) {
    return false;
  }

//  const uint64_t index = fs_file->meta->addr - InumBegin;
  const uint64_t index = fs_file->meta->addr;

//  std::cerr << fs_file->meta->addr << ' ' << InumBegin << ' ' << index << ' ' << InodeEncountered.size() << std::endl;

  if (InodeEncountered[index]) {
    return false;
  }
  InodeEncountered[index] = true;

  // ridiculous bullshit to force attrs to be populated
  tsk_fs_file_attr_get_idx(fs_file, 0);

  if (fs_file->name) {
    while (!Path.empty() && fs_file->name->par_addr != Path.top()) {
      std::cerr << Path.top() << " done\n";
      Path.pop();
    }
    Path.push(fs_file->meta->addr);

    std::cerr << fs_file->name->par_addr << " -> " << Path.top() << '\n';
  }

/*
  if (fs_file->name) {
    std::cerr << fs_file->name->par_addr << " -> " << fs_file->meta->addr;
  }
  else {
    std::cerr << << fs_file->meta->addr;
  }
  std::cerr << '\n';
*/

  TSK_FS_INFO* their_fs = fs_file->fs_info;
  TSK_FS_INFO* our_fs;

  // open our own copy of the fs, since TskAuto closes the ones it opens
  auto p = Fs.emplace(their_fs->offset, make_unique_del(nullptr, tsk_fs_close));
  if (p.second) {
    p.first->second = make_unique_del(
      tsk_fs_open_img(Img.get(), their_fs->offset, their_fs->ftype),
      tsk_fs_close
    );
  }
  our_fs = p.first->second.get();

  // open our own copy of the file, since TskAuto closes the ones it opens
  auto our_file = make_unique_del(
    tsk_fs_file_open_meta(our_fs, nullptr, fs_file->meta->addr),
    tsk_fs_file_close
  );

  Input->push({
    Conv.convertMeta(*fs_file->meta, fs_file->fs_info->ftype),
    std::static_pointer_cast<BlockSequence>(std::make_shared<TskBlockSequence>(std::move(our_file)))
  });

  if (fs_file->name) {
    Output->outputDirent(Conv.convertName(*fs_file->name));
  }
  return true;
}
