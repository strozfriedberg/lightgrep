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

#include "byteset.h"
#include "container_out.h"
#include "vm.h"
#include "program.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"PC\":" << std::hex << t.PC
      << ", \"Label\":" << std::dec << t.Label
      #ifdef LBT_TRACE_ENABLED
      << ", \"Id\":" << t.Id
      #endif
      << ", \"Start\":" << t.Start
      << ", \"End\":" << t.End << " }";
  return out;
}

#ifdef LBT_TRACE_ENABLED

void Vm::open_init_epsilon_json(std::ostream& out) {
  if (BeginDebug == 0) {
    out << "{\"offset\":-1, \"byte\":0, \"num\":0, \"list\":[";
    first_thread_json = true;
  }
}

void Vm::close_init_epsilon_json(std::ostream& out) const {
  close_frame_json(out, 0);
}

void Vm::open_frame_json(std::ostream& out, uint64_t offset, const byte* const cur) {
  if (BeginDebug <= offset && offset < EndDebug) {
    out << "{\"offset\":" << offset << ", \"byte\":" << (uint32_t) *cur
        << ", \"num\":" << Active.size() << ", \"list\":[";
    first_thread_json = true;
  }
}

void Vm::close_frame_json(std::ostream& out, uint64_t offset) const {
  if (BeginDebug <= offset && offset < EndDebug) {
    out << "]}" << std::endl;
  }
}

void Vm::pre_run_thread_json(std::ostream& out, uint64_t offset,
                             const Thread& t, const Instruction* const base) {
  if (BeginDebug <= offset && offset < EndDebug) {
    byte state = Thread::PRERUN;

    if (new_thread_json.erase(t.Id)) {
      state |= Thread::BORN;
    }

    thread_json(out, t, base, state);
  }
}

void Vm::post_run_thread_json(std::ostream& out, uint64_t offset,
                              const Thread& t, const Instruction* const base) {
  if (BeginDebug <= offset && offset < EndDebug) {
    byte state = Thread::POSTRUN;
    if (!t.PC)  {
      state |= Thread::DIED;
    }

    thread_json(out, t, base, state);
  }
}

void Vm::thread_json(std::ostream& out, const Thread& t,
                     const Instruction* const base, byte state) {
  // put commas between consecutive threads
  if (first_thread_json) {
    first_thread_json = false;
  }
  else {
    out << ", ";
  }

  t.output_json(out, base, state);
}

void Thread::output_json(std::ostream& out, const Instruction* const base, byte state) const {
  out << "{ \"Id\":" << Id
      << ", \"PC\":" << (PC ? PC - base : -1)
      << ", \"Label\":" << Label
      << ", \"Start\":" << Start
      << ", \"End\":" << End
      << ", \"state\":" << (uint32_t) state
      << ", \"op\":" << (PC ? PC->OpCode : 0)
      << " }";
}
#endif

std::shared_ptr<VmInterface> VmInterface::create(ProgramPtr prog) {
  return std::shared_ptr<VmInterface>(new Vm(prog));
}

Vm::Vm(ProgramPtr prog):
  #ifdef LBT_TRACE_ENABLED
  BeginDebug(Thread::NONE), EndDebug(Thread::NONE), NextId(0),
  #endif
  Prog(prog), ProgEnd(&prog->back()-1),
  First(), Active(1, &(*prog)[0]), Next(),
  CheckLabels(prog->MaxCheck+1),
  LiveNoLabel(false), Live(prog->MaxLabel+1),
  MatchEnds(prog->MaxLabel+1), MatchEndsMax(0),
  CurHitFn(nullptr), UserData(nullptr)
{
// FIXME: should do these checks inside SparseSet::resize()?
  if (Live.size() > Live.max_size()) {
    throw std::runtime_error("Too many patterns.");
  }

  if (CheckLabels.size() > CheckLabels.max_size()) {
    throw std::runtime_error("Too many checked states.");
  }

  ThreadList::iterator t(Active.begin());

  #ifdef LBT_TRACE_ENABLED
  open_init_epsilon_json(std::clog);
  new_thread_json.insert(Active.front().Id);
  pre_run_thread_json(std::clog, 0, Active.front(), &(*Prog)[0]);
  #endif

  if (_executeEpSequence<0>(&(*Prog)[0], t, 0)) {
    Next.push_back(*t);
  }

  #ifdef LBT_TRACE_ENABLED
  post_run_thread_json(std::clog, 0, Active.front(), &(*Prog)[0]);
  close_init_epsilon_json(std::clog);
  #endif

  First.swap(Next);

  reset();
}

