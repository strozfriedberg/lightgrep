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
    0x96, 0xf3, 0x98, 0x38, 0x19, 0x1b, 0x52, 0x2e,
    0x00, 0x35, 0x1e, 0xc2, 0x21, 0x10, 0x4f, 0xab,
    0x1b, 0xcb, 0x94, 0x98, 0xef, 0xed, 0x56, 0x72,
    0x1f, 0x4f, 0x73, 0xfb, 0xea, 0xd0, 0x33, 0xf9
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
    0xd4, 0xb4, 0xec, 0xcc, 0x4f, 0xe0, 0xb3, 0xe0,
    0xed, 0x96, 0x89, 0x20, 0x5d, 0xef, 0x9d, 0xaa,
    0x70, 0xf4, 0x42, 0xbd, 0x1a, 0x09, 0x0d, 0x11,
    0xc6, 0x83, 0x64, 0xd7, 0x80, 0x56, 0x52, 0x24
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
    0x91, 0x1c, 0x38, 0xe6, 0x84, 0x69, 0x98, 0xc3,
    0xac, 0xaf, 0xef, 0x58, 0xf0, 0x2e, 0xc1, 0xfc,
    0xe0, 0x91, 0x2a, 0xdc, 0x35, 0xf6, 0xc6, 0xbf,
    0x01, 0x51, 0xfb, 0x44, 0x7f, 0x8d, 0x37, 0x54
  }};

  SCOPE_ASSERT_EQUAL(exp, hasher.hashAttr(r));  
}

SCOPE_TEST(testHashInode) {
  RecordHasher hasher;

  const std::string in = R"(
{
  "addr": 562,
  "flags": "Allocated, Used",
  "link": "",
  "nlink": 1,
  "seq": 0,
  "type": "File",
  "uid": "0",
  "gid": "0",
  "attrs": [
    {
      "stream": {
        "id": 0,
        "flags": "In Use,Non-resident",
        "name": "",
        "size": 1404014,
        "type": 1,
        "data_id": ""
      },
      "alloc_size": 1409024,
      "comp_size": 0,
      "init_size": 1404014,
      "skip_len": 0,
      "rd_buf": "",
      "rd_buf_size": 0,
      "nrds": [
        {
          "addr": 35984,
          "flags": "",
          "len": 2752,
          "offset": 0
        }
      ]
    }
  ],
  "timestamps": {
    "created": "2009-04-30 15:35:16.3",
    "modified": "2009-04-29 09:00:24",
    "accessed": "2015-02-09 00:00:00"
  }
})";

  const jsoncons::json r = jsoncons::json::parse(in);

  const FieldHash exp{{
    0x33, 0x32, 0x8c, 0x75, 0xc5, 0xa0, 0x85, 0x6f,
    0xe7, 0x3a, 0x66, 0xd0, 0xa7, 0x50, 0x1d, 0xd7,
    0xc8, 0x60, 0xbb, 0xbb, 0xb9, 0xc3, 0x34, 0x85,
    0x49, 0x45, 0xee, 0xf2, 0x3d, 0x39, 0xcf, 0x9c
  }};

  SCOPE_ASSERT_EQUAL(exp, hasher.hashInode(r));  
}

SCOPE_TEST(testHashPath) {
  RecordHasher hasher;

  const jsoncons::json r(
    jsoncons::json_object_arg,
    {
      { "path", "foo/bar" }
    }
  );

  const FieldHash exp{{
    0x33, 0x32, 0x8c, 0x75, 0xc5, 0xa0, 0x85, 0x6f,
    0xe7, 0x3a, 0x66, 0xd0, 0xa7, 0x50, 0x1d, 0xd7,
    0xc8, 0x60, 0xbb, 0xbb, 0xb9, 0xc3, 0x34, 0x85,
    0x49, 0x45, 0xee, 0xf2, 0x3d, 0x39, 0xcf, 0x9c
  }};

  SCOPE_ASSERT_EQUAL(exp, hasher.hashPath(r));  
}

SCOPE_TEST(testHashDirent) {
  RecordHasher hasher;

  const std::string in = R"(
{
  "type": "File",
  "flags": "",
  "path_id": "ed3cd7003653d8512b71d473a56127c558be82a1e057ba595fb406d10bbcc0b6" ,
  "streams": [
    "33328c75c5a0856fe73a66d0a7501dd7c860bbbbb9c334854945eef23d39cf9c", 
    "8f3a29581a930c5f89698e819e40c8edf08391d5bb0ca8664b62291cbe30686f"
  ],
  "children": [
    "3c3b55265bc4ebb040da923cbdcd81ee0ab1250e0d1775d5e57caed9bf272b48",
    "04ad441d5836a5ddff1f7da179e9be462f58b5ad9647508715af3283b4e42611"
  ]
}
)";

  const jsoncons::json r = jsoncons::json::parse(in);

  const FieldHash exp{{
    0x33, 0x32, 0x8c, 0x75, 0xc5, 0xa0, 0x85, 0x6f,
    0xe7, 0x3a, 0x66, 0xd0, 0xa7, 0x50, 0x1d, 0xd7,
    0xc8, 0x60, 0xbb, 0xbb, 0xb9, 0xc3, 0x34, 0x85,
    0x49, 0x45, 0xee, 0xf2, 0x3d, 0x39, 0xcf, 0x9c
  }};

  SCOPE_ASSERT_EQUAL(exp, hasher.hashDirent(r));
}


