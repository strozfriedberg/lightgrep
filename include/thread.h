#pragma once

#include "basic.h"
#include <limits>

#include "instructions.h"

struct Thread {
  Thread(): PC(0), Label(std::numeric_limits<uint32>::max()), Start(0), End(std::numeric_limits<uint64>::max()) {}
  Thread(const Instruction* pc, uint32 label, uint64 start, uint64 end): PC(pc), Label(label), Start(start), End(end) {}
  Thread(const Instruction* pc, const Thread& parent): PC(pc), Label(parent.Label), Start(parent.Start), End(parent.End) {}
  Thread(const Instruction* pc): PC(pc), Label(std::numeric_limits<uint32>::max()), Start(0), End(std::numeric_limits<uint64>::max()) {}

  void init(const Instruction* pc, uint32 label, uint64 start, uint64 end) {
    PC = pc;
    Label = label;
    Start = start;
    End = end;
  }

  void init(const Instruction* base, uint64 start) {
    PC = base;
    Start = start;
  }

  void jump(const Instruction* base, uint32 offset) {
    PC = base;
    PC += offset;
  }

  void fork(const Thread& parent, const Instruction* base, uint32 offset) {
    *this = parent;
    jump(base, offset);
  }

  void advance() {
    PC += PC->wordSize();
  }

  const Instruction* PC;
  uint32             Label;
  uint64             Start,
                     End;
  
  #ifdef LBT_TRACE_ENABLED
  static uint64 NextId;
  uint64 Id;

  enum ThreadLife {
    BORN,
    PRERUN,
    POSTRUN,
    DEAD
  };

  void output_json(std::ostream& out, const Instruction* base, ThreadLife state) const;
  #endif

  bool operator==(const Thread& x) const {
    return PC == x.PC && Label == x.Label && Start == x.Start && End == x.End;
  }
};

std::ostream& operator<<(std::ostream& out, const Thread& t);
