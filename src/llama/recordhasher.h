#pragma once

#include "fieldhasher.h"
#include "jsoncons_wrapper.h"

class RecordHasher {
public:
  FieldHash hashRun(const jsoncons::json& r);

  FieldHash hashStream(const jsoncons::json& r);

  FieldHash hashAttr(const jsoncons::json& r);

private:
  FieldHasher Hasher;
};
