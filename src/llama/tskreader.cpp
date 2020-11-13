#include "tskreader.h"

#include "filerecord.h"
#include "inputhandler.h"

TSKReader::TSKReader(const std::string& imgName) :
  ImgName(imgName),
  Input(),
  LastFS(nullptr),
  Conv()
{
}

bool TSKReader::open() {
  const char* nameHolder = ImgName.c_str();
  return openImageUtf8(1, &nameHolder, TSK_IMG_TYPE_DETECT, 0) == 0;
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

void TSKReader::setInputHandler(std::shared_ptr<InputHandler> in) {
  Input = in;
}

bool TSKReader::startReading() {
  // tell TskAuto to start giving files to processFile
  // std::cerr << "Image is " << getImageSize() << " bytes in size" << std::endl;
  const bool ret = recurseDisk();
  // std::cerr << "recurseDisk returned " << ret;
  if (ret) {
    // teardown
    Input->flush();
  }
  return ret;
}

bool TSKReader::recurseDisk() {
  return 0 == findFilesInImg();
}

TSK_FILTER_ENUM TSKReader::filterVs(const TSK_VS_INFO* vs_info) {
  return TSK_FILTER_CONT;
}

TSK_FILTER_ENUM TSKReader::filterVol(const TSK_VS_PART_INFO* vs_part) {
  return TSK_FILTER_CONT;
}

TSK_FILTER_ENUM TSKReader::filterFs(TSK_FS_INFO *fs_info) {
  return TSK_FILTER_CONT;
}

TSK_RETVAL_ENUM TSKReader::processFile(TSK_FS_FILE* fs_file, const char* /* path*/) {
  // std::cerr << "processFile " << path << "/" << fs_file->name->name << std::endl;
  if (fs_file->fs_info != LastFS) {
    LastFS = fs_file->fs_info;
    setInumRange(LastFS->first_inum, LastFS->last_inum);
  }
  addToBatch(fs_file);
  return TSK_OK;
}

bool TSKReader::addToBatch(TSK_FS_FILE* fs_file) {
  if (!fs_file || !fs_file->meta) {
    return false;
  }

//  const uint64_t index = fs_file->meta->addr - InumBegin;
  const uint64_t index = fs_file->meta->addr;

  if (InodeEncountered[index]) {
    return false;
  }

  InodeEncountered[index] = true;
  Input->push(Conv.convertFile(*fs_file));
  return true;
}
