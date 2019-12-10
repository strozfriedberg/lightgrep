#include <scope/test.h>

#include <sstream>
#include <iostream>

#include "filerecord.h"
#include "mockoutput.h"
#include "recordbuffer.h"

SCOPE_TEST(testRecordBufferFlush) {
  MockOutput mock;
  RecordBuffer r("my-recs", 10u, mock);

  r.write("whatever"); // will also write a \n
  SCOPE_ASSERT_EQUAL(9u, r.size());
  SCOPE_ASSERT_EQUAL(0u, mock.OutFiles.size());
  r.write("a");
  SCOPE_ASSERT_EQUAL(11u, r.size());
  SCOPE_ASSERT_EQUAL(0u, mock.OutFiles.size());
  r.write("b");
  SCOPE_ASSERT_EQUAL(2u, r.size());
  SCOPE_ASSERT_EQUAL(1u, mock.OutFiles.size());
}

SCOPE_TEST(testRecordBufferOutput) {
  MockOutput mock;
  RecordBuffer r("recs/my-recs", 1u, mock);
  r.write("a record");
  r.flush();
  SCOPE_ASSERT_EQUAL(1u, mock.OutFiles.size());
  SCOPE_ASSERT_EQUAL("recs/my-recs-0001.jsonl", mock.OutFiles[0].Path);
  SCOPE_ASSERT_EQUAL(9u, mock.OutFiles[0].Size);
}
