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
  meta.mtime_nano = 589793238;

  jsoncons::json ts;

  TskConverter munge;
  munge.convertTimestamps(meta, ts);

  SCOPE_ASSERT_EQUAL("2020-01-07 02:40:22.1234567", ts["accessed"]);
  SCOPE_ASSERT_EQUAL("1970-01-01 08:42:17.1234564", ts["created"]);
  SCOPE_ASSERT_EQUAL("1977-06-02 18:24:30.315227845", ts["metadata"]);
  SCOPE_ASSERT_EQUAL("1979-12-16 02:27:45.589793238", ts["modified"]);
}
