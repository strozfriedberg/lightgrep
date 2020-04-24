#pragma once

#include <sstream>

#include <tsk/libtsk.h>

#include "jsoncons.h"

class TskConverter {
public:
  TskConverter();

  std::string volumeSystemType(unsigned int type);
  std::string volumeFlags(unsigned int flags);

  std::string filesystemFlags(unsigned int flags);

  std::string nameType(unsigned int type);
  std::string nameFlags(unsigned int flags);

  std::string metaType(unsigned int type);
  std::string metaFlags(unsigned int flags);

  std::string attrType(unsigned int type);
  std::string attrFlags(unsigned int flags);

  std::string nrdRunFlags(unsigned int flags);

  void convertMeta(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& jsMeta);
  void convertTimestamps(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& timestamps);
  void convertAttr(const TSK_FS_ATTR& attr, jsoncons::json& jsAttr);
  void convertNRDR(const TSK_FS_ATTR_RUN& dataRun, jsoncons::json& nrdr);

  std::string hexEncode(const char* str, unsigned int size) { return hexEncode(reinterpret_cast<const unsigned char*>(str), size); }
  std::string hexEncode(unsigned const char* str, unsigned int size);

  std::string extractString(const char* str, unsigned int size);

private:
  jsoncons::json formatTimestamp(int64_t unix_time, uint32_t ns);

  std::ostringstream NanoBuf,
                     RdBuf;
};
