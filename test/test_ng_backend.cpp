#include <catch2/catch_test_macros.hpp>

#include "instructions.h"

enum OpCodesNG {
  BYTE_OP_NG = 0,
  MATCH_OP_NG
};

#pragma pack(push, 1)

struct InstructionNG {
  Operand Op;

  byte OpCode; // low byte
};

struct CurEnd {
  uint32_t cur;
  uint32_t end;
};

struct MatchInfo {
  uint32_t som;   // buffer index of start of match; needs to get remapped by callee
  uint32_t label; // pattern index number
};

#pragma pack(pop)

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

class VmNG {
public:

private:
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
               CurEnd curBuf,
               const InstructionNG* prog,
               CurEnd curProg,
               MatchInfo info,
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

int dispatch(const byte* buf,
             CurEnd curBuf,
             const InstructionNG* prog,
             CurEnd curProg,
             MatchInfo info,
             void* vm)
{
  if (UNLIKELY(curBuf.cur == curBuf.end)) {
    return 0;
  }
  switch(prog[curProg.cur].OpCode) {
  case BYTE_OP_NG:
    return do_byte_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  default:
    return 0;
  }
}


struct TestDispatcher {

  const byte* Buf;
  CurEnd      CurBuf;

  const InstructionNG* Prog;
  CurEnd               CurProg;

  MatchInfo   Info;

};

int test_dispatch(const byte* buf,
                     CurEnd curBuf,
                     const InstructionNG* prog,
                     CurEnd curProg,
                     MatchInfo info,
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
  MatchInfo info = {0, 0};

  int result = do_byte_op<test_dispatch>(buf, curBuf, &prog, curProg, info, &disp);
  REQUIRE(result == 0);
  result = do_byte_op<test_dispatch>(&buf[1], curBuf, &prog, curProg, info, &disp);
  REQUIRE(result == 1);
}

// TEST_CASE("do_branch_byte_op") {
//   TestDispatcher disp;

//   std::string data("hello");
//   const byte* buf = (const byte*)data.data();
//   CurEnd curBuf = {0, 5};
//   InstructionNG prog[]
//   prog.OpCode = OpCodesNG::BYTE_OP_NG;
//   prog.Op.T1.Byte = 'e';
//   CurEnd curProg = {0, 1};
//   MatchInfo info = {0, 0};

//   int result = do_branch_byte_op<test_dispatch>(buf, curBuf, &prog, curProg, info, &disp);
// }
