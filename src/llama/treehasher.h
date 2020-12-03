#pragma once

#include "fieldhasher.h"

#include <stack>

class TreeHasher;

class HasherHolder {
public:
  HasherHolder(TreeHasher& th);

  ~HasherHolder(); 

private:
  TreeHasher& th;
};

class TreeHasher {
public:
  TreeHasher() = default;

  TreeHasher(const TreeHasher&) = delete;
  
  TreeHasher(TreeHasher&&) = default;

  TreeHasher& operator=(const TreeHasher&) = delete;

  TreeHasher& operator=(TreeHasher&&) = default;

  FieldHasher& push() {
    if (Spares.empty()) {
      InUse.emplace();
    }
    else {
      InUse.push(std::move(Spares.top()));
      Spares.pop();
    }
    return InUse.top();
  }

  FieldHasher& pop() {
    InUse.top().reset();
    Spares.push(std::move(InUse.top()));
    InUse.pop();
    return InUse.top();  
  }

  template <typename...Args>
  FieldHash hash(Args&&... args) {
    return InUse.top().hash(std::forward<Args>(args)...);
  }

  template <typename... Args>
  FieldHasher& hash_em(Args&&... args) {
    return InUse.top().hash_em(std::forward<Args>(args)...);
  }

  FieldHash get_hash() {
    return InUse.top().get_hash();
  }

  HasherHolder subhash() {
    return HasherHolder(*this);
  }

private:
  std::stack<FieldHasher> InUse, Spares;
};
