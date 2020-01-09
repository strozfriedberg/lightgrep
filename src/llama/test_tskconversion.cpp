#include <scope/test.h>

#include "tskconversion.h"

SCOPE_TEST(testTskConvertTimestamps) {
  TSK_FS_META meta;
  meta.atime = 1578364822; // 2020-01-07 02:40:22
  meta.atime_nano = 123456700;
  meta.crtime = 31337; // 1970-01-01 08:42:17
  meta.crtime_nano = 123456400;
  meta.ctime = 234123870; // 1977-06-02 18:24:30
  meta.ctime_nano = 315227845;
  meta.mtime = 314159265; // 1979-12-16 02:27:45
  meta.mtime_nano = 999999999;

  jsoncons::json ts;

  TskConverter munge;
  munge.convertTimestamps(meta, TSK_FS_TYPE_DETECT, ts);
  // basic four are good
  SCOPE_ASSERT_EQUAL("2020-01-07 02:40:22.1234567", ts.at("accessed"));
  SCOPE_ASSERT_EQUAL("1970-01-01 08:42:17.1234564", ts.at("created"));
  SCOPE_ASSERT_EQUAL("1977-06-02 18:24:30.315227845", ts.at("metadata"));
  SCOPE_ASSERT_EQUAL("1979-12-16 02:27:45.999999999", ts.at("modified"));
  // others not so much
  SCOPE_ASSERT(ts.at("deleted").is_null());
  SCOPE_ASSERT(ts.at("backup").is_null());
  SCOPE_ASSERT(ts.at("fn_accessed").is_null());
  SCOPE_ASSERT(ts.at("fn_created").is_null());
  SCOPE_ASSERT(ts.at("fn_metadata").is_null());
  SCOPE_ASSERT(ts.at("fn_modified").is_null());
}

SCOPE_TEST(testTskConvertEpochBeginningIsNull) {
  TSK_FS_META meta;
  meta.atime = 0; // 1970-01-01 00:00:00
  meta.atime_nano = 0;
  meta.crtime = 1; // 1970-01-01 00:00::01
  meta.crtime_nano = 0;
  meta.ctime = 0; // 1970-01-01 00:00:00.000000001
  meta.ctime_nano = 1;
  meta.mtime = 0; // 1970-01-01 00:00:00
  meta.mtime_nano = 0;

  jsoncons::json ts;

  TskConverter munge;
  munge.convertTimestamps(meta, TSK_FS_TYPE_DETECT, ts);
  // basic four are good
  SCOPE_ASSERT(ts.at("accessed").is_null());
  SCOPE_ASSERT_EQUAL("1970-01-01 00:00:01", ts.at("created"));
  SCOPE_ASSERT_EQUAL("1970-01-01 00:00:00.000000001", ts.at("metadata"));
  SCOPE_ASSERT(ts.at("modified").is_null());
}