void Vm::reset() {
  Active.clear();
  Next.clear();

  CheckLabels.clear();

  LiveNoLabel = false;
  Live.clear();

  MatchEnds.assign(MatchEnds.size(), 0);
  MatchEndsMax = 0;

  CurHitFn = nullptr;

  #ifdef LBT_TRACE_ENABLED
  NextId = 1;
  #endif
}

inline void Vm::_markLive(const uint32_t label) {
  if (label == Thread::NOLABEL) {
    LiveNoLabel = true;
  }
  else if (!Live.find(label)) {
    Live.insert(label);
  }
}

inline bool Vm::_execute(const Instruction* const base, ThreadList::iterator t, const byte* const cur) const {
  const Instruction& instr = *t->PC;

  switch (instr.OpCode) {
  case JUMP_TABLE_RANGE_OP:
    if (instr.Op.T2.First <= *cur && *cur <= instr.Op.T2.Last) {
      const uint32_t addr = *reinterpret_cast<const uint32_t* const>(t->PC + 1 + (*cur - instr.Op.T2.First));
      if (addr != 0xFFFFFFFF) {
        t->jump(base, addr);
        return true;
      }
    }
    break;

  case BYTE_OP:
    if ((*cur == instr.Op.T1.Byte) ^ (instr.Op.T1.Flags & Instruction::NEGATE)) {
      t->advance(InstructionSize<BYTE_OP>::VAL);
      return true;
    }
    break;

  case BIT_VECTOR_OP:
    if ((*reinterpret_cast<const ByteSet* const>(t->PC + 1))[*cur]) {
      t->advance(InstructionSize<BIT_VECTOR_OP>::VAL);
      return true;
    }
    break;

  case EITHER_OP:
    if ((*cur == instr.Op.T2.First || *cur == instr.Op.T2.Last) ^ (instr.Op.T2.Flags & Instruction::NEGATE)) {
      t->advance(InstructionSize<EITHER_OP>::VAL);
      return true;
    }
    break;

  case RANGE_OP:
    if ((instr.Op.T2.First <= *cur && *cur <= instr.Op.T2.Last) ^ (instr.Op.T2.Flags & Instruction::NEGATE)) {
      t->advance(InstructionSize<RANGE_OP>::VAL);
      return true;
    }
    break;

  case ANY_OP:
    t->advance(InstructionSize<ANY_OP>::VAL);
    return true;

  case FINISH_OP:
    return true;
  }

  // Die.
  return false;
}

inline bool Vm::_liveCheck(const uint64_t start, const uint32_t label) const {
  if (label == Thread::NOLABEL) {
    // if we're unlabeled, and anything live has priority, we're blocked
    // if we're unlabeled and we overlap any matches, we're blocked
    return !Next.empty() || start < MatchEndsMax;
  }
  else {
    // if we're labeled and an unlabeled or same-labeled thread has
    // priority, we're blocked
    return LiveNoLabel || Live.find(label);
  }
}

