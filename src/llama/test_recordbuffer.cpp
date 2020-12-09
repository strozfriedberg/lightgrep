#include <scope/test.h>

#include <sstream>
#include <iostream>

#include "mockoutputwriter.h"
#include "outputchunk.h"
#include "recordbuffer.h"

SCOPE_TEST(testRecordBufferFlush) {
  MockOutputWriter mock;
  RecordBuffer r("my-recs", 10u, [&mock](const OutputChunk& c){ mock.OutFiles.push_back(c); });

  r.write("whatever"); // will also write a \n
  SCOPE_ASSERT_EQUAL(9u, r.size());
  SCOPE_ASSERT_EQUAL(0u, mock.OutFiles.size());
  r.write("a");
  SCOPE_ASSERT_EQUAL(11u, r.size());
  SCOPE_ASSERT_EQUAL(0u, mock.OutFiles.size());
  r.write("b");
  SCOPE_ASSERT_EQUAL(2u, r.size());
  SCOPE_ASSERT_EQUAL(1u, mock.OutFiles.size());
  SCOPE_ASSERT_EQUAL("whatever\na\n", mock.OutFiles[0].data);
  r.write("this is terrible");
  SCOPE_ASSERT_EQUAL(1u, mock.OutFiles.size());
  r.flush();
  SCOPE_ASSERT_EQUAL(0u, r.size());
  SCOPE_ASSERT_EQUAL(2u, mock.OutFiles.size());
  SCOPE_ASSERT_EQUAL("b\nthis is terrible\n", mock.OutFiles[1].data);
}

SCOPE_TEST(testRecordBufferOutput) {
  MockOutputWriter mock;
  RecordBuffer r("recs/my-recs", 1u, [&mock](const OutputChunk& c){ mock.OutFiles.push_back(c); });
  r.write("a record");
  r.flush();
  SCOPE_ASSERT_EQUAL(1u, mock.OutFiles.size());
  SCOPE_ASSERT_EQUAL("recs/my-recs-0001.jsonl", mock.OutFiles[0].path);
  SCOPE_ASSERT_EQUAL(9u, mock.OutFiles[0].size);
}

SCOPE_TEST(testRecordBufferDirectAccess) {
  MockOutputWriter mock;
  RecordBuffer r("your-recs", 10u, [&mock](const OutputChunk& c){ mock.OutFiles.push_back(c); });

  r.get() << "whatever\n";
  SCOPE_ASSERT_EQUAL(9u, r.size());
  SCOPE_ASSERT_EQUAL(0u, mock.OutFiles.size());
}

SCOPE_TEST(testRecordBufferDestructor) {
  MockOutputWriter mock;
  {
    RecordBuffer r("my-recs", 10u, [&mock](const OutputChunk& c){ mock.OutFiles.push_back(c); });
    r.write("whatever");
    SCOPE_ASSERT_EQUAL(0u, mock.OutFiles.size());;
  }
  SCOPE_ASSERT_EQUAL(1u, mock.OutFiles.size());;
}
