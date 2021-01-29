#pragma once

#include <functional>

#include <tsk/libtsk.h>

class LlamaTskAuto: public TskAuto {
public:
  LlamaTskAuto(
    TSK_IMG_INFO* info,
    std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)> vs_cb,
    std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)> vol_cb,
    std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> fs_cb,
    std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)> file_cb
  ):
    vs_cb(vs_cb),
    vol_cb(vol_cb),
    fs_cb(fs_cb),
    file_cb(file_cb)
  {
    m_internalOpen = false;
    m_img_info = info;
  }

  virtual ~LlamaTskAuto() {}

  virtual TSK_RETVAL_ENUM processFile(TSK_FS_FILE* fs_file,
                                      const char* path) override;

  virtual TSK_FILTER_ENUM filterVs(const TSK_VS_INFO* vs_info) override;

  virtual TSK_FILTER_ENUM filterVol(const TSK_VS_PART_INFO* vs_part) override;

  virtual TSK_FILTER_ENUM filterFs(TSK_FS_INFO* fs_info) override;

  virtual void closeImage() override;

private:
  std::function<TSK_FILTER_ENUM(const TSK_VS_INFO*)> vs_cb;
  std::function<TSK_FILTER_ENUM(const TSK_VS_PART_INFO*)> vol_cb;
  std::function<TSK_FILTER_ENUM(TSK_FS_INFO*)> fs_cb;
  std::function<TSK_RETVAL_ENUM(TSK_FS_FILE*, const char*)> file_cb;
};
