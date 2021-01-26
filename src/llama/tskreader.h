#pragma once

#include <map>
#include <memory>
#include <stack>
#include <vector>

#include <tsk/libtsk.h>

#include "inputreader.h"
#include "tskconversion.h"

class InputHandler;
class OutputHandler;
class TimestampGetter;

class TSKReader: public InputReader {
public:
  TSKReader(const std::string& imgName);

  virtual ~TSKReader() {}

  bool open();

  virtual void setInputHandler(std::shared_ptr<InputHandler> in) override;

  virtual void setOutputHandler(std::shared_ptr<OutputHandler> in) override;

  virtual bool startReading() override;

  // recurseDisk wraps TskAuto::findFilesInImg(). Override to replace/mock.
  virtual bool recurseDisk();

  bool addToBatch(TSK_FS_FILE* fs_file);

  void setInodeRange(uint64_t begin, uint64_t end);

  void setBlockRange(uint64_t begin, uint64_t end);

  bool markInodeSeen(uint64_t inum);

  void claimBlockRange(uint64_t begin, uint64_t end);

  // callbacks
  TSK_FILTER_ENUM filterVs(const TSK_VS_INFO* vs_info);

  TSK_FILTER_ENUM filterVol(const TSK_VS_PART_INFO* vs_part);

  TSK_FILTER_ENUM filterFs(TSK_FS_INFO* fs_info);

  TSK_RETVAL_ENUM processFile(TSK_FS_FILE* fs_file, const char* path);

private:
  std::string ImgName;
  std::unique_ptr<TSK_IMG_INFO, void(*)(TSK_IMG_INFO*)> Img;
  std::map<TSK_OFF_T, std::unique_ptr<TSK_FS_INFO, void(*)(TSK_FS_INFO*)>> Fs;

  std::shared_ptr<InputHandler> Input;
  std::shared_ptr<OutputHandler> Output;

  const TSK_FS_INFO* LastFS;

  std::vector<bool> InodeEncountered;

  uint64_t InumBegin,
           InumEnd;

  std::vector<bool> Allocated;

  uint64_t BlockBegin,
           BlockEnd;

  TskConverter Conv;
  TskImgAssembler Ass;
  std::unique_ptr<TimestampGetter> Tsg;

  std::stack<TSK_INUM_T> Path;
};
