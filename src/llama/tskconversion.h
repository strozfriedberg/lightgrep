#pragma once

#include <sstream>

#include <tsk/libtsk.h>

#include "jsoncons_wrapper.h"

class TskConverter {
public:
  TskConverter();

// FIXME: should be static or nonmembers
  std::string volumeSystemType(unsigned int type) const;
  std::string volumeFlags(unsigned int flags) const;

  std::string filesystemFlags(unsigned int flags) const;

  std::string nameType(unsigned int type) const;
  std::string nameFlags(unsigned int flags) const;

  std::string metaType(unsigned int type) const;
  std::string metaFlags(unsigned int flags) const;

  std::string attrType(unsigned int type) const;
  std::string attrFlags(unsigned int flags) const;

  std::string nrdRunFlags(unsigned int flags) const;

  void convertFile(const TSK_FS_FILE& file, jsoncons::json&jsFile);
  void convertName(const TSK_FS_NAME& name, jsoncons::json& jsMeta) const;
  void convertMeta(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& jsMeta);
  void convertAttr(const TSK_FS_ATTR& attr, jsoncons::json& jsAttr) const;
  void convertNRDR(const TSK_FS_ATTR_RUN& dataRun, jsoncons::json& nrdr) const;

  void convertTimestamps(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& timestamps);
  void convertStandardTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);
  void convertDefaultTimestamps(const TSK_FS_META& meta, jsoncons::json& ts) const;
  void convertHFSTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);
  void convertEXTTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);
  void convertNTFSTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);

// FIXME: should be static or nonmembers
  std::string hexEncode(const void* str, unsigned int size) const;

  std::string extractString(const char* str, unsigned int size) const;

private:
  jsoncons::json formatTimestamp(int64_t unix_time, uint32_t ns);

  std::ostringstream NanoBuf,
                     RdBuf;
};
