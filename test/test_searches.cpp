#include <scope/test.h>

#include "parser.h"
#include "utility.h"
#include "vm.h"

#include <boost/bind.hpp>

struct STest: public HitCallback {
  std::vector< SearchHit > Hits;
  Vm Grep;

  STest(const std::string& key) {
    SyntaxTree  tree;
    Parser      p;
    if (parse(key, tree, boost::bind(&Parser::callback, &p, _1, _2))) {
      DynamicFSMPtr fsm = p.getFsm();
      ProgramPtr prog = createProgram(*fsm);
      Grep.init(prog, firstBytes(*fsm), 1);
    }
    else {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("couldn't parse " << key);
    }
  }

  STest(uint32 num, const char* keys[]) {
    for (uint32 i = 0; i < num; ++i) {
      SyntaxTree  tree;
      Parser      p;
      if (parse(std::string(keys[i]), tree, boost::bind(&Parser::callback, &p, _1, _2))) {
        DynamicFSMPtr fsm = p.getFsm();
        ProgramPtr prog = createProgram(*fsm);
        Grep.init(prog, firstBytes(*fsm), 1);
        break;
      }
      else {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("couldn't parse keys[" << i << "], " << keys[i]);
      }
    }
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
