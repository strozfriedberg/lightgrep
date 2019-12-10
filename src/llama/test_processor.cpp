#include "processor.h"

#include "lightgrep/api.h"
#include "filerecord.h"
#include "outputbase.h"
#include "mockoutput.h"

#include <hasher.h>
#include <scope/test.h>

#include <vector>

SCOPE_TEST(TestSizeMatch) {
  std::shared_ptr<ProgramHandle> lg;

  std::string matches = "whatever\t8\td869db7fe62fb07c25a0403ecaea55031744b5fb";
  LG_Error* errPtr = nullptr;
  auto matcher = std::shared_ptr<SFHASH_FileMatcher>(sfhash_create_matcher(matches.data(), matches.data() + matches.size(), &errPtr), sfhash_destroy_matcher);
  // std::shared_ptr<SFHASH_FileMatcher> matcher;
  Processor proc(matcher, lg);

  MockOutput mock;
  FileRecord rec1;
  rec1.Size = 8;
  rec1._data = "whatever";

  proc.process(rec1, mock);
  SCOPE_ASSERT_EQUAL(1u, mock.Received.size());
  SCOPE_ASSERT_EQUAL({0xd8, 0x69, 0xdb, 0x7f, 0xe6, 0x2f, 0xb0, 0x7c, 0x25, 0xa0, 0x40, 0x3e, 0xca, 0xea, 0x55, 0x03, 0x17, 0x44, 0xb5, 0xfb},
                      mock.Received[0].Hashes.Sha1);
  SCOPE_ASSERT_EQUAL({0x00, 0x8c, 0x59, 0x26, 0xca, 0x86, 0x10, 0x23, 0xc1, 0xd2, 0xa3, 0x66, 0x53, 0xfd, 0x88, 0xe2},
                      mock.Received[0].Hashes.Md5);

  FileRecord rec2;
  rec2.Size = 8;
  rec2._data = "deadbeef";
  std::fill_n(&rec2.Hashes.Md5[0], 16, 0);
  std::fill_n(&rec2.Hashes.Sha1[0], 20, 0);
  proc.process(rec2, mock);
  SCOPE_ASSERT_EQUAL(1u, mock.Received.size()); // mock size shouldn't change from above
  // rec.Hashes will be altered, though, as the size matched
  SCOPE_ASSERT_EQUAL({0x4f, 0x41, 0x24, 0x38, 0x47, 0xda, 0x69, 0x3a, 0x4f, 0x35, 0x6c, 0x04, 0x86, 0x11, 0x4b, 0xc6},
                      rec2.Hashes.Md5);
  SCOPE_ASSERT_EQUAL({0xf4, 0x9c, 0xf6, 0x38, 0x1e, 0x32, 0x2b, 0x14, 0x70, 0x53, 0xb7, 0x4e, 0x45, 0x00, 0xaf, 0x85, 0x33, 0xac, 0x1e, 0x4c},
                      rec2.Hashes.Sha1);

  FileRecord rec3;
  rec3.Size = 9;
  rec3._data = "excelsior";
  std::fill_n(&rec3.Hashes.Md5[0], 16, 0);
  std::fill_n(&rec3.Hashes.Sha1[0], 20, 0);
  proc.process(rec3, mock);
  SCOPE_ASSERT_EQUAL(1u, mock.Received.size()); // mock size shouldn't change from above
  // rec.Hashes will not be altered
  SCOPE_ASSERT_EQUAL({0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                      rec3.Hashes.Md5);
  SCOPE_ASSERT_EQUAL({0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                      rec3.Hashes.Sha1);
}
