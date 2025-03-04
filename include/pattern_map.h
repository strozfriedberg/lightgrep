/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
 
 #pragma once

#include <istream>
#include <memory>
#include <vector>

#include "lightgrep/api.h"

class PatternMap {
public:
  PatternMap(unsigned int sizeHint): Patterns(), Shared(false) {
    Patterns.reserve(sizeHint);
  }

  ~PatternMap() {
    clearPatterns();
  }

  PatternMap(const PatternMap& other);

  PatternMap& operator=(const PatternMap& other);

  void addPattern(const char* pattern, const char* chain, uint64_t index);

  LG_PatternInfo& operator[](size_t index);

  const LG_PatternInfo& operator[](size_t index) const;

  size_t count() const;

  size_t bufSize() const;
  std::vector<char> marshall() const;

  static std::unique_ptr<PatternMap> unmarshall(const void* buf, size_t len);

  bool operator==(const PatternMap& rhs) const;

  friend std::ostream& operator<<(std::ostream& out, const PatternMap& p);

private:
  void usePattern(const char* pattern, const char* chain, uint64_t index);

  void copyOther(const PatternMap& other);

  void clearPatterns();

  std::vector<LG_PatternInfo> Patterns;
  bool Shared;
};

bool operator==(const LG_PatternInfo& lhs, const LG_PatternInfo& rhs);

std::ostream& operator<<(std::ostream& out, const PatternMap& p);

std::ostream& operator<<(std::ostream& out, const LG_PatternInfo& pi);
