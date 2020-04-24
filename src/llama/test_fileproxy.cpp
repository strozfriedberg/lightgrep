#include "scope/test.h"

#include "filerecord.h"

SCOPE_TEST(TestFileProxyAccess) {
  FileRecord rec("/usr/bin/hello", 12u);
  rec._data = "hello, world";
  std::string expected(rec.fileBegin(), rec.fileEnd());
  SCOPE_ASSERT_EQUAL("hello, world", expected);
}
