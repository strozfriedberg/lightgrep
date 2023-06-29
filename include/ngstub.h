#pragma once

#include <cassert>
#include <limits>
#include <cstring>

#include "instructions.h"
#include "threadlist.h"

enum OpCodesNG {
  BYTE_OP_NG = 0,
  BRANCH_BYTE,
  JUMP_OP_NG,
  SET_START,
  SET_END,
  MATCH_OP_NG,
  MEMCHR_OP
};

#pragma pack(push, 1)

struct InstructionNG {
  Operand Op;

  byte OpCode; // low byte

  void set(const uint32_t val) {
    *reinterpret_cast<uint32_t*>(this) = val;
  }

  explicit operator uint32_t() const {
    return *reinterpret_cast<const uint32_t*>(this);
  }
};


struct CurEnd {
  uint32_t cur;
  uint32_t end;
};

struct MatchInfo {
  uint64_t Start,
           End;
  uint32_t Label; // pattern index number

  MatchInfo():
    Start(std::numeric_limits<uint64_t>::max()),
    End(std::numeric_limits<uint64_t>::max()),
    Label(std::numeric_limits<uint32_t>::max()) {}

  MatchInfo(uint64_t s, uint64_t e, uint32_t l):
    Start(s), End(e), Label(l) {}

  bool operator==(const MatchInfo& x) const {
    return Start == x.Start && End == x.End && Label == x.Label;
  }
};


#pragma pack(pop)

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

int dispatch(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm);

#include "lightgrep/search_hit.h"

#include <iterator>


class ProgramNG {
/*
  A program is at base an array of 32-bit instructions.

  However, often other state needs to be bunbled with these instructions.
  For example, it's good to know how many patterns are encoded in the instructions,
  and maybe what they were originally, and there could be all sorts of statistics
  about the automata involved that are useful to keep around, and other
  data structures that can be profitably used by the VM. So, this is where to put that.
*/
public:
  ProgramNG(): Code() {}
  ProgramNG(const std::vector<InstructionNG>& code): Code(code) {}

  void swapCode(std::vector<InstructionNG>& newCode) {
    Code.swap(newCode);
  }

  const InstructionNG* begin() const { return &Code[0]; }
  const InstructionNG* end() const { return &Code[Code.size()]; }

  uint32_t numInstructions() const { return static_cast<uint32_t>(Code.size()); }

private:
  std::vector<InstructionNG> Code;
};


class VmNG {
/*
  A VM is a virtual machine for executing programs in a regexp-oriented bytecode
  fantasy land. The VM provides high-level methods for searching and matching
  data, while invoking low-level machinery behind the scenes to do just that.

  This particular VM allows for multiple "threads" (green threads) of execution
  to be active. The threads are kept in order, which corresponds to automaton-
  precedence rules within the patterns. However, the threads are not executed in
  lock-step, byte by byte. This allows for optimizations, but can complicate
  reporting of search hits (aka matches).

  Execution of the instructions actually occurs in a series of free functions
  that utilize "tail call optimization" to avoid function call and stack overhead.
  The purpose of the VM is to kick this process off and to provide a place for
  executing programs to retain state and, sometimes, synchronize with each other.

  A VM is not threadsafe from a client perspective, however. Multithreaded clients
  can safely share a ProgramNG amongst multiple VmNGs running in separate threads.
*/
public:
  VmNG(): Prog(), Hits(), BufOffset(0) { Hits.reserve(100); }

  VmNG(const ProgramNG& prog): Prog(prog), Hits(), BufOffset(0) { Hits.reserve(100); }

  const std::vector<MatchInfo>& hits() const { return Hits; }

  uint64_t curBufOffset() const { return BufOffset; }

  void addHit(const MatchInfo& hit) { Hits.push_back(hit); }

  void search(const byte* buf, const byte* bufEnd) {
    BufOffset = 0;
    CurEnd curBuf = {0, static_cast<uint32_t>(bufEnd - buf)};
    CurEnd curProg = {0, Prog.numInstructions()};
    MatchInfo info;

    dispatch(buf, curBuf, Prog.begin(), curProg, info, this);
  }

