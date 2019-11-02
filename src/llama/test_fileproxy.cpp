#include "scope/test.h"

#include "filerecord.h"

SCOPE_TEST(TestFileProxyAccess) {
  FileRecord rec{"/usr/bin/hello", 12u, "hello, world", SFHASH_HashValues()};
  std::string expected(rec.fileBegin(), rec.fileEnd());
  SCOPE_ASSERT_EQUAL("hello, world", expected);
}
