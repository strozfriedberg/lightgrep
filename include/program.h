#pragma once

#include <memory>
#include <vector>

#include "instructions.h"

class Program: public std::vector<Instruction> {
public:
  Program(size_t num, const Instruction& val): std::vector<Instruction>(num, val) {}
  Program(): std::vector<Instruction>() {}

  uint32  NumChecked;

  ByteSet First;

  int bufSize() const {
  	return sizeof(First) + sizeof(NumChecked) + (size() * sizeof(value_type));
  }
};

typedef std::shared_ptr<Program> ProgramPtr;

std::ostream& operator<<(std::ostream& out, const Program& prog);
