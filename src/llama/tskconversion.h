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
  std::string filesystemID(const uint8_t* id, size_t len, bool le);

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

  jsoncons::json convertImg(const TSK_IMG_INFO& img);
  jsoncons::json convertVS(const TSK_VS_INFO& vs);
  jsoncons::json convertVol(const TSK_VS_PART_INFO& vol);
  jsoncons::json convertFS(const TSK_FS_INFO& fs);

  jsoncons::json convertName(const TSK_FS_NAME& name);

  jsoncons::json convertNRDR(const TSK_FS_ATTR_RUN& dataRun);
}

class TskConverter {
public:
  TskConverter();

// TODO: could some of this be static? nonmembers?
// TODO: check how slow using stringstreams is
// TODO: check if it would be faster to use the streaming API

  jsoncons::json convertMeta(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType);
  jsoncons::json convertAttrs(const TSK_FS_META& meta) const;
  jsoncons::json convertAttr(const TSK_FS_ATTR& attr) const;

  void convertTimestamps(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& timestamps);
  void convertStandardTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);
  void convertDefaultTimestamps(const TSK_FS_META& meta, jsoncons::json& ts) const;
  void convertHFSTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);
  void convertEXTTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);
  void convertNTFSTimestamps(const TSK_FS_META& meta, jsoncons::json& ts);

private:
  jsoncons::json formatTimestamp(int64_t unix_time, uint32_t ns);

  std::ostringstream NanoBuf;
};

class TskImgAssembler {
public:
  void addImage(jsoncons::json&& img);
  void addVolumeSystem(jsoncons::json&& vs);
  void addVolume(jsoncons::json&& vol);
  void addFileSystem(jsoncons::json&& fs);

  jsoncons::json dump();

private:
  jsoncons::json Doc;
};
