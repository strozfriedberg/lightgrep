/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
    return sizeof(Program) + size()*sizeof(Instruction);
  }

  std::vector<char> marshall() const;
  static ProgramPtr unmarshall(void* buf, size_t len);

private:
  std::unique_ptr<Instruction[], void(*)(Instruction*)> IBeg;
  Instruction* IEnd;
};

std::ostream& operator<<(std::ostream& out, const Program& prog);

std::istream& operator>>(std::istream& in, Program& prog);
