#include "filescheduler.h"
#include "tskreader.h"

TSKReader::TSKReader(const std::string& imgName) :
  ImgName(imgName),
  CurBatch(new std::vector<FileRecord>()),
  LastFS(nullptr)
{
  CurBatch->reserve(200);
}

bool TSKReader::open() {
  const char* nameHolder = ImgName.c_str();
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
  const bool ret = recurseDisk();
  // std::cerr << "recurseDisk returned " << ret;
  if (ret) {
    // teardown
    Sink->scheduleFileBatch(CurBatch);
  }
  return ret;
}

TSK_RETVAL_ENUM TSKReader::processFile(TSK_FS_FILE* fs_file, const char* /* path*/) {
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

bool TSKReader::recurseDisk() {
  return 0 == findFilesInImg();
}

bool TSKReader::addToBatch(const TSK_FS_FILE* fs_file, std::vector<FileRecord>& batch) {
  if (!fs_file || !fs_file->meta) {
    return false;
  }

  const uint64_t index = fs_file->meta->addr - InumBegin;
  if (InodeEncountered[index]) {
    return false;
  }

  InodeEncountered[index] = true;
  batch.emplace_back(fs_file);
  return true;
}
