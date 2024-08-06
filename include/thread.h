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

#include "basic.h"
#include "instructions.h"

struct Thread {
  static const uint32_t NOLABEL;
  static const uint64_t NONE;

  Thread(): Thread(nullptr, NOLABEL, 0, NONE) {}

  Thread(const Instruction* pc): Thread(pc, NOLABEL, 0, NONE) {}

  Thread(const Instruction* pc, uint32_t label, uint64_t start, uint64_t end):
    PC(pc),
    Start(start),
    End(end),
    #ifdef LBT_TRACE_ENABLED
    Id(0),
    #endif
    Label(label),
    Lead(false) {}

  #ifdef LBT_TRACE_ENABLED
  Thread(const Instruction* pc, uint32_t label,
         uint64_t id, uint64_t start, uint64_t end):
    PC(pc),
    Start(start),
    End(end),
    Id(id),
    Label(label),
    Lead(false) {}
  #endif

  void jump(const Instruction* base, uint32_t offset) {
    PC = base + offset;
  }

  void fork(const Thread& parent, const Instruction* base, uint32_t offset) {
    *this = parent;
    jump(base, offset);
  }

  void advance(uint32_t size) {
    PC += size;
  }

  void advance() {
    PC += PC->wordSize();
  }

  const Instruction* PC;
  uint64_t Start, End;
  #ifdef LBT_TRACE_ENABLED
  uint64_t Id;
  #endif
  uint32_t Label;
  bool Lead;

//  uint32_t Dummy;

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

