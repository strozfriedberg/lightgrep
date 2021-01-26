#pragma once

#include <sstream>

#include <tsk/libtsk.h>

#include "jsoncons_wrapper.h"

class TimestampGetter {
public:
  virtual ~TimestampGetter() {}

  virtual jsoncons::json accessed(const TSK_FS_META& meta) = 0;

  virtual jsoncons::json created(const TSK_FS_META& meta) = 0;

  virtual jsoncons::json metadata(const TSK_FS_META& meta) = 0;

  virtual jsoncons::json modified(const TSK_FS_META& meta) = 0;

  virtual jsoncons::json deleted(const TSK_FS_META& meta) = 0;

  virtual jsoncons::json backup(const TSK_FS_META& meta) = 0;

  virtual jsoncons::json fn_accessed(const TSK_FS_META& meta) = 0;

  virtual jsoncons::json fn_created(const TSK_FS_META& meta) = 0;

  virtual jsoncons::json fn_metadata(const TSK_FS_META& meta) = 0;

  virtual jsoncons::json fn_modified(const TSK_FS_META& meta) = 0;
};

class CommonTimestampGetter: public TimestampGetter {
public:
  CommonTimestampGetter();

  virtual ~CommonTimestampGetter() {}

  virtual jsoncons::json accessed(const TSK_FS_META& meta) override;

  virtual jsoncons::json created(const TSK_FS_META& meta) override;

  virtual jsoncons::json metadata(const TSK_FS_META& meta) override;

  virtual jsoncons::json modified(const TSK_FS_META& meta) override;

  virtual jsoncons::json deleted(const TSK_FS_META& meta) override;

  virtual jsoncons::json backup(const TSK_FS_META& meta) override;

  virtual jsoncons::json fn_accessed(const TSK_FS_META& meta) override;

  virtual jsoncons::json fn_created(const TSK_FS_META& meta) override;

  virtual jsoncons::json fn_metadata(const TSK_FS_META& meta) override;

  virtual jsoncons::json fn_modified(const TSK_FS_META& meta) override;

protected:
  std::ostringstream Buf;
};

class NTFSTimestampGetter: public CommonTimestampGetter {
public:
  virtual ~NTFSTimestampGetter() {}

  virtual jsoncons::json fn_accessed(const TSK_FS_META& meta) override;

  virtual jsoncons::json fn_created(const TSK_FS_META& meta) override;

  virtual jsoncons::json fn_metadata(const TSK_FS_META& meta) override;

  virtual jsoncons::json fn_modified(const TSK_FS_META& meta) override;
};

class EXTTimestampGetter: public CommonTimestampGetter {
public:
  virtual ~EXTTimestampGetter() {}

  virtual jsoncons::json deleted(const TSK_FS_META& meta) override;
};

class HFSTimestampGetter: public CommonTimestampGetter {
public:
  virtual ~HFSTimestampGetter() {}

  virtual jsoncons::json backup(const TSK_FS_META& meta) override;
};
