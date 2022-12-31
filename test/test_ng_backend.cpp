#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "ngstub.h"

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
  REQUIRE(result == 1);
  REQUIRE(curProg.cur == 1);
  REQUIRE(disp.hits().size() == 1);
  REQUIRE(info == disp.hits()[0]);
}

TEST_CASE("memchr_op") {
  TestDispatcher disp;

  std::string data("hello");
  const byte* buf = (const byte*)data.data();
  CurEnd curBuf = {0, 5};
  InstructionNG prog[1];
  prog[0].OpCode = OpCodesNG::MEMCHR_OP;
  prog[0].Op.T1.Byte = 'l';
  CurEnd curProg = {0, 1};
  MatchInfo info;

  int result = do_memchr_op<test_dispatch>(buf, curBuf, prog, curProg, info, &disp);
  REQUIRE(result == 1);
  REQUIRE(curProg.cur == 1);
  REQUIRE(curBuf.cur == 3); // remember, one past, since it consumes

  // find the next 'l', which is currently pointed at
  curProg.cur = 0;
  result = do_memchr_op<test_dispatch>(buf, curBuf, prog, curProg, info, &disp);
  REQUIRE(result == 1);
  REQUIRE(curProg.cur == 1);
  REQUIRE(curBuf.cur == 4);

  curBuf.cur = 0;
  curProg.cur = 0;
  prog[0].Op.T1.Byte = 'j';
  result = do_memchr_op<test_dispatch>(buf, curBuf, prog, curProg, info, &disp);
  REQUIRE(result == 1);
  REQUIRE(curProg.cur == 0);
  REQUIRE(curBuf.cur == 5);
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

#include <list>

TEST_CASE("threadlist") {
  Threadlist list;

  ThreadNG t;
  t.PC = 5;

  REQUIRE(list.empty());
  REQUIRE(list.size() == 0);
  auto itr = list.insert(list.begin(), t);
  REQUIRE(!list.empty());
  REQUIRE(list.size() == 1);
  REQUIRE(itr == list.begin());
  REQUIRE(itr != list.end());
  REQUIRE(itr->PC == 5);
  REQUIRE((*itr).PC == 5);

  itr = list.insert(list.begin(), ThreadNG{6, LG_SearchHit()});
  REQUIRE(list.size() == 2);
  REQUIRE(itr == list.begin());
  REQUIRE(itr != list.end());
  REQUIRE(itr->PC == 6);

  ++itr;
  REQUIRE(itr != list.begin());
  REQUIRE(itr != list.end());
  REQUIRE(itr->PC == 5);

  auto prevItr = itr++;
  REQUIRE(prevItr != itr);
  REQUIRE(prevItr != list.begin());
  REQUIRE(prevItr != list.end());
  REQUIRE(prevItr->PC == 5);
  REQUIRE(itr == list.end());

  itr = list.insert(list.end(), ThreadNG{7, LG_SearchHit()});
  REQUIRE(itr != list.begin());
  REQUIRE(itr != list.end());
  REQUIRE(list.size() == 3);
  REQUIRE(itr->PC == 7);
  ++itr;
  REQUIRE(itr == list.end());

  auto end = list.end();
  REQUIRE(end == list.end());
  ++end;
  REQUIRE(end == list.end());

  list.clear();
  REQUIRE(list.empty());
  REQUIRE(list.size() == 0);
  REQUIRE(list.begin() == list.end());

  list.insert(list.end(), ThreadNG{1, LG_SearchHit()});
  itr = list.insert(list.end(), ThreadNG{2, LG_SearchHit()});
  list.insert(list.end(), ThreadNG{3, LG_SearchHit()});
  REQUIRE(list.size() == 3);
  itr = list.erase(itr);
  REQUIRE(list.size() == 2);
  REQUIRE(itr->PC == 3);
  REQUIRE(list.front().PC == 1);
  REQUIRE(list.back().PC == 3);
  itr = list.erase(itr);
  REQUIRE(list.size() == 1);
  REQUIRE(itr == list.end());

  const size_t vec_size = list.vector_size();
  itr = list.insert(list.end(), ThreadNG{8, LG_SearchHit()});
  REQUIRE(vec_size == list.vector_size());

  Threadlist list1;
  list1.reserve(100);
  BENCHMARK("threadlist performance") {
    list1.clear();
    for (unsigned int i = 0; i < 40; ++i) {
      list1.insert(list1.begin(), ThreadNG{i, LG_SearchHit()});
    }
    auto itr = list1.begin();
    for (unsigned int i = 0; i < 10; ++i) {
      itr = list1.erase(itr);
      ++itr;
      ++itr;
    }
    for (unsigned int i = 0; i < 10; ++i) {
      list1.insert(list1.begin(), ThreadNG{i, LG_SearchHit()});
    }
  };

  std::list<ThreadNG> list2;
  BENCHMARK("stdlist performance") {
    list2.clear();
    for (unsigned int i = 0; i < 40; ++i) {
      list2.insert(list2.begin(), ThreadNG{i, LG_SearchHit()});
    }
    auto itr = list2.begin();
    for (unsigned int i = 0; i < 10; ++i) {
      itr = list2.erase(itr);
      ++itr;
      ++itr;
    }
    for (unsigned int i = 0; i < 10; ++i) {
      list2.insert(list2.begin(), ThreadNG{i, LG_SearchHit()});
    }
  };

  std::vector<ThreadNG> list3;
  list3.reserve(100);
  BENCHMARK("vectorlist performance") {
    list3.clear();
    for (unsigned int i = 0; i < 40; ++i) {
      list3.insert(list3.begin(), ThreadNG{i, LG_SearchHit()});
    }
    auto itr = list3.begin();
    for (unsigned int i = 0; i < 10; ++i) {
      itr = list3.erase(itr);
      ++itr;
      ++itr;
    }
    for (unsigned int i = 0; i < 10; ++i) {
      list3.insert(list3.begin(), ThreadNG{i, LG_SearchHit()});
    }
  };
}
