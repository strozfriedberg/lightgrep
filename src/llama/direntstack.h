#pragma once

#include <stack>
#include <string>

#include "jsoncons_wrapper.h"

class RecordHasher;

class DirentStack {
public:
  DirentStack(RecordHasher& rh): RecHasher(rh) {}

  bool empty() const;

  const jsoncons::json& top() const;

  jsoncons::json pop();

  void push(const std::string& filename, jsoncons::json&& rec);

  void push(const char* filename, jsoncons::json&& rec);

private:
  struct Element {
    // The index of the last path separator
    size_t LastPathSepIndex;

    // The dirent record
    jsoncons::json Record;
  };

  std::string Path;
  std::stack<Element> Stack;
  RecordHasher& RecHasher;
};
