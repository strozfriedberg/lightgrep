#pragma once

#include <stack>
#include <string>

#include "jsoncons_wrapper.h"

class DirentStack {
private:
  struct Element {
    // The index of the last path separator
    size_t LastPathSepIndex;

    // The dirent record
    jsoncons::json Record;
  };

public:
  bool empty() const {
    return Stack.empty();
  }

  const jsoncons::json& top() const {
    return Stack.top().Record;
  }

  jsoncons::json& top() {
    return Stack.top().Record;
  }

  jsoncons::json pop() {
    // return the record and trim back the path
    Element& e = Stack.top();
    Path.resize(e.LastPathSepIndex);
    jsoncons::json rec{std::move(e.Record)};
    Stack.pop();
    return rec;
  }

  void push(const char* filename, jsoncons::json&& rec) {
    const size_t sep_idx = Path.length();
    Path.append("/").append(filename);

    rec["path"] = Path;
    rec["children"] = jsoncons::json(jsoncons::json_array_arg);
    rec["streams"] = jsoncons::json(jsoncons::json_array_arg);

    Stack.push({sep_idx, std::move(rec)});
  }

private:
  std::string Path;
  std::stack<Element> Stack;
};
