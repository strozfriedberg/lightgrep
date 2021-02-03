#pragma once

#include <functional>
#include <memory>

#include <tsk/libtsk.h>

#include "jsoncons_wrapper.h"
#include "tsktimestamps.h"

class DummyTsk {
public:
  std::unique_ptr<TSK_IMG_INFO, void(*)(TSK_IMG_INFO*)> openImg(const char* /* path */) const {
    return {nullptr, nullptr};
  }

  std::unique_ptr<TSK_FS_INFO, void(*)(TSK_FS_INFO*)> openFS(TSK_IMG_INFO* /* img */, TSK_OFF_T /* off */, TSK_FS_TYPE_ENUM /* type */) const {
    return {nullptr, nullptr};
  }

  std::unique_ptr<TSK_FS_FILE, void(*)(TSK_FS_FILE*)> openFile(TSK_FS_INFO* /*fs*/, TSK_INUM_T /* inum */) const {
    return {nullptr, nullptr};
  }

  void populateAttrs(TSK_FS_FILE* /* file */) const {
  }

  bool walk(
    TSK_IMG_INFO* /* info */,
    std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)> /* vs_cb */,
    std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)> /* vol_cb */,
    std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> /* fs_cb */,
    std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)> /* file_cb */
  ) {
    return true;
  }

  jsoncons::json convertImg(const TSK_IMG_INFO& /* img */) const {
    return jsoncons::json();
  }

  jsoncons::json convertVS(const TSK_VS_INFO& /* vs */) const {
    return jsoncons::json();
  }

  jsoncons::json convertVol(const TSK_VS_PART_INFO& /* vol */) const {
    return jsoncons::json();
  }

  jsoncons::json convertFS(const TSK_FS_INFO& /* fs */) const {
    return jsoncons::json();
  }

  jsoncons::json convertName(const TSK_FS_NAME& /* name */) const {
    return jsoncons::json();
  }

  jsoncons::json convertMeta(const TSK_FS_META& /* meta */, TimestampGetter& /* ts */) const{
    return jsoncons::json();
  }

  jsoncons::json convertAttr(const TSK_FS_ATTR& /* attr */) const {
    return jsoncons::json();
  }

  std::unique_ptr<TimestampGetter> makeTimestampGetter(TSK_FS_TYPE_ENUM /* fstype */) const {
    return nullptr;
  }
};
