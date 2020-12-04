#pragma once

#include <sstream>
#include <string>

#include <tsk/libtsk.h>

#include "jsoncons_wrapper.h"

namespace TskUtils {
  std::string extractString(const char* str, unsigned int size);

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

  template <class F>
  std::string flagsString(unsigned int flags, const F& fmap) {
    if (!flags) {
      return "";
    }

    std::string ret;
    bool first = true;
    for (const auto& f: fmap) {
      if (flags & f.first) {
        if (first) {
          first = false;
        }
        else {
          ret += ", ";
        }
        ret += f.second;
      }
    }

    return ret;
  }
}

class TskConverter {
public:
  TskConverter();

// TODO: could some of this be static? nonmembers?
// TODO: check how slow using stringstreams is
// TODO: check if it would be faster to use the streaming API

  jsoncons::json convertName(const TSK_FS_NAME& name) const;
  jsoncons::json convertMeta(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType);
  jsoncons::json convertAttrs(const TSK_FS_META& meta) const;
  jsoncons::json convertAttr(const TSK_FS_ATTR& attr) const;
  jsoncons::json convertNRDR(const TSK_FS_ATTR_RUN& dataRun) const;

  void convertTimestamps(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& timestamps);
  void convertStandardTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);
  void convertDefaultTimestamps(const TSK_FS_META& meta, jsoncons::json& ts) const;
  void convertHFSTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);
  void convertEXTTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);
  void convertNTFSTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);

private:
  jsoncons::json formatTimestamp(int64_t unix_time, uint32_t ns);

  std::ostringstream NanoBuf,
                     RdBuf;
};
