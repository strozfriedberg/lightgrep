#pragma once

#include <cassert>
#include <limits>
#include <cstring>

#include "instructions.h"

enum OpCodesNG {
  BYTE_OP_NG = 0,
  BRANCH_BYTE,
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

class VmNG {
public:
  VmNG(): BufOffset(0) { Hits.reserve(100); }

  const std::vector<MatchInfo>& hits() const { return Hits; }

  uint64_t curBufOffset() const { return BufOffset; }

  void addHit(const MatchInfo& hit) { Hits.push_back(hit); }

  void search(const byte* buf, const byte* bufEnd, const InstructionNG* prog) {
    BufOffset = 0;
    CurEnd curBuf = {0, static_cast<uint32_t>(bufEnd - buf)};
    CurEnd curProg = {0, 10};
    MatchInfo info;

    dispatch(buf, curBuf, prog, curProg, info, this);
  }

private:
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
	const byte* cur = &buf[curBuf.cur];
	const byte* end = &buf[curBuf.end];
	const byte* found(reinterpret_cast<const byte*>(std::memchr(cur, prog[curProg.cur].Op.T1.Byte, end - cur)));
	if (found) {
		++curProg.cur;
		curBuf.cur = found - cur;
		++curBuf.cur;
	}
	else {
		curBuf.cur = curBuf.end;
	}
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
  case SET_START:
    [[clang::musttail]] return do_set_start_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case SET_END:
    [[clang::musttail]] return do_set_end_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case MATCH_OP_NG:
    [[clang::musttail]] return do_match_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  default:
    return 0;
  }
}
