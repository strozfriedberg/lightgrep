#include <scope/test.h>

#include "direntstack.h"
#include "recordhasher.h"

SCOPE_TEST(testDirentStackStartsEmpty) {
  RecordHasher rh;
  DirentStack dirents(rh);
  SCOPE_ASSERT(dirents.empty());
}

SCOPE_TEST(testDirentStackPushPop) {
  RecordHasher rh;
  DirentStack dirents(rh);

  jsoncons::json in(
    jsoncons::json_object_arg,
    {
      { "foo", "bar" },
      { "type", "whatever" }
    }
  );
  
  dirents.push("filename", std::move(in));
  
  SCOPE_ASSERT(!dirents.empty());
  SCOPE_ASSERT_EQUAL("filename", dirents.top()["path"]);
  
  const jsoncons::json exp_out(
    jsoncons::json_object_arg,
    {
      { "foo", "bar" },
      { "children", jsoncons::json_array_arg },
      { "streams", jsoncons::json_array_arg },
      { "hash", "2cf245061b41742690f0ebe9eceba6d8763d24d948f8969cae2071412bbc610e" },
      { "path", "filename" },
      { "type", "whatever" },
    }
  );

  SCOPE_ASSERT_EQUAL(exp_out, dirents.pop());
}

SCOPE_TEST(testDirentStackPushPushPopPop) {
  RecordHasher rh;
  DirentStack dirents(rh);

  SCOPE_ASSERT(dirents.empty());

  jsoncons::json a(
    jsoncons::json_object_arg,
    {
      { "foo", "bar" },
      { "type", "whatever" }
    }
  );
  
  dirents.push("a", std::move(a));
  
  SCOPE_ASSERT(!dirents.empty());
  SCOPE_ASSERT_EQUAL("a", dirents.top()["path"]);

  jsoncons::json b(
    jsoncons::json_object_arg,
    {
      { "foo", "baz" },
      { "type", "whatever" }
    }
  );
 
  dirents.push("b", std::move(b));

  SCOPE_ASSERT(!dirents.empty());
  SCOPE_ASSERT_EQUAL("a/b", dirents.top()["path"]);

  const jsoncons::json exp_out_b(
    jsoncons::json_object_arg,
    {
      { "foo", "baz" },
      { "children", jsoncons::json_array_arg },
      { "streams", jsoncons::json_array_arg },
      { "hash", "d41f36222eabcc685f01bbd288b60b66ff41dc4b52c69ba4a5126a74b4489ac7" },
      { "path", "a/b" },
      { "type", "whatever" },
    }
  );

  SCOPE_ASSERT_EQUAL(exp_out_b, dirents.pop());

  SCOPE_ASSERT(!dirents.empty());
  SCOPE_ASSERT_EQUAL("a", dirents.top()["path"]);

  const jsoncons::json exp_out_a(
    jsoncons::json_object_arg,
    {
      { "foo", "bar" },
      {
        "children",
        jsoncons::json(
          jsoncons::json_array_arg,
          { "d41f36222eabcc685f01bbd288b60b66ff41dc4b52c69ba4a5126a74b4489ac7" }
        )
      },
      { "streams", jsoncons::json_array_arg },
      { "hash", "0907b14d225552a966673312558b413135edd21d0460164141a1f74274f3281a" },
      { "path", "a" },
      { "type", "whatever" },
    }
  );

  SCOPE_ASSERT_EQUAL(exp_out_a, dirents.pop());
  SCOPE_ASSERT(dirents.empty());
}
