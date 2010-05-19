#include <scope/test.h>

#include "vm.h"

SCOPE_TEST(executeLit) {
  byte b = 'a';
  std::vector<bool> checkStates;
  Instruction i = Instruction::makeLit('a');
  Thread      cur(&i, 0, 0, 0);
  Vm::ThreadList  next,
              active;
  SCOPE_ASSERT(!Vm::execute(&i, cur, checkStates, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);
  
  next.clear();
  b = 'c';
  SCOPE_ASSERT(!Vm::execute(&i, cur, checkStates, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
}

SCOPE_TEST(executeEither) {
  byte b = 'z';
  std::vector<bool> checkStates;
  Instruction i = Instruction::makeEither('z', '3');
  Thread      cur(&i, 0, 0, 0);
  Vm::ThreadList  next,
              active;
  SCOPE_ASSERT(!Vm::execute(&i, cur, checkStates, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);
  SCOPE_ASSERT_EQUAL(&i+1, cur.PC);

  next.clear();
  b = '3';
  cur.PC = &i;
  SCOPE_ASSERT(!Vm::execute(&i, cur, checkStates, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);
  SCOPE_ASSERT_EQUAL(&i+1, cur.PC);

  next.clear();
  b = '4';
  cur.PC = &i;
  SCOPE_ASSERT(!Vm::execute(&i, cur, checkStates, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(&i, cur.PC);
}

SCOPE_TEST(executeRange) {
  Instruction i = Instruction::makeRange('c', 't');
  std::vector<bool> checkStates;
  Thread      cur(&i, 0, 0, 0);
  Vm::ThreadList  next,
              active;
  for (uint32 j = 0; j < 256; ++j) {
    next.clear();
    byte b = j;
    cur.PC = &i;
    SCOPE_ASSERT(!Vm::execute(&i, cur, checkStates, active, next, &b, 0));
    if ('c' <= j && j <= 't') {
      SCOPE_ASSERT_EQUAL(0u, active.size());
      SCOPE_ASSERT_EQUAL(1u, next.size());
      SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);      
      SCOPE_ASSERT_EQUAL(&i+1, cur.PC);
    }
    else {
      SCOPE_ASSERT_EQUAL(0u, next.size());
      SCOPE_ASSERT_EQUAL(0u, active.size());
    }
  }
}

SCOPE_TEST(executeJump) {
  byte b;
  std::vector<bool> checkStates;
  Instruction i = Instruction::makeJump(18);
  Thread      cur(&i, 0, 0, 0);
  Vm::ThreadList  next,
              active;
  SCOPE_ASSERT(Vm::execute(&i, cur, checkStates, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(&i+18, cur.PC);
}

SCOPE_TEST(executeJumpTable) {
  byte b;
  std::vector<bool> checkStates;
  Instruction instr = Instruction::makeJumpTable();
  Vm::ThreadList next,
                 active;
  for (uint32 i = 0; i < 256; ++i) {
    b = i;
    next.clear();
    active.clear();
    Thread cur(&instr, 0, 0, 0);
    SCOPE_ASSERT(!Vm::execute(&instr, cur, checkStates, active, next, &b, 0));
    SCOPE_ASSERT_EQUAL(0u, active.size());
    SCOPE_ASSERT_EQUAL(1u, next.size());
    SCOPE_ASSERT_EQUAL(&instr, cur.PC);
    SCOPE_ASSERT_EQUAL(Thread(&instr + 1 + b, 0, 0, 0), next[0]);
  }
}

SCOPE_TEST(executeMatch) {
  byte b;
  std::vector<bool> checkStates;
  Instruction i = Instruction::makeMatch();
  Thread      cur(&i, 0, 0, 0);
  Vm::ThreadList  next,
              active;
  SCOPE_ASSERT(!Vm::execute(&i, cur, checkStates, active, next, &b, 57));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i, 0, 0, 57), cur);
}

SCOPE_TEST(executeSaveLabel) {
  byte b;
  std::vector<bool> checkStates;
  Instruction i = Instruction::makeSaveLabel(31);
  Thread      cur(&i, 0, 0, 0);
  Vm::ThreadList  next,
              active;
  SCOPE_ASSERT(Vm::execute(&i, cur, checkStates, active, next, &b, 47));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 31, 0, 0), cur);
}

SCOPE_TEST(executeFork) {
  byte b;
  std::vector<bool> checkStates;
  Instruction i = Instruction::makeFork(237);
  Thread      cur(&i, 0, 0, 0);
  Vm::ThreadList  next,
              active;
  SCOPE_ASSERT(Vm::execute(&i, cur, checkStates, active, next, &b, 47));
  SCOPE_ASSERT_EQUAL(1u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+237, 0, 0, 0), active[0]);
  SCOPE_ASSERT_EQUAL(&i+1, cur.PC);
}

SCOPE_TEST(executeCheckBranch) {
  byte b;
  std::vector<bool> checkStates(6, false);
  Instruction i[] = {Instruction::makeCheckBranch(5), Instruction::makeJump(3019)};
  Thread      cur(i, 0, 0, 0);
  Vm::ThreadList next,
                 active;
  SCOPE_ASSERT(Vm::execute(i, cur, checkStates, active, next, &b, 231));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(i+1, 0, 0, 0), cur);
  SCOPE_ASSERT(checkStates[5]);
  SCOPE_ASSERT(checkStates[0]); // this bit is reserved specially to see whether we need to clear the set

  cur.PC = i;
  SCOPE_ASSERT(Vm::execute(i, cur, checkStates, active, next, &b, 231));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(i+2, 0, 0, 0), cur); // skipped ahead because the state was set
  SCOPE_ASSERT(checkStates[5]);
  SCOPE_ASSERT(checkStates[0]);
}

class TestCallback: public HitCallback {
public:
  virtual void collect(const SearchHit& hit) {
    Hits.push_back(hit);
  }
  
  std::vector<SearchHit> Hits;
};

SCOPE_TEST(simpleLitMatch) {
  ProgramPtr p(new Program());
  Program& prog(*p);
  prog.push_back(Instruction::makeSaveLabel(3));
  prog.push_back(Instruction::makeLit('a'));
  prog.push_back(Instruction::makeLit('b'));
  prog.push_back(Instruction::makeMatch());

  byte text[] = {'a', 'b', 'c'};
  TestCallback cb;
  Vm v;
  ByteSet fb;
  fb.set('a');
  v.init(p, fb);
  SCOPE_ASSERT(!v.search(text, &text[3], 35, cb));
  SCOPE_ASSERT_EQUAL(1u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(35, 2, 3), cb.Hits[0]);
  text[1] = 'c';
  SCOPE_ASSERT(!v.search(text, &text[3], 35, cb));
}

SCOPE_TEST(threeKeywords) {
  ProgramPtr p(new Program); // (a)|(b)|(bc)
  p->push_back(Instruction::makeFork(2));       // 0
  p->push_back(Instruction::makeJump(5));       // 1
  p->push_back(Instruction::makeLit('a'));      // 2
  p->push_back(Instruction::makeSaveLabel(0));  // 3
  p->push_back(Instruction::makeMatch());       // 4
  p->push_back(Instruction::makeLit('b'));      // 5
  p->push_back(Instruction::makeFork(9));       // 6
  p->push_back(Instruction::makeSaveLabel(1));  // 7
  p->push_back(Instruction::makeMatch());       // 8
  p->push_back(Instruction::makeLit('c'));      // 9
  p->push_back(Instruction::makeSaveLabel(2));  // 10
  p->push_back(Instruction::makeMatch());       // 11

  byte text[] = {'c', 'a', 'b', 'c'};
  TestCallback cb;
  Vm v;
  ByteSet fb;
  fb.set('a');
  fb.set('b');
  v.init(p, fb);
  SCOPE_ASSERT(!v.search(text, &text[4], 10, cb));
  SCOPE_ASSERT_EQUAL(3u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), cb.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), cb.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 2), cb.Hits[2]);
}

SCOPE_TEST(stitchedText) {
  ProgramPtr p(new Program);
  p->push_back(Instruction::makeLit('a'));
  p->push_back(Instruction::makeLit('b'));
  p->push_back(Instruction::makeMatch());
  byte text1[] = {'a', 'c', 'a'},
       text2[] = {'b', 'b'};
  TestCallback cb;
  Vm v;
  ByteSet fb;
  fb.set('a');
  v.init(p, fb);
  SCOPE_ASSERT(v.search(text1, &text1[3], 0, cb));
  SCOPE_ASSERT_EQUAL(0u, cb.Hits.size());
  SCOPE_ASSERT(!v.search(text2, &text2[2], 3, cb));
  SCOPE_ASSERT_EQUAL(1u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), cb.Hits[0]);
}