// while base is always == &Program[0], we pass it in because it then should get inlined away
template <uint32_t X>
inline bool Vm::_executeEpsilon(const Instruction* const base, ThreadList::iterator t, const uint64_t offset) {
  const Instruction& instr = *t->PC;

  switch (instr.OpCode) {
  case FINISH_OP:
    {
      const uint32_t tLabel = t->Label;
      const uint64_t tStart = t->Start;
      const uint64_t tEnd = t->End;

      if (tEnd == offset) {
        ThreadList::iterator i(t+1);
        const ThreadList::const_iterator e(Active.end());

        if (t->Lead) {
          // we are the lead thread; kill all same-labeled threads
          for ( ; i != e; ++i) {
            if (i->Label == tLabel) {
              // DIE. Penultimate instruction is always a halt
              i->PC = ProgEnd;
            }
          }
        }
        else {
          // we are not lead; kill all same-labeled, same-start threads
          for ( ; i != e && i->Start == tStart; ++i) {
            if (i->Label == tLabel) {
              // DIE. Penultimate instruction is always a halt
              i->PC = ProgEnd;
            }
          }
        }
      }

      if (!LiveNoLabel && !Live.find(tLabel)) {
        if (tStart >= MatchEnds[tLabel]) {
          MatchEnds[tLabel] = tEnd + 1;

          if (tEnd + 1 > MatchEndsMax) {
            MatchEndsMax = tEnd + 1;
          }

          if (CurHitFn) {
            const SearchHit hit(tStart, tEnd + 1, tLabel);
            (*CurHitFn)(UserData, &hit);
          }
        }

        t->PC = 0;
      }

      return false;
    }

  case FORK_OP:
    {
      Thread f = *t;
      t->advance(InstructionSize<FORK_OP>::VAL);

      // recurse to keep going in sequence
      if (_executeEpSequence<X == 0 ? 0 : X-1>(base, t, offset)) {
        _markLive(t->Label);
        Next.push_back(*t);
      }

      // Now back up to the fork, fall through to handle it as a longjump.
      // Note that the forked child is taking the parent's place in Active.
      // This is ESSENTIAL for maintaining correct thread priority order.
      *t = f;

      #ifdef LBT_TRACE_ENABLED
      new_thread_json.insert(t->Id = NextId++);
      #endif
    }

  case JUMP_OP:
    t->jump(base, *reinterpret_cast<const uint32_t* const>(t->PC+1));
    return true;

  case CHECK_HALT_OP:
    {
      if (CheckLabels.find(instr.Op.Offset)) {
        // another thread has the lock, we die
        t->PC = 0;
        return false;
      }
      else if (!_liveCheck(t->Start, t->Label)) {
        // nothing blocks us, we take the lock
        CheckLabels.insert(instr.Op.Offset);
      }

      t->advance(InstructionSize<CHECK_HALT_OP>::VAL);
      return true;
    }

  case LABEL_OP:
    {
      const uint32_t label = instr.Op.Offset;
      if (t->Start >= MatchEnds[label]) {
        t->Label = label;
        t->advance(InstructionSize<LABEL_OP>::VAL);
        return true;
      }
      else {
        t->PC = 0;
        return false;
      }
    }

  case MATCH_OP:
    t->End = offset;
    t->advance(InstructionSize<MATCH_OP>::VAL);
    t->Lead = !LiveNoLabel && !Live.find(t->Label);
    return true;

  case HALT_OP:
    // die, motherfucker, die
    t->PC = 0;
    return false;
  }

  return false;
}

inline void Vm::_executeThread(const Instruction* const base, ThreadList::iterator t, const byte* const cur, const uint64_t offset) {
  #ifdef LBT_TRACE_ENABLED
  pre_run_thread_json(std::clog, offset, *t, base);
  const bool alive = _execute(base, t, cur);
  post_run_thread_json(std::clog, offset, *t, base);

  if (alive && _executeEpSequence<10>(base, t, offset)) {
    _markLive(t->Label);
    Next.push_back(*t);
  }
  #else
  if (_execute(base, t, cur) && _executeEpSequence<10>(base, t, offset)) {
    _markLive(t->Label);
    Next.push_back(*t);
  }
  #endif
}

template <uint32_t X>
inline bool Vm::_executeEpSequence(const Instruction* const base, ThreadList::iterator t, const uint64_t offset) {

  // kill threads overlapping an emitted match
  if (t->Label != Thread::NOLABEL && t->Start < MatchEnds[t->Label]) {
    return false;
  }

  #ifdef LBT_TRACE_ENABLED
  bool ex;
  do {
    const uint64_t id = t->Id; // t can change on a fork, we want the original
    pre_run_thread_json(std::clog, offset, *t, base);
    ex = _executeEpsilon<X>(base, t, offset);
//std::cerr << "\nNext.size() == " << Next.size() << std::endl;

    if (t->Id == id) {
      post_run_thread_json(std::clog, offset, *t, base);
    }
    else if (!Next.empty() && Next.back().Id == id) {
      post_run_thread_json(std::clog, offset, Next.back(), base);
    }
/*
    const Thread& x = t->Id == id ? *t : Next.back();
    post_run_thread_json(std::cerr, offset, x, base);
*/
  } while (ex);
  #else
  while (_executeEpsilon<X>(base, t, offset)) ;
  #endif

  return t->PC;
}

