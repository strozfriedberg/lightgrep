#include "hitwriter.h"

#include <scope/test.h>

SCOPE_TEST(hitWriterOutput) {
/*
  std::vector<std::pair<uint32, uint32 >> tbl;
  std::vector<std::string> keys,
                             encodings;
  std::stringstream stream;

  keys.push_back("whatever");
  encodings.push_back("ASCII");
  encodings.push_back("UCS-16");

  tbl.push_back(std::make_pair<uint32,uint32>(0, 0));
  tbl.push_back(std::make_pair<uint32,uint32>(0, 1));

  HitWriter writer(stream, tbl, keys, encodings);
  writer.collect(SearchHit(0, 10, 0));

  uint64 offset, end, keyIndex;
  std::string key, encoding;

  stream >> offset >> end >> keyIndex >> key >> encoding;
  SCOPE_ASSERT_EQUAL(0u, offset);
  SCOPE_ASSERT_EQUAL(10u, end);
  SCOPE_ASSERT_EQUAL(0u, keyIndex);
  SCOPE_ASSERT_EQUAL(std::string("whatever"), key);
  SCOPE_ASSERT_EQUAL(std::string("ASCII"), encoding);

  writer.collect(SearchHit(2, 22, 1));

  stream >> offset >> end >> keyIndex >> key >> encoding;
  SCOPE_ASSERT_EQUAL(2u, offset);
  SCOPE_ASSERT_EQUAL(22u, end);
  SCOPE_ASSERT_EQUAL(0u, keyIndex);
  SCOPE_ASSERT_EQUAL(std::string("whatever"), key);
  SCOPE_ASSERT_EQUAL(std::string("UCS-16"), encoding);
*/
}
