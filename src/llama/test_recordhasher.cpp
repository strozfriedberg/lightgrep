#include <scope/test.h>

#include "hex.h"
#include "recordhasher.h"

SCOPE_TEST(testHashRun) {
  RecordHasher hasher;

  const jsoncons::json r(
    jsoncons::json_object_arg,
    {
      { "offset", 1 },
      { "addr", 2 },
      { "len", 3 },
      { "flags", "Checkered" }
    }
  );

  const FieldHash exp{{
    0x23, 0x9c, 0xf4, 0xfc, 0x42, 0xa4, 0xac, 0xad,
    0xfd, 0x62, 0x75, 0xa5, 0xef, 0x32, 0x85, 0x49,
    0xe8, 0x06, 0xef, 0x37, 0x59, 0xae, 0x57, 0x7f,
    0xc9, 0xed, 0xe0, 0x9f, 0x7a, 0xd3, 0xe8, 0x7c
  }};

  SCOPE_ASSERT_EQUAL(exp, hasher.hashRun(r));
}

SCOPE_TEST(testHashStream) {
  RecordHasher hasher;

  const jsoncons::json r(
    jsoncons::json_object_arg,
    {
      { "id", 1 },
      { "type", 2 },
      { "size", 3 },
      { "name", "Bob" },
      { "flags", "Red" },
      { "data_id", "!#$%^" }
    }
  );

  const FieldHash exp{{
    0x97, 0x05, 0x62, 0x22, 0x33, 0x5b, 0x6b, 0x29,
    0x5b, 0xae, 0xd1, 0xc6, 0xab, 0xa0, 0x8d, 0x22,
    0xa6, 0x37, 0x6d, 0xea, 0x24, 0x67, 0xc7, 0xa9,
    0x4a, 0x71, 0xfb, 0xaf, 0x87, 0x6b, 0x53, 0x3d, 
  }};

  SCOPE_ASSERT_EQUAL(exp, hasher.hashStream(r));  
}

SCOPE_TEST(testHashAttr) {
  RecordHasher hasher;

  const jsoncons::json sr(
    jsoncons::json_object_arg,
    {
      { "id", 1 },
      { "type", 2 },
      { "size", 3 },
      { "name", "Bob" },
      { "flags", "Red" },
      { "data_id", "!#$%^" }
    }
  );

  const jsoncons::json nrds(
    jsoncons::json_array_arg,
    {
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "offset", 1 },
          { "addr", 2 },
          { "len", 3 },
          { "flags", "abc" }
        }
      ),
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "offset", 4 },
          { "addr", 5 },
          { "len", 6 },
          { "flags", "def" }
        }
      ),
      jsoncons::json(
        jsoncons::json_object_arg,
        {
          { "offset", 7 },
          { "addr", 8 },
          { "len", 9 },
          { "flags", "ghi" }
        }
      )
    }
  );

  const uint8_t buf[20] = { 0xFE };

  const jsoncons::json r = jsoncons::json( 
    jsoncons::json_object_arg,
    {
      { "stream", sr },
      { "init_size", 1 },
      { "comp_size",  2 },
      { "rd_buf_size", 20 },
      { "rd_buf", hexEncode(buf, sizeof(buf)) },
      { "skip_len", 5 },
      { "alloc_size", 6 },
      { "nrds", nrds } 
    }
  );
 
  const FieldHash exp{{
    0x97, 0x05, 0x62, 0x22, 0x33, 0x5b, 0x6b, 0x29,
    0x5b, 0xae, 0xd1, 0xc6, 0xab, 0xa0, 0x8d, 0x22,
    0xa6, 0x37, 0x6d, 0xea, 0x24, 0x67, 0xc7, 0xa9,
    0x4a, 0x71, 0xfb, 0xaf, 0x87, 0x6b, 0x53, 0x3d, 
  }};

  SCOPE_ASSERT_EQUAL(exp, hasher.hashAttr(r));  
}
