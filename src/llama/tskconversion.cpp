#include "tskconversion.h"

#include <boost/date_time/posix_time/posix_time.hpp>

TskConverter::TskConverter()
{
  NanoBuf << std::fixed << std::setprecision(9);
}

void TskConverter::convertTimestamps(const TSK_FS_META& meta, TSK_FS_TYPE_ENUM fsType, jsoncons::json& timestamps) {
  timestamps["accessed"] = formatTimestamp(meta.atime, meta.atime_nano);
  timestamps["created"] = formatTimestamp(meta.crtime, meta.crtime_nano);
  timestamps["metadata"] = formatTimestamp(meta.ctime, meta.ctime_nano);
  timestamps["modified"] = formatTimestamp(meta.mtime, meta.mtime_nano);

  switch (fsType) {
    case TSK_FS_TYPE_NTFS:
      timestamps["deleted"] = jsoncons::null_type();
      timestamps["backup"] = jsoncons::null_type();
      timestamps["fn_accessed"] = formatTimestamp(meta.time2.ntfs.fn_atime, meta.time2.ntfs.fn_atime_nano);
      timestamps["fn_created"] = formatTimestamp(meta.time2.ntfs.fn_crtime, meta.time2.ntfs.fn_crtime_nano);
      timestamps["fn_metadata"] = formatTimestamp(meta.time2.ntfs.fn_ctime, meta.time2.ntfs.fn_ctime_nano);
      timestamps["fn_modified"] = formatTimestamp(meta.time2.ntfs.fn_mtime, meta.time2.ntfs.fn_mtime_nano);
      break;
    case TSK_FS_TYPE_FFS1: // need to double-check this list
    case TSK_FS_TYPE_FFS1B:
    case TSK_FS_TYPE_FFS2:
    case TSK_FS_TYPE_EXT2:
    case TSK_FS_TYPE_EXT3:
    case TSK_FS_TYPE_EXT4:
      timestamps["deleted"] = formatTimestamp(meta.time2.hfs.bkup_time, meta.time2.hfs.bkup_time_nano);
      timestamps["backup"] = jsoncons::null_type();
      timestamps["fn_accessed"] = jsoncons::null_type();
      timestamps["fn_created"] = jsoncons::null_type();
      timestamps["fn_metadata"] = jsoncons::null_type();
      timestamps["fn_modified"] = jsoncons::null_type();
      break;    
    case TSK_FS_TYPE_HFS:
      timestamps["deleted"] = jsoncons::null_type();
      timestamps["backup"] = formatTimestamp(meta.time2.hfs.bkup_time, meta.time2.hfs.bkup_time_nano);
      timestamps["fn_accessed"] = jsoncons::null_type();
      timestamps["fn_created"] = jsoncons::null_type();
      timestamps["fn_metadata"] = jsoncons::null_type();
      timestamps["fn_modified"] = jsoncons::null_type();
      break;
    default:
      timestamps["deleted"] = jsoncons::null_type();
      timestamps["backup"] = jsoncons::null_type();
      timestamps["fn_accessed"] = jsoncons::null_type();
      timestamps["fn_created"] = jsoncons::null_type();
      timestamps["fn_metadata"] = jsoncons::null_type();
      timestamps["fn_modified"] = jsoncons::null_type();
      break;
  }
}

jsoncons::json TskConverter::formatTimestamp(int64_t unix_time, uint32_t ns) {
  std::string ret;

  if (0 == unix_time) {
    if (0 == ns) {
      return jsoncons::null_type();
    }
    // some C libs will otherwise print an empty string with strftime
    ret.append("1970-01-01 00:00:00");
  }
  else {
    // Boost, you tried.
    //const boost::posix_time::ptime pt = boost::posix_time::from_time_t(unix_time);
    try {
      const boost::posix_time::ptime start(boost::gregorian::date(1970, 1, 1));
      const int64_t min = unix_time / 60;
      // Boost Date-Time has a maximum year of around 10000,
      // Which means the number of _hours_ since 1970 will fit in a int32_t
      // (In some versions of Boost (1_64), the time_duration takes an int32_t hours param,
      //  While in others it takes a std::time_t hours)
      boost::posix_time::time_duration duration(
        static_cast<boost::posix_time::time_res_traits::hour_type>(min / 60),
        static_cast<boost::posix_time::time_res_traits::min_type>(min  % 60),
        static_cast<boost::posix_time::time_res_traits::sec_type>(unix_time % 60)
      );
      const boost::posix_time::ptime pt = start + duration;
      const tm pt_tm = boost::posix_time::to_tm(pt);
      char tbuf[100];
      const size_t len = strftime(tbuf, 100, "%Y-%m-%d %H:%M:%S", &pt_tm);
      if (len) {
        ret.append(tbuf);
      } // else error??? [a greybeard once said, do not test for errors you can't handle... -- jls]
    } catch (std::exception&) {}
  }
  // fractional seconds
  if (ns - 1 < 999999999) {
    NanoBuf << double(ns) / 1000000000;
    auto frac = NanoBuf.str();
    ret.append(frac.substr(1, frac.find_last_not_of('0'))); // no leading or trailing zeroes
    NanoBuf.str("");
  }
  return ret;
}

void TskConverter::convertNRDR(const TSK_FS_ATTR_RUN& dataRun, jsoncons::json& nrdr) {
  nrdr["addr"]   = dataRun.addr;
  nrdr["len"]    = dataRun.len;
  nrdr["offset"] = dataRun.offset;
  if (dataRun.flags & TSK_FS_ATTR_RUN_FLAG_SPARSE) {
    nrdr["flags"] = "Sparse";
  }
}
