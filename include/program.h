#pragma once

#include <istream>
#include <ostream>
#include <vector>

#include "basic.h"
#include "instructions.h"
#include "fwd_pointers.h"
#include "byteset.h"

class Program: public std::vector<Instruction> {
public:
  Program(size_t num, const Instruction& val):
    std::vector<Instruction>(num, val), NumChecked(0), First() {}

  Program(): std::vector<Instruction>(), NumChecked(0), First() {}

  uint32  NumChecked;

  ByteSet First;

  int bufSize() const;

  bool operator==(const Program& rhs) const;

  std::string marshall() const;
  static ProgramPtr unmarshall(const std::string& s);
};

std::ostream& operator<<(std::ostream& out, const Program& prog);

std::istream& operator>>(std::istream& in, Program& prog);
