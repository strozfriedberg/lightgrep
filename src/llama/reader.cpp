#include "reader.h"
#include "filescheduler.h"
#include "tskreader.h"

#include <iostream>

std::shared_ptr<InputReaderBase>
InputReaderBase::createTSK(const std::string &imgName) {
  auto ret = std::make_shared<TSKReader>(imgName);
  if (!ret->open()) {
    throw std::runtime_error("Couldn't open image " + imgName);
  }
  return std::static_pointer_cast<InputReaderBase>(ret);
}

std::shared_ptr<InputReaderBase>
InputReaderBase::createDir(const std::string &) {
  return std::shared_ptr<InputReaderBase>();
}

TSKReader::TSKReader(const std::string &imgName) : 
  ImgName(imgName),
  CurBatch(new std::vector<FileRecord>()),
  LastFS(nullptr)
{
  CurBatch->reserve(200);
}

bool TSKReader::open() {
  const char *nameHolder = ImgName.c_str();
  return openImageUtf8(1, &nameHolder, TSK_IMG_TYPE_DETECT, 0) == 0;
}

void TSKReader::setInumRange(uint64_t begin, uint64_t end) {
  InumBegin = begin;
  InumEnd = end;
  InodeEncountered.resize(end - begin);
}

bool TSKReader::startReading(const std::shared_ptr<FileScheduler>& sink) {
  // setup
  Sink = sink;
  // tell TskAuto to start giving files to processFile
  // std::cerr << "Image is " << getImageSize() << " bytes in size" << std::endl;
  bool ret = recurseDisk();
  // std::cerr << "recurseDisk returned " << ret;
  if (!ret) {
    return false;
  }
  // teardown
  Sink->scheduleFileBatch(CurBatch);
  return true;
}

TSK_RETVAL_ENUM TSKReader::processFile(TSK_FS_FILE *fs_file, const char *path) {
  // std::cerr << "processFile " << path << "/" << fs_file->name->name << std::endl;
  if (fs_file->fs_info != LastFS) {
    LastFS = fs_file->fs_info;
    setInumRange(LastFS->first_inum, LastFS->last_inum);
  }
  if (addToBatch(fs_file, *CurBatch) && CurBatch->size() >= 200) {
    Sink->scheduleFileBatch(CurBatch);
    CurBatch.reset(new std::vector<FileRecord>());
    CurBatch->reserve(200);
  }
  return TSK_OK;
}

bool TSKReader::recurseDisk() { return 0 == findFilesInImg(); }

bool TSKReader::addToBatch(TSK_FS_FILE* fs_file, std::vector<FileRecord>& batch) {
  if (!fs_file || !fs_file->meta) {
    return false;
  }
  uint64_t index = fs_file->meta->addr - InumBegin;
  if (InodeEncountered[index]) {
    return false;
  }
  else {
    InodeEncountered[index] = true;
    batch.emplace_back(fs_file->meta, fs_file->fs_info->ftype);
    return true;
  }
}
