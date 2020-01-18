#pragma once

#include <sstream>

#include <tsk/libtsk.h>

#include "jsoncons.h"

class TskConverter {
public:
  TskConverter();

  void convertTimestamps(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& timestamps);
  void convertNRDR(const TSK_FS_ATTR_RUN& dataRun, jsoncons::json& nrdr);

private:
  jsoncons::json formatTimestamp(int64_t unix_time, uint32_t ns);

  std::ostringstream NanoBuf;
};
