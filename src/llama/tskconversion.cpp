#include "tskconversion.h"

#include <boost/date_time/posix_time/posix_time.hpp>

TskConverter::TskConverter()
{
  NanoBuf << std::setprecision(9);
}

void TskConverter::convertTimestamps(const TSK_FS_META& meta, jsoncons::json& timestamps) {
  timestamps["accessed"] = formatTimestamp(meta.atime, meta.atime_nano);
  timestamps["created"] = formatTimestamp(meta.crtime, meta.crtime_nano);
  timestamps["metadata"] = formatTimestamp(meta.ctime, meta.ctime_nano);
  timestamps["modified"] = formatTimestamp(meta.mtime, meta.mtime_nano);
}

std::string TskConverter::formatTimestamp(int64_t unix_time, uint32_t ns) {
  std::string ret;

  if (0 == unix_time) {
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
    ret.append(NanoBuf.str().substr(1)); // skips the leading zero
    NanoBuf.str("");
  }
  return ret;
}
