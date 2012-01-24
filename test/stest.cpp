#include <algorithm>

#include "stest.h"
#include "patterninfo.h"
#include "utility.h"

void collector(void* userData, const LG_SearchHit* const hit) {
  STest* stest = static_cast<STest*>(userData);
  stest->Hits.push_back(*static_cast<const SearchHit* const>(hit));
}

Pattern makePattern(const std::string& s) {
  return Pattern(s);
}

STest::STest(const std::vector<std::string>& keys) {
  std::vector<Pattern> pats;
  std::transform(keys.begin(), keys.end(), std::back_inserter(pats), makePattern);
  init(pats);
}

void STest::init(const std::vector<Pattern>& kws) {
  Fsm = createGraph(kws, true, true);
  if (Fsm) {
    Prog = createProgram(*Fsm);
    Prog->First = firstBytes(*Fsm);
    Grep = VmInterface::create();
    Grep->init(Prog);
  }
}
