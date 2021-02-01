#include "tskwrapper.h"

#include "util.h"

std::unique_ptr<TSK_IMG_INFO, void(*)(TSK_IMG_INFO*)> TskWrapper::openImg(const char* path) const {
  return make_unique_del(
    tsk_img_open_utf8(1, &path, TSK_IMG_TYPE_DETECT, 0),
    tsk_img_close
  );
}

std::unique_ptr<TSK_FS_INFO, void(*)(TSK_FS_INFO*)> TskWrapper::openFS(TSK_IMG_INFO* img, TSK_OFF_T off, TSK_FS_TYPE_ENUM type) const {
  return make_unique_del(tsk_fs_open_img(img, off, type), tsk_fs_close);
}

std::unique_ptr<TSK_FS_FILE, void(*)(TSK_FS_FILE*)> TskWrapper::openFile(TSK_FS_INFO* fs, TSK_INUM_T inum) const {
  return make_unique_del(
    tsk_fs_file_open_meta(fs, nullptr, inum),
    tsk_fs_file_close
  );
}

void TskWrapper::populateAttrs(TSK_FS_FILE* file) const {
  // ridiculous bullshit to force attrs to be populated
  tsk_fs_file_attr_get_idx(file, 0);
}
