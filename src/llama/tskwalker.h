#pragma once

#include <functional>

#include <tsk/libtsk.h>

class TskWalker {
public:
  virtual ~TskWalker() {}

  virtual bool walk(
    TSK_IMG_INFO* info,
    std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)> vs_cb,
    std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)> vol_cb,
    std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> fs_cb,
    std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)> file_cb
  ) = 0;
};
