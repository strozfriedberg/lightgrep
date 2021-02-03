#include "tskautowrapper.h"

TSK_FILTER_ENUM TskAutoWrapper::filterVs(const TSK_VS_INFO* vs_info) {
  return vs_cb(vs_info);
}

TSK_FILTER_ENUM TskAutoWrapper::filterVol(const TSK_VS_PART_INFO* vs_part) {
  return vol_cb(vs_part);
}

TSK_FILTER_ENUM TskAutoWrapper::filterFs(TSK_FS_INFO *fs_info) {
  return fs_cb(fs_info);
}

TSK_RETVAL_ENUM TskAutoWrapper::processFile(TSK_FS_FILE* fs_file, const char* path) {
  return file_cb(fs_file, path);
}

void TskAutoWrapper::closeImage() {
}
