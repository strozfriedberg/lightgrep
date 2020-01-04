#include "reader.h"
#include "filescheduler.h"
#include "tskreader.h"

#include <iostream>

std::shared_ptr<InputReaderBase>
InputReaderBase::createTSK(const std::string &imgName) {
  return std::static_pointer_cast<InputReaderBase>(
      std::make_shared<TSKReader>(imgName));
}

std::shared_ptr<InputReaderBase>
InputReaderBase::createDir(const std::string &) {
  return std::shared_ptr<InputReaderBase>();
}

TSKReader::TSKReader(const std::string &imgName) : 
  ImgName(imgName),
  CurBatch(new std::vector<FileRecord>())
{
  CurBatch->reserve(200);

  const char *nameHolder = imgName.c_str();
  if (openImageUtf8(1, &nameHolder, TSK_IMG_TYPE_DETECT, 0) != 0) {
    throw std::runtime_error("Couldn't open image " + imgName);
  }
}

bool TSKReader::startReading(const std::shared_ptr<FileScheduler>& sink) {
  // setup
  Sink = sink;
  // tell TskAuto to start giving files to processFile
  std::cerr << "Image is " << getImageSize() << " bytes in size" << std::endl;
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
  // std::cerr << "processFile " << path << "/" << fs_file->name->name <<
  // std::endl;

  std::string fullpath(path);
  fullpath.append(fs_file->name->name);
  CurBatch->push_back(
      FileRecord{fullpath, fs_file->meta ? uint64_t(fs_file->meta->size) : 0u});
  if (CurBatch->size() >= 200) {
    Sink->scheduleFileBatch(CurBatch);
    CurBatch.reset(new std::vector<FileRecord>());
    CurBatch->reserve(200);
  }
  return TSK_OK;
}

bool TSKReader::recurseDisk() { return 0 == findFilesInImg(); }
