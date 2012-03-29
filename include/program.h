#pragma once

#include <memory>
#include <vector>

#include "instructions.h"

class Program;

typedef std::shared_ptr<Program> ProgramPtr;

class Program: public std::vector<Instruction> {
public:
  Program(size_t num, const Instruction& val): std::vector<Instruction>(num, val) {}
  Program(): std::vector<Instruction>() {}

  uint32  NumChecked;

  int bufSize() const {
  	return sizeof(First) + sizeof(NumChecked) + (size() * sizeof(value_type));
  }
};
  bool operator==(const Program& rhs) const;

  std::string marshall() const;
  static ProgramPtr unmarshall(const std::string& s);
};

std::ostream& operator<<(std::ostream& out, const Program& prog);
