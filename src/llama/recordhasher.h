#pragma once

#include "fieldhasher.h"
#include "jsoncons_wrapper.h"

struct AttrRecord;
struct RunRecord;
struct StreamRecord;

class RecordHasher {
public:
  FieldHash hash(const RunRecord& r);

  FieldHash hash(const StreamRecord& r);

  FieldHash hash(const AttrRecord& r);

  FieldHash hashRun(const jsoncons::json& r);

  FieldHash hashStream(const jsoncons::json& r);

  FieldHash hashAttr(const jsoncons::json& r);

private:
  FieldHasher Hasher;
};
