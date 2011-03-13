#pragma once

#include "basic.h"
#include <limits>

#include "instructions.h"

struct Thread {
  Thread():
    PC(0),
    Label(std::numeric_limits<uint32>::max()),
    #ifdef LBT_TRACE_ENABLED
    Id(0),
    #endif
    Start(0),
    End(std::numeric_limits<uint64>::max()) {}

  #ifdef LBT_TRACE_ENABLED
  Thread(const Instruction* pc, uint32 label,
         uint64 id, uint64 start, uint64 end):
    PC(pc),
    Label(label),
    Id(id),
    Start(start),
    End(end) {}
  #endif

  Thread(const Instruction* pc, uint32 label, uint64 start, uint64 end):
    PC(pc),
    Label(label),
    Start(start),
    End(end) {}

  Thread(const Instruction* pc, const Thread& parent):
    PC(pc),
    Label(parent.Label),
    #ifdef LBT_TRACE_ENABLED
    Id(parent.Id),
    #endif
    Start(parent.Start),
    End(parent.End) {}

  Thread(const Instruction* pc):
    PC(pc),
    Label(std::numeric_limits<uint32>::max()),
    #ifdef LBT_TRACE_ENABLED
    Id(0),
    #endif
    Start(0),
    End(std::numeric_limits<uint64>::max()) {}

  Thread(const Thread& t):
    PC(t.PC),
    Label(t.Label),
    #ifdef LBT_TRACE_ENABLED
    Id(t.Id),
    #endif
    Start(t.Start),
    End(t.End) {}

  #ifdef LBT_TRACE_ENABLED
  void init(const Instruction* pc, uint32 label,
            uint64 id, uint64 start, uint64 end) {
    PC = pc;
    Id = id;
    Label = label;
    Start = start;
    End = end;
  }
  #endif

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

  void advance(uint32 size) {
    PC += size;
  }

  void advance() {
    PC += PC->wordSize();
  }

  const Instruction* PC;
  uint32             Label;
  #ifdef LBT_TRACE_ENABLED
  uint64             Id;
  #endif
  uint64             Start,
                     End;

  #ifdef LBT_TRACE_ENABLED
  enum ThreadLife {
    BORN = 1,
    PRERUN = 2,
    POSTRUN = 4,
    DIED = 8
  };

  void output_json(std::ostream& out, const Instruction* base, byte state) const;
  #endif

  bool operator==(const Thread& x) const {
    return PC == x.PC && Label == x.Label &&
           Start == x.Start && End == x.End;
  }
};

std::ostream& operator<<(std::ostream& out, const Thread& t);