  void reset() {
    Hits.clear();
    BufOffset = 0;
  }

private:
  ProgramNG Prog;

  std::vector<MatchInfo> Hits;

  uint64_t BufOffset;
};

/*
  State:
    current instruction/offset into program (cur instruction)
    [begin, end) of program

    current offset into input buffer (cur byte)
    [begin, end) of input buffer

    start of match, pattern label

    pointer back to VM machinery (potential match reporting & resolution, thread lists, etc)

  CPS on Intel: six registers, 64 bits apiece
    - should they be out-parameters so state becomes visible to callee?
    - does making them out-parameters even work with __fastcall semantics???
    - it's okay for complex functions to manipulate lots of data, but calling functions could screw up all of CSP
*/



template<auto DispatcherFn>
int do_byte_op(const byte* buf,
               CurEnd& curBuf,
               const InstructionNG* prog,
               CurEnd& curProg,
               MatchInfo& info,
               void* vm)
{
  const InstructionNG inst = prog[curProg.cur];
  if (UNLIKELY(buf[curBuf.cur] == inst.Op.T1.Byte)) {
    ++curBuf.cur;
    ++curProg.cur;
    [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
  }
  else {
    return 0;
  }
}

template<auto DispatcherFn>
int do_branch_byte_op(const byte* buf,
                     CurEnd& curBuf,
                     const InstructionNG* prog,
                     CurEnd& curProg,
                     MatchInfo& info,
                     void* vm)
{
  if (UNLIKELY(curBuf.cur >= curBuf.end)) {
    return 0;
  }
  const InstructionNG inst = prog[curProg.cur];
  if (UNLIKELY(buf[curBuf.cur] == inst.Op.T1.Byte)) {
    curProg.cur += 2;
  }
  else {
    curProg.cur = uint32_t(prog[curProg.cur + 1]);
  }
  ++curBuf.cur;
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_set_start_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  VmNG& vmRef(*reinterpret_cast<VmNG*>(vm));

  assert(vmRef.curBufOffset() + curBuf.cur >= prog[curProg.cur].Op.Offset);
  info.Start = vmRef.curBufOffset() + curBuf.cur - prog[curProg.cur].Op.Offset;
  ++curProg.cur;
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_set_end_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  VmNG& vmRef(*reinterpret_cast<VmNG*>(vm));

  info.End = vmRef.curBufOffset() + curBuf.cur;
  ++curProg.cur;
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_match_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  VmNG& vmRef(*reinterpret_cast<VmNG*>(vm));

  vmRef.addHit(info);
  ++curProg.cur;
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_memchr_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  // std::cerr << "memchr'ing for '" << prog[curProg.cur].Op.T1.Byte << "' [" << curBuf.cur << ", " << curBuf.end << ") of " << buf << '\n';
  const byte* cur = &buf[curBuf.cur];
  const byte* end = &buf[curBuf.end];
  const byte* found(reinterpret_cast<const byte*>(std::memchr(cur, prog[curProg.cur].Op.T1.Byte, end - cur)));
  if (found) {
    ++curProg.cur;
    curBuf.cur = found - buf;
    ++curBuf.cur;
    // std::cerr << "Found at " << (curBuf.cur - 1) << ", curProg.cur at " << curProg.cur << '\n';
  }
  else {
    // std::cerr << "Not found\n";
    curBuf.cur = curBuf.end;
  }
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_jump_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  curProg.cur = uint32_t(prog[curProg.cur + 1]);
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

int dispatch(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  if (UNLIKELY(curBuf.cur == curBuf.end)) {
    return 0;
  }
  switch(prog[curProg.cur].OpCode) {
  case BYTE_OP_NG:
    [[clang::musttail]] return do_byte_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case BRANCH_BYTE:
    [[clang::musttail]] return do_branch_byte_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case JUMP_OP_NG:
    [[clang::musttail]] return do_jump_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case SET_START:
    [[clang::musttail]] return do_set_start_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case SET_END:
    [[clang::musttail]] return do_set_end_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case MATCH_OP_NG:
    [[clang::musttail]] return do_match_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
   case MEMCHR_OP:
    [[clang::musttail]] return do_memchr_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  default:
    return 0;
  }
}
