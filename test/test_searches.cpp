#include <scope/test.h>

#include "parser.h"
#include "utility.h"
#include "vm.h"

#include <iostream>
#include <cstdlib>

#include <boost/bind.hpp>

struct STest: public HitCallback {
  std::vector< SearchHit > Hits;
  DynamicFSMPtr Fsm;
  ProgramPtr Prog;
  Vm Grep;

  STest(const std::string& key) {
    SyntaxTree  tree;
    Parser      p;
    if (parse(key, tree, boost::bind(&Parser::callback, &p, _1, _2))) {
      Fsm = p.getFsm();
      Prog = createProgram(*Fsm);
      Grep.init(Prog, firstBytes(*Fsm), 1);
    }
    else {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("couldn't parse " << key);
    }
  }

  STest(uint32 num, const char** keys) {
    Fsm.reset();
    for (uint32 i = 0; i < num; ++i) {
      SyntaxTree  tree;
      Parser      p;
      p.setCurLabel(i);
      if (parse(std::string(keys[i]), tree, boost::bind(&Parser::callback, &p, _1, _2))) {
        // writeGraphviz(std::cout, *p.getFsm());
        if (Fsm) {
          mergeIntoFSM(*Fsm, *p.getFsm(), i);
          // writeGraphviz(std::cout, *Fsm);
        }
        else {
          Fsm = p.getFsm();
        }
      }
      else {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("couldn't parse keys[" << i << "], " << keys[i]);
      }
    }
    Prog = createProgram(*Fsm);
    Grep.init(Prog, firstBytes(*Fsm), 1);
  }
  
  virtual void collect(const SearchHit& hit) {
    Hits.push_back(hit);
  }
};

SCOPE_FIXTURE_CTOR(abSearch, STest, STest("ab")) {
  const byte* text = (const byte*)"abc";
  fixture.Grep.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 2u, 0u), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aOrbSearch, STest, STest("a|b")) {
  const byte* text = (const byte*)"abc";
  fixture.Grep.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 1u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1u, 1u, 0u), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aOrbOrcSearch, STest, STest("a|b|c")) {
  const byte* text = (const byte*)"abc";
  fixture.Grep.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 1u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1u, 1u, 0u), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2u, 1u, 0u), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(aOrbcSearch, STest, STest("a|bc")) {
  const byte* text = (const byte*)"abc";
  fixture.Grep.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 1u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1u, 2u, 0u), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aAndbOrcSearch, STest, STest("a(b|c)")) {
  const byte* text = (const byte*)"abac";
  fixture.Grep.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 2u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2u, 2u, 0u), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(abQuestionSearch, STest, STest("ab?")) {
  const byte* text = (const byte*)"aab";
  // std::cout << *fixture.Prog;
  fixture.Grep.search(text, text+3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 1u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1u, 2u, 0u), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(abQcQdSearch, STest, STest("ab?c?d")) {
  //                               012345678901234
  const byte* text = (const byte*)"ad abcd abd acd";
  fixture.Grep.search(text, text+15, 0, fixture);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 2u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3u, 4u, 0u), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8u, 3u, 0u), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12u, 3u, 0u), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(aOrbQcSearch, STest, STest("(a|b?)c")) {
  //                               01234567890
  const byte* text = (const byte*)"ac bc c abc";
  fixture.Grep.search(text, text + std::strlen((const char*)text), 0, fixture);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(aOrbPlusSearch, STest, STest("(a|b)+")) {
  const byte* text = (const byte*)" abbaaaba ";
  // std::cout << *fixture.Prog;
  fixture.Grep.search(text, text+10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 8, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(fourKeysSearch, STest, STest(4, (const char*[]){"a(b|c)a", "ac+", "ab?a", "two"})) { //
  // writeGraphviz(std::cout, *fixture.Fsm);
  //                               01234567890123
  const byte* text = (const byte*)"aba aa aca two";
  fixture.Grep.search(text, text + 14, 0, fixture);
  SCOPE_ASSERT_EQUAL(6u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(aOrbStarbPlusSearch, STest, STest("(a|b)*b+")) {
  //                               01234567890
  const byte* text = (const byte*)" abbaaaba b";
  // std::cout << *fixture.Prog;
  fixture.Grep.search(text, text+11, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[1]);
}
