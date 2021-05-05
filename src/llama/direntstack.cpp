#include "direntstack.h"

bool DirentStack::empty() const {
  return Stack.empty();
}

const jsoncons::json& DirentStack::top() const {
  return Stack.top().Record;
}

jsoncons::json& DirentStack::top() {
  return Stack.top().Record;
}

jsoncons::json DirentStack::pop() {
  // return the record and trim back the path
  Element& e = Stack.top();
  Path.resize(e.LastPathSepIndex);
  jsoncons::json rec{std::move(e.Record)};
  Stack.pop();
  return rec;
}

void DirentStack::push(const std::string& filename, jsoncons::json&& rec) {
  push(filename.c_str(), std::move(rec));
}

void DirentStack::push(const char* filename, jsoncons::json&& rec) {
  const size_t sep_idx = Path.length();
  Path.append("/").append(filename);

  rec["path"] = Path;
  rec["children"] = jsoncons::json(jsoncons::json_array_arg);
  rec["streams"] = jsoncons::json(jsoncons::json_array_arg);

  Stack.push({sep_idx, std::move(rec)});
}
