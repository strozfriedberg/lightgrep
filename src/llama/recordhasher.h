#pragma once

#include "fieldhasher.h"
#include "jsoncons_wrapper.h"
#include "treehasher.h"

class RecordHasher {
public:
  FieldHash hashRun(const jsoncons::json& r);

  FieldHash hashStream(const jsoncons::json& r);

  FieldHash hashAttr(const jsoncons::json& r);

  FieldHash hashInode(const jsoncons::json& r);

  FieldHash hashDirent(const jsoncons::json& r);

private:
  TreeHasher Hasher;
};
