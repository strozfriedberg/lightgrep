#pragma once

#include "instructions.h"
#include "skiptable.h"


class Program: public std::vector<Instruction> {
public:
  Program(size_t num, const Instruction& val): std::vector<Instruction>(num, val) {}
  Program(): std::vector<Instruction>() {}

  uint32  NumChecked;
  
  boost::shared_ptr<SkipTable> Skip;
  ByteSet First;
};

typedef boost::shared_ptr<Program> ProgramPtr;

std::ostream& operator<<(std::ostream& out, const Program& prog);
