#include <catch2/catch_test_macros.hpp>

#include <cassert>
#include <limits>

#include "instructions.h"

enum OpCodesNG {
  BYTE_OP_NG = 0,
  BRANCH_BYTE,
  SET_START,
  SET_END,
  MATCH_OP_NG
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

  bool operator==(const MatchInfo&) const = default;
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
  VmNG(): BufOffset(0) {}

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
    return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
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
  return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
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
  return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
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
  return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
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
  return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
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
    return do_byte_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case BRANCH_BYTE:
    return do_branch_byte_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case SET_START:
    return do_set_start_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case SET_END:
    return do_set_end_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case MATCH_OP_NG:
    return do_match_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  default:
    return 0;
  }
}


struct TestDispatcher: public VmNG {

  const byte* Buf;
  CurEnd      CurBuf;

  const InstructionNG* Prog;
  CurEnd               CurProg;

  MatchInfo   Info;
};

int test_dispatch(const byte* buf,
                     CurEnd& curBuf,
                     const InstructionNG* prog,
                     CurEnd& curProg,
                     MatchInfo& info,
                     void* vm)
{
  TestDispatcher* dPtr = reinterpret_cast<TestDispatcher*>(vm);
  dPtr->Buf = buf;
  dPtr->CurBuf = curBuf;
  dPtr->Prog = prog;
  dPtr->CurProg = curProg;
  dPtr->Info = info;
  return 1;
}

TEST_CASE("do_byte_op") {
  TestDispatcher disp;

  std::string data("hello");
  const byte* buf = (const byte*)data.data();
  CurEnd curBuf = {0, 5};
  InstructionNG prog;
  prog.OpCode = OpCodesNG::BYTE_OP_NG;
  prog.Op.T1.Byte = 'e';
  CurEnd curProg = {0, 1};
  MatchInfo info;

  int result = do_byte_op<test_dispatch>(buf, curBuf, &prog, curProg, info, &disp);
  REQUIRE(result == 0);
  result = do_byte_op<test_dispatch>(&buf[1], curBuf, &prog, curProg, info, &disp);
  REQUIRE(result == 1);
}

TEST_CASE("do_branch_byte_op") {
  TestDispatcher disp;

  std::string data("hello");
  const byte* buf = (const byte*)data.data();
  CurEnd curBuf = {0, 5};
  InstructionNG prog[2];
  prog[0].OpCode = OpCodesNG::BRANCH_BYTE;
  prog[0].Op.T1.Byte = 'e';
  prog[1].set(0);
  CurEnd curProg = {0, 2};
  MatchInfo info;

  int result = do_branch_byte_op<test_dispatch>(buf, curBuf, prog, curProg, info, &disp);
  REQUIRE(curProg.cur == 0); // fails, branches back to zero
  REQUIRE(curBuf.cur == 1);
  result = do_branch_byte_op<test_dispatch>(buf, curBuf, prog, curProg, info, &disp);
  REQUIRE(curProg.cur == 2); // succeeds, skips ahead
  REQUIRE(curBuf.cur == 2);

  curBuf.cur = 5; // return 0 since we're at the end of the buffer
  curProg.cur = 0;
  result = do_branch_byte_op<test_dispatch>(buf, curBuf, prog, curProg, info, &disp);
  REQUIRE(result == 0);
  REQUIRE(curProg.cur == 0);
  REQUIRE(curBuf.cur == 5);
}

TEST_CASE("set_start") {
  TestDispatcher disp;

  std::string data("hello");
  const byte* buf = (const byte*)data.data();
  CurEnd curBuf = {3, 5};
  InstructionNG prog[1];
  prog[0].OpCode = OpCodesNG::SET_START;
  prog[0].Op.Offset = 0;
  CurEnd curProg = {0, 1};
  MatchInfo info;

  int result = do_set_start_op<test_dispatch>(buf, curBuf, prog, curProg, info, &disp);
  REQUIRE(result == 1);
  REQUIRE(curBuf.cur == 3);
  REQUIRE(info.Start == 3);
  REQUIRE(curProg.cur == 1);
}

TEST_CASE("set_end") {
  TestDispatcher disp;

  std::string data("hello");
  const byte* buf = (const byte*)data.data();
  CurEnd curBuf = {3, 5};
  InstructionNG prog[1];
  prog[0].OpCode = OpCodesNG::SET_END;
  prog[0].Op.Offset = 0;
  CurEnd curProg = {0, 1};
  MatchInfo info;

  int result = do_set_end_op<test_dispatch>(buf, curBuf, prog, curProg, info, &disp);
  REQUIRE(result == 1);
  REQUIRE(curBuf.cur == 3);
  REQUIRE(info.End == 3);
  REQUIRE(curProg.cur == 1);
}

TEST_CASE("match_op") {
  TestDispatcher disp;

  std::string data("hello");
  const byte* buf = (const byte*)data.data();
  CurEnd curBuf = {3, 5};
  InstructionNG prog[1];
  prog[0].OpCode = OpCodesNG::MATCH_OP_NG;
  prog[0].Op.Offset = 0;
  CurEnd curProg = {0, 1};
  MatchInfo info = {1, 3, 2};

  REQUIRE(disp.hits().empty());
  int result = do_match_op<test_dispatch>(buf, curBuf, prog, curProg, info, &disp);
  REQUIRE(curProg.cur == 1);
  REQUIRE(disp.hits().size() == 1);
  REQUIRE(info == disp.hits()[0]);
}

TEST_CASE("simple_foo_search") {
  VmNG vm;
  //                0         1         2         3
  //                0123456789012345678901234567890123456789
  std::string data("This is a clear example of the foo going fubar.");
  const byte* buf = (const byte*)data.data();

  InstructionNG prog[11];
  prog[0].OpCode = OpCodesNG::BRANCH_BYTE;
  prog[0].Op.T1.Byte = 'f';
  prog[1].set(0);
  prog[2].OpCode = OpCodesNG::BRANCH_BYTE;
  prog[2].Op.T1.Byte = 'o';
  prog[3].set(0);
  prog[4].OpCode = OpCodesNG::BRANCH_BYTE;
  prog[4].Op.T1.Byte = 'o';
  prog[5].set(0);
  prog[6].OpCode = OpCodesNG::SET_START;
  prog[6].Op.Offset = 3;
  prog[7].OpCode = OpCodesNG::SET_END;
  // need a label instruction
  prog[8].OpCode = OpCodesNG::MATCH_OP_NG;
  // need a prog[8] = Jmp 0
  prog[9].OpCode = OpCodesNG::BRANCH_BYTE;
  prog[9].Op.T1.Byte = 0; // null won't exist, so this is a poor man's jump
  prog[10].set(0);

  CurEnd curBuf = {0, static_cast<uint32_t>(data.length())};
  CurEnd curProg = {0, 11};
  MatchInfo info;

  dispatch(buf, curBuf, prog, curProg, info, &vm);
  REQUIRE(curBuf.cur == curBuf.end);
  CHECK(curProg.cur == 0);
//  vm.search(buf, buf + data.length(), &prog[0]);
  REQUIRE(vm.hits().size() == 1);
  const MatchInfo& hit = vm.hits()[0];
  CHECK(hit.Start == 31);
  CHECK(hit.End == 34);
  CHECK(hit.Label == std::numeric_limits<uint32_t>::max());
}
