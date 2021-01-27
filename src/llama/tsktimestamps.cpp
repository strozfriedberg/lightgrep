#include "tsktimestamps.h"

#include <iomanip>

#include "timestamps.h"

jsoncons::json nullEmpty(std::string&& s) {
  return s.empty() ? jsoncons::null_type() : jsoncons::json(std::move(s));
}

CommonTimestampGetter::CommonTimestampGetter() {
  Buf << std::fixed << std::setprecision(9);
}

jsoncons::json CommonTimestampGetter::accessed(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.atime, meta.atime_nano, Buf));
}

jsoncons::json CommonTimestampGetter::created(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.crtime, meta.crtime_nano, Buf));
}

jsoncons::json CommonTimestampGetter::metadata(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.ctime, meta.ctime_nano, Buf));
}

jsoncons::json CommonTimestampGetter::modified(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.mtime, meta.mtime_nano, Buf));
}

jsoncons::json CommonTimestampGetter::deleted(const TSK_FS_META&) {
  return jsoncons::null_type();
}

jsoncons::json CommonTimestampGetter::backup(const TSK_FS_META&) {
  return jsoncons::null_type();
}

jsoncons::json CommonTimestampGetter::fn_accessed(const TSK_FS_META&) {
  return jsoncons::null_type();
}

jsoncons::json CommonTimestampGetter::fn_created(const TSK_FS_META&) {
  return jsoncons::null_type();
}

jsoncons::json CommonTimestampGetter::fn_metadata(const TSK_FS_META&) {
  return jsoncons::null_type();
}

jsoncons::json CommonTimestampGetter::fn_modified(const TSK_FS_META&) {
  return jsoncons::null_type();
}

jsoncons::json NTFSTimestampGetter::fn_accessed(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.time2.ntfs.fn_atime,
                                   meta.time2.ntfs.fn_atime_nano, Buf));
}

jsoncons::json NTFSTimestampGetter::fn_created(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.time2.ntfs.fn_crtime,
                                   meta.time2.ntfs.fn_crtime_nano, Buf));
}

jsoncons::json NTFSTimestampGetter::fn_metadata(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.time2.ntfs.fn_ctime,
                                   meta.time2.ntfs.fn_ctime_nano, Buf));
}

jsoncons::json NTFSTimestampGetter::fn_modified(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.time2.ntfs.fn_mtime,
                                   meta.time2.ntfs.fn_mtime_nano, Buf));
}

jsoncons::json EXTTimestampGetter::deleted(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.time2.hfs.bkup_time,
                                   meta.time2.hfs.bkup_time_nano, Buf));
}

jsoncons::json HFSTimestampGetter::backup(const TSK_FS_META& meta) {
  return nullEmpty(formatTimestamp(meta.time2.hfs.bkup_time,
                                   meta.time2.hfs.bkup_time_nano, Buf));
}
