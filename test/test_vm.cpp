#include <scope/test.h>

#include "vm.h"

SCOPE_TEST(executeLit) {
  byte b = 'a';
  Instruction i = Instruction::makeLit('a');
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next,
              active;
  SCOPE_ASSERT(!Vm::execute(&i, cur, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);
  
  next.clear();
  b = 'c';
  SCOPE_ASSERT(!Vm::execute(&i, cur, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
}

SCOPE_TEST(executeEither) {
  byte b = 'z';
  Instruction i = Instruction::makeEither('z', '3');
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next,
              active;
  SCOPE_ASSERT(!Vm::execute(&i, cur, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);
  SCOPE_ASSERT_EQUAL(&i+1, cur.PC);

  next.clear();
  b = '3';
  cur.PC = &i;
  SCOPE_ASSERT(!Vm::execute(&i, cur, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);
  SCOPE_ASSERT_EQUAL(&i+1, cur.PC);

  next.clear();
  b = '4';
  cur.PC = &i;
  SCOPE_ASSERT(!Vm::execute(&i, cur, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(&i, cur.PC);
}

SCOPE_TEST(executeRange) {
  Instruction i = Instruction::makeRange('c', 't');
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next,
              active;
  for (uint32 j = 0; j < 256; ++j) {
    next.clear();
    byte b = j;
    cur.PC = &i;
    SCOPE_ASSERT(!Vm::execute(&i, cur, active, next, &b, 0));
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
  Instruction i = Instruction::makeJump(18);
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next,
              active;
  SCOPE_ASSERT(Vm::execute(&i, cur, active, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(&i+18, cur.PC);
}

SCOPE_TEST(executeMatch) {
  byte b;
  Instruction i = Instruction::makeMatch();
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next,
              active;
  SCOPE_ASSERT(!Vm::execute(&i, cur, active, next, &b, 57));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i, 0, 0, 57), cur);
}

SCOPE_TEST(executeSaveLabel) {
  byte b;
  Instruction i = Instruction::makeSaveLabel(31);
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next,
              active;
  SCOPE_ASSERT(Vm::execute(&i, cur, active, next, &b, 47));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 31, 0, 0), cur);
}

SCOPE_TEST(executeFork) {
  byte b;
  Instruction i = Instruction::makeFork(237);
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next,
              active;
  SCOPE_ASSERT(Vm::execute(&i, cur, active, next, &b, 47));
  SCOPE_ASSERT_EQUAL(1u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+237, 0, 0, 0), active[0]);
  SCOPE_ASSERT_EQUAL(&i+1, cur.PC);
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
  v.init(p);
  SCOPE_ASSERT(v.search(text, &text[3], 35, cb));
  SCOPE_ASSERT_EQUAL(1u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(35, 2, 3), cb.Hits[0]);
  text[1] = 'c';
  SCOPE_ASSERT(!v.search(text, &text[3], 35, cb));
}

SCOPE_TEST(twoKeywords) {
  ProgramPtr p(new Program);
  p->push_back(Instruction::makeFork(2));       // 0
  p->push_back(Instruction::makeJump(5));       // 1
  p->push_back(Instruction::makeLit('a'));      // 2
  p->push_back(Instruction::makeSaveLabel(0));  // 3
  p->push_back(Instruction::makeMatch());       // 4
  p->push_back(Instruction::makeLit('b'));      // 5
  p->push_back(Instruction::makeSaveLabel(1));  // 6
  p->push_back(Instruction::makeMatch());       // 7

  byte text[] = {'c', 'a', 'b', 'c'};
  TestCallback cb;
  Vm v;
  v.init(p);
  SCOPE_ASSERT(v.search(text, &text[4], 10, cb));
  SCOPE_ASSERT_EQUAL(2u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), cb.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), cb.Hits[1]);
}
