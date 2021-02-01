#pragma once

#include <memory>

#include <tsk/libtsk.h>

class TskWrapper {
public:
  std::unique_ptr<TSK_IMG_INFO, void(*)(TSK_IMG_INFO*)> openImg(const char* path) const;

  std::unique_ptr<TSK_FS_INFO, void(*)(TSK_FS_INFO*)> openFS(TSK_IMG_INFO* img, TSK_OFF_T off, TSK_FS_TYPE_ENUM type) const;

  std::unique_ptr<TSK_FS_FILE, void(*)(TSK_FS_FILE*)> openFile(TSK_FS_INFO* fs, TSK_INUM_T inum) const;

  void populateAttrs(TSK_FS_FILE* file) const; 
};