inline void Vm::_executeNewThreads(const Instruction* const base, ThreadList::iterator t, const byte* const cur, const uint64_t offset) {
  const size_t oldsize = Active.size();

  for (t = First.begin(); t != First.end(); ++t) {
    Active.emplace_back(
      t->PC, Thread::NOLABEL,
      #ifdef LBT_TRACE_ENABLED
      NextId++,
      #endif
      offset, Thread::NONE
    );

    #ifdef LBT_TRACE_ENABLED
    new_thread_json.insert(Active.back().Id);
    #endif
  }

  for (t = Active.begin() + oldsize; t != Active.end(); ++t) {
    _executeThread(base, t, cur, offset);
    // ++count;
  }
}

inline void Vm::_executeFrame(const std::bitset<256*256>& filter, ThreadList::iterator t, const Instruction* const base, const byte* const cur, const uint64_t offset) {
  // run old threads at this offset
  // uint32_t count = 0;

  for ( ; t != Active.end(); ++t) {
    _executeThread(base, t, cur, offset);
    // ++count;
  }

  // create new threads at this offset
  if (filter[*reinterpret_cast<const uint16_t* const>(cur+Prog->FilterOff)]) {
    _executeNewThreads(base, t, cur, offset);
  }
  // ThreadCountHist.resize(count + 1, 0);
  // ++ThreadCountHist[count];
}

inline void Vm::_executeFrame(ThreadList::iterator t, const Instruction* const base, const byte* const cur, const uint64_t offset) {
  // run old threads at this offset
  // uint32_t count = 0;

  for ( ; t != Active.end(); ++t) {
    _executeThread(base, t, cur, offset);
    // ++count;
  }

  // create new threads at this offset
  _executeNewThreads(base, t, cur, offset);

  // ThreadCountHist.resize(count + 1, 0);
  // ++ThreadCountHist[count];
}

inline void Vm::_cleanup() {
  Active.swap(Next);
  Next.clear();

  CheckLabels.clear();

  LiveNoLabel = false;
  Live.clear();
}

void Vm::cleanup() { _cleanup(); }

bool Vm::execute(Thread* t, const byte* const cur) {
  Active.push_back(*t);
  return execute(Active.end()-1, cur);
}

bool Vm::execute(ThreadList::iterator t, const byte* const cur) {
  return _execute(&(*Prog)[0], t, cur);
}

bool Vm::executeEpsilon(Thread* t, uint64_t offset) {
  Active.push_back(*t);
  return executeEpsilon(Active.end()-1, offset);
}

bool Vm::executeEpsilon(ThreadList::iterator t, uint64_t offset) {
  return _executeEpsilon<0>(&(*Prog)[0], t, offset);
}

void Vm::executeFrame(const byte* const cur, uint64_t offset, HitCallback hitFn, void* userData) {
  CurHitFn = hitFn;
  UserData = userData;
  ThreadList::iterator t = Active.begin();
  _executeFrame(Prog->Filter, t, &(*Prog)[0], cur, offset);
}

void Vm::startsWith(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData) {
  CurHitFn = hitFn;
  UserData = userData;
  const Instruction* const base = &(*Prog)[0];
  uint64_t offset = startOffset;

  const byte* const filterOff = beg+Prog->FilterOff;

  if (end - beg == 1 || (filterOff < end - 1 &&
      Prog->Filter[*(reinterpret_cast<const uint16_t*>(filterOff))]))
  {
    for (ThreadList::const_iterator t(First.begin()); t != First.end(); ++t) {
      Active.emplace_back(t->PC, Thread::NOLABEL, offset, Thread::NONE);
    }

    for (const byte* cur = beg; cur < end; ++cur, ++offset) {
      for (ThreadList::iterator t(Active.begin()); t != Active.end(); ++t) {
        _executeThread(base, t, cur, offset);
      }

      _cleanup();

      if (Active.empty()) {
        // early exit if threads die out
        break;
      }
    }
  
    closeOut(hitFn, userData);
    reset();
  }
}

