#pragma once

#include <memory>
#include <istream>
#include <ostream>
#include <vector>

#include "instructions.h"

class Program;

typedef std::shared_ptr<Program> ProgramPtr;

class Program: public std::vector<Instruction> {
public:
  Program(size_t num, const Instruction& val): std::vector<Instruction>(num, val) {}
  Program(): std::vector<Instruction>() {}

  uint32  NumChecked;

  ByteSet First;

  int bufSize() const; 

  bool operator==(const Program& rhs) const;

  std::string marshall() const;
  static ProgramPtr unmarshall(const std::string& s);
};

std::ostream& operator<<(std::ostream& out, const Program& prog);

std::istream& operator>>(std::istream& in, Program& prog);
