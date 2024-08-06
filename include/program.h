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

#include <algorithm>
#include <bitset>
#include <iterator>
#include <istream>
#include <memory>
#include <ostream>
#include <vector>

#include "basic.h"
#include "instructions.h"
#include "fwd_pointers.h"

class Program {
public:
  Program(size_t icount): Program(icount, Instruction()) {}

  Program(size_t icount, const Instruction& val):
    MaxLabel(0), MaxCheck(0), FilterOff(0), Filter(),
    IBeg(new Instruction[icount], [](Instruction* i){ delete[] i; }),
    IEnd(IBeg.get() + icount)
  {
    std::fill(IBeg.get(), IEnd, val);
  }

  uint32_t MaxLabel, MaxCheck;

  uint32_t FilterOff;
  std::bitset<256*256> Filter;

  // typedefs for container compatibility
  typedef Instruction value_type;
  typedef size_t size_type;
  typedef off_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  iterator begin() {
    return IBeg.get();
  }

  const_iterator begin() const {
    return cbegin();
  }

  const_iterator cbegin() const {
    return IBeg.get();
  }

  iterator end() {
    return IEnd;
  }

  const_iterator end() const {
    return cend();
  }

  const_iterator cend() const {
    return IEnd;
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  const_reverse_iterator rbegin() const {
    return crbegin();
  }

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(cend());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rend() const {
    return crend();
  }

  const_reverse_iterator crend() const {
    return const_reverse_iterator(cbegin());
  }

  reference front() {
    return *begin();
  }

  const_reference front() const {
    return *cbegin();
  }

  reference back() {
    return *rend();
  }

  const_reference back() const {
    return *crend();
  }

  reference operator[](size_type i) {
    return *(begin() + i);
  }

  const_reference operator[](size_type i) const {
    return *(cbegin() + i);
  }

  size_type size() const {
    return cend() - cbegin();
  }

  bool operator==(const Program& rhs) const;

  size_t bufSize() const {
    return sizeof(MaxLabel) +
           sizeof(MaxCheck) +
           sizeof(FilterOff) +
           Filter.size()/8 +
           size()*sizeof(Instruction);
  }

  std::vector<char> marshall() const;
  static ProgramPtr unmarshall(const void* buf, size_t len);

private:
  std::unique_ptr<Instruction[], void(*)(Instruction*)> IBeg;
  Instruction* IEnd;
};

std::ostream& operator<<(std::ostream& out, const Program& prog);

std::istream& operator>>(std::istream& in, Program& prog);
