#include <scope/test.h>

#include <boost/bind.hpp>

#include "utility.h"
#include "states.h"
#include "dfasearch.h"

#include <ostream>

class HitCollector: public HitCallback {
public:
  HitCollector(): HitCallback() {}
  virtual ~HitCollector() {}
  
  void collect(const SearchHit& hit) { Hits.push_back(hit); }

  std::vector<SearchHit> Hits;
};

SCOPE_TEST(dfaSearch) {
  DynamicFSM dynfsm(3);
  dynfsm[boost::add_edge(0, 1, dynfsm).first].reset(new LitState('a'));
  dynfsm[boost::add_edge(1, 2, dynfsm).first].reset(new LitState('b'));
  boost::shared_ptr<StaticFSM> fsm(convert_to_static(dynfsm));
  
  DFASearch search;
  search.init(fsm);

  byte mem[] = {'1', 'a', 'b', 'c', 'a', 'a', 'b'};
  HitCollector hc;
  search.search(mem, mem+7, 0, hc);
  SCOPE_ASSERT_EQUAL(2u, hc.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2), hc.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 2), hc.Hits[1]);
}
