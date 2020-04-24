#pragma once

#include <tsk/libtsk.h>

#include "filerecord.h"
#include "reader.h"

class FileScheduler;

class TSKReader : public InputReaderBase, public TskAuto {
public:
  TSKReader(const std::string &imgName);
  virtual ~TSKReader() {}

  bool open();

  void setInumRange(uint64_t begin, uint64_t end);

  bool startReading(const std::shared_ptr<FileScheduler>& sink) override;

  virtual TSK_RETVAL_ENUM processFile(TSK_FS_FILE *fs_file,
                                      const char *path) override;

  // recurseDisk wraps TskAuto::findFilesInImg(). Override to replace/mock.
  virtual bool recurseDisk();

  bool addToBatch(TSK_FS_FILE* fs_file, std::vector<FileRecord>& batch);

private:
  std::string ImgName;

  std::shared_ptr<FileScheduler> Sink;

  std::shared_ptr<std::vector<FileRecord>> CurBatch;

  TSK_FS_INFO* LastFS;

  std::vector<bool> InodeEncountered;

  uint64_t InumBegin,
           InumEnd;
};
