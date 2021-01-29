#include "tskwalkerimpl.h"

#include "llamatskauto.h"

bool TskWalkerImpl::walk(
  TSK_IMG_INFO* info,
  std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)> vs_cb,
  std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)> vol_cb,
  std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> fs_cb,
  std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)> file_cb
) {
  return LlamaTskAuto(info, vs_cb, vol_cb, fs_cb, file_cb).findFilesInImg() == 0;
}