uint64_t Vm::_startOfLeftmostLiveThread(const uint64_t offset) const {
  const ThreadList::const_iterator e(Active.end());
  for (ThreadList::const_iterator t(Active.begin()); t != e; ++t) {
    const unsigned char op = t->PC->OpCode;
    if (op == HALT_OP || op == FINISH_OP) {
      continue;
    }
    // this is a live thread
    return t->Start;
  }

  return offset;
}

uint64_t Vm::search(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData) {
  CurHitFn = hitFn;
  UserData = userData;
  const Instruction* const base = &(*Prog)[0];

  const std::bitset<256*256>& filter = Prog->Filter;
  const byte* const filterEnd = end - Prog->FilterOff - 1;

  uint64_t offset = startOffset;

  const byte* cur = beg;
  for ( ; cur < filterEnd; ++cur, ++offset) {
    #ifdef LBT_TRACE_ENABLED
    open_frame_json(std::clog, offset, cur);
    #endif

    _executeFrame(filter, Active.begin(), base, cur, offset);

    #ifdef LBT_TRACE_ENABLED
    close_frame_json(std::clog, offset);
    #endif

    _cleanup();
  }

  for ( ; cur < end; ++cur, ++offset) {
    #ifdef LBT_TRACE_ENABLED
    open_frame_json(std::clog, offset, cur);
    #endif

    _executeFrame(Active.begin(), base, cur, offset);

    #ifdef LBT_TRACE_ENABLED
    close_frame_json(std::clog, offset);
    #endif

    _cleanup();
  }

  // std::cerr << "Max number of active threads was " << maxActive << ", average was " << total/(end - beg) << std::endl;

  // check for remaining live threads
  return _startOfLeftmostLiveThread(offset);
}

uint64_t Vm::searchResolve(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData) {
  CurHitFn = hitFn;
  UserData = userData;
  const Instruction* const base = &(*Prog)[0];
  uint64_t offset = startOffset;

  bool hadRealOps = true;

  for (const byte* cur = beg; cur < end && !Active.empty() && hadRealOps; ++cur, ++offset) {
    #ifdef LBT_TRACE_ENABLED
    open_frame_json(std::clog, offset, cur);
    #endif

    hadRealOps = false;
    for (ThreadList::iterator t(Active.begin()); t != Active.end(); ++t) {
      hadRealOps |= !(t->PC->OpCode == HALT_OP && t->PC->OpCode == FINISH_OP);
      _executeThread(base, t, cur, offset);
    }

    #ifdef LBT_TRACE_ENABLED
    close_frame_json(std::clog, offset);
    #endif

    _cleanup();
  }

  // std::cerr << "Max number of active threads was " << maxActive << ", average was " << total/(end - beg) << std::endl;

  // check for remaining live threads
  return _startOfLeftmostLiveThread(offset);
}

void Vm::closeOut(HitCallback hitFn, void* userData) {
  CurHitFn = hitFn;
  UserData = userData;

  if (!CurHitFn) {
    return;
  }

  SearchHit hit;

  for (ThreadList::const_iterator t(Active.begin()); t != Active.end(); ++t) {
    if (t->PC->OpCode == FINISH_OP) {
      // has match
      if (t->Start >= MatchEnds[t->Label]) {
        MatchEnds[t->Label] = t->End + 1;

        hit.Start = t->Start;
        hit.End = t->End + 1;
        hit.KeywordIndex = t->Label;
        (*CurHitFn)(UserData, &hit);
      }
    }
  }
  // std::stringstream buf;
  // buf << "{\"threads\":[";
  // for (unsigned int i = 0; i < ThreadCountHist.size(); ++i) {
  //   if (i > 0) {
  //     buf << ",";
  //   }
  //   buf << ThreadCountHist[i];
  // }
  // buf << "]}\n";
  // std::cerr << buf.str();
  // ThreadCountHist.clear();
}
