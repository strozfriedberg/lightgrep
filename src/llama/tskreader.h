#pragma once

#include <vector>

#include <tsk/libtsk.h>

#include "inputreader.h"

class InputHandler;
class FileRecord;

class TSKReader : public InputReader, public TskAuto {
public:
  TSKReader(const std::string& imgName);

  virtual ~TSKReader() {}

  bool open();

  void setInumRange(uint64_t begin, uint64_t end);

  virtual void setInputHandler(std::shared_ptr<InputHandler> in) override;

  virtual bool startReading() override;

  virtual TSK_RETVAL_ENUM processFile(TSK_FS_FILE* fs_file,
                                      const char* path) override;

  // recurseDisk wraps TskAuto::findFilesInImg(). Override to replace/mock.
  virtual bool recurseDisk();

  bool addToBatch(TSK_FS_FILE* fs_file);

private:
  std::string ImgName;

  std::shared_ptr<InputHandler> Input;

  const TSK_FS_INFO* LastFS;

  std::vector<bool> InodeEncountered;

  uint64_t InumBegin,
           InumEnd;
};
