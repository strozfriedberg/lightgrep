#include "hitwriter.h"

#include <scope/test.h>

/*
SCOPE_TEST(hitWriterOutput) {
  std::vector<std::pair<uint32_t, uint32_t >> tbl;
  std::vector<std::string> keys,
                             encodings;
  std::stringstream stream;

  keys.push_back("whatever");
  encodings.push_back("ASCII");
  encodings.push_back("UCS-16");

  tbl.push_back(std::make_pair<uint32_t,uint32_t>(0, 0));
  tbl.push_back(std::make_pair<uint32_t,uint32_t>(0, 1));

  HitWriter writer(stream, tbl, keys, encodings);
  writer.collect(SearchHit(0, 10, 0));

  uint64_t offset, end, keyIndex;
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
}
*/

const char TXT[] = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9";

SCOPE_TEST(findLeadingContext0) {
  SCOPE_ASSERT_EQUAL(TXT+10, find_leading_context(TXT, TXT+10, 0));
}

SCOPE_TEST(findLeadingContext1) {
  SCOPE_ASSERT_EQUAL(TXT+8, find_leading_context(TXT, TXT+10, 1));
}

SCOPE_TEST(findLeadingContext2) {
  SCOPE_ASSERT_EQUAL(TXT+6, find_leading_context(TXT, TXT+10, 2));
}

SCOPE_TEST(findLeadingContext3) {
  SCOPE_ASSERT_EQUAL(TXT+4, find_leading_context(TXT, TXT+10, 3));
}

SCOPE_TEST(findLeadingContext4) {
  SCOPE_ASSERT_EQUAL(TXT+2, find_leading_context(TXT, TXT+10, 4));
}

SCOPE_TEST(findLeadingContext5) {
  SCOPE_ASSERT_EQUAL(TXT, find_leading_context(TXT, TXT+10, 5));
}

SCOPE_TEST(findLeadingContext6) {
  SCOPE_ASSERT_EQUAL(TXT, find_leading_context(TXT, TXT+10, 6));
}

SCOPE_TEST(findTrailingContext0) {
  SCOPE_ASSERT_EQUAL(TXT+11, find_trailing_context(TXT+11, TXT+19, 0));
}

SCOPE_TEST(findTrailingContext1) {
  SCOPE_ASSERT_EQUAL(TXT+13, find_trailing_context(TXT+11, TXT+19, 1));
}

SCOPE_TEST(findTrailingContext2) {
  SCOPE_ASSERT_EQUAL(TXT+15, find_trailing_context(TXT+11, TXT+19, 2));
}

SCOPE_TEST(findTrailingContext3) {
  SCOPE_ASSERT_EQUAL(TXT+17, find_trailing_context(TXT+11, TXT+19, 3));
}

SCOPE_TEST(findTrailingContext4) {
  SCOPE_ASSERT_EQUAL(TXT+19, find_trailing_context(TXT+11, TXT+19, 4));
}

SCOPE_TEST(findTrailingContext5) {
  SCOPE_ASSERT_EQUAL(TXT+19, find_trailing_context(TXT+11, TXT+19, 5));
}

SCOPE_TEST(findTrailingContext6) {
  SCOPE_ASSERT_EQUAL(TXT+19, find_trailing_context(TXT+11, TXT+19, 6));
}
