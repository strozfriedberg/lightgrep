#include "stest.h"

#include "utility.h"
#include "compiler.h"

void collector(void* userData, const LG_SearchHit* const hit) {
  STest* stest = static_cast<STest*>(userData);
  stest->Hits.push_back(*static_cast<const SearchHit* const>(hit));
}

STest::STest(const char* key) {
  std::initializer_list<const char*> keys = { key };
  init(keys);
}

STest::STest(std::initializer_list<const char*> keys) {
  init(keys);
}

STest::STest(const std::vector<Pattern>& patterns) {
  std::vector<Pattern> pats(patterns);
  init(pats);
}

void STest::init(std::vector<Pattern>& pats) {
  Fsm = createGraph(pats, true, true);
  if (Fsm) {
    Prog = Compiler::createProgram(*Fsm);
    Prog->First = firstBytes(*Fsm);
    Grep = VmInterface::create();
    Grep->init(Prog);
  }
}

void STest::search(const byte* begin, const byte* end, uint64 offset) {
  Grep->search(begin, end, offset, collector, this);
  Grep->closeOut(collector, this);
}

void STest::startsWith(const byte* begin, const byte* end, uint64 offset) {
  Grep->startsWith(begin, end, offset, collector, this);
}
