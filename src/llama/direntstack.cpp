#include "direntstack.h"
#include "hex.h"
#include "recordhasher.h"

bool DirentStack::empty() const {
  return Stack.empty();
}

const jsoncons::json& DirentStack::top() const {
  return Stack.top().Record;
}

jsoncons::json DirentStack::pop() {
  // pop the record and trim back the path
  Element& e = Stack.top();
  Path.resize(e.LastPathSepIndex);
  jsoncons::json rec{std::move(e.Record)};
  Stack.pop();

  // hash the record
  const FieldHash fhash{RecHasher.hashDirent(rec)};
  std::string hash = hexEncode(&fhash.hash, sizeof(fhash.hash));

  // add the hash to the parent, if any
  if (!Stack.empty()) {
    Stack.top().Record["children"].push_back(hash);
  }

  // put the hash into the record
  rec["hash"] = std::move(hash);

  return rec;
}

void DirentStack::push(const std::string& filename, jsoncons::json&& rec) {
  push(filename.c_str(), std::move(rec));
}

void DirentStack::push(const char* filename, jsoncons::json&& rec) {
  const size_t sep_idx = Path.length();
  if (sep_idx > 0) {
    Path.append("/");
  }
  Path.append(filename);

  rec["path"] = Path;
  rec["children"] = jsoncons::json(jsoncons::json_array_arg);
  rec["streams"] = jsoncons::json(jsoncons::json_array_arg);

  Stack.push({sep_idx, std::move(rec)});
}
