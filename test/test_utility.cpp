#include <scope/test.h>

#include <iostream>

#include "utility_impl.h"
#include "states.h"

SCOPE_TEST(emptyFsm) {
  // what does it mean to have an empty FSM?
  boost::shared_ptr<StaticFSM> tight(convert_to_static(DynamicFSM()));
}

DynamicFSM createAfsm() {
  DynamicFSM fsm(2);
  std::pair<EdgeIdx, bool> edge(boost::add_edge(0, 1, fsm));
  SCOPE_ASSERT(edge.second);
  fsm[edge.first].reset(new LitState('a'));
  return fsm;
}

SCOPE_TEST(aFSM) {
  DynamicFSM fsm = createAfsm();

  boost::shared_ptr<StaticFSM> tight(convert_to_static(fsm));
  SCOPE_ASSERT(tight);
  SCOPE_ASSERT_EQUAL(2u, tight->numStates());
  SCOPE_ASSERT_EQUAL(1u, tight->numEdges());
  StaticFSM::StateT s0 = tight->getFirstState();
  StaticFSM::EdgeRange edges = tight->getEdges(s0);
  uint32 numEdges = 0;
  SCOPE_ASSERT_EQUAL((uint64)(tight->getRawBuffer() + 4), (uint64)edges.first);
  SCOPE_ASSERT_EQUAL((uint64)(tight->getRawBuffer() + 12), (uint64)edges.second);
  for (StaticFSM::EdgeIt cur = edges.first; cur != edges.second; ++cur) {
    ++numEdges;
  }
  SCOPE_ASSERT_EQUAL(1u, numEdges);

  byte text = 'a';
  SCOPE_ASSERT(tight->allowed(&text, &text+1, *edges.first));
  text = 'b';
  SCOPE_ASSERT(!tight->allowed(&text, &text+1, *edges.first));

  edges = tight->getEdges(edges.first->StateOffset);
  SCOPE_ASSERT_EQUAL(edges.first, edges.second);
  SCOPE_ASSERT_EQUAL(0u, (uint64)edges.first);
}

SCOPE_TEST(abFSM) {
  DynamicFSM fsm(3);
  fsm[boost::add_edge(0, 1, fsm).first].reset(new LitState('a'));
  fsm[boost::add_edge(1, 2, fsm).first].reset(new LitState('b'));

  boost::shared_ptr<StaticFSM> tight(convert_to_static(fsm));
  SCOPE_ASSERT(tight);
  SCOPE_ASSERT_EQUAL(3u, tight->numStates());
  SCOPE_ASSERT_EQUAL(2u, tight->numEdges());
  StaticFSM::StateT s0 = tight->getFirstState();
  StaticFSM::EdgeRange edges = tight->getEdges(s0);
  SCOPE_ASSERT_EQUAL(1u, edges.second - edges.first);
  byte text = 'a';
  SCOPE_ASSERT(tight->allowed(&text, &text+1, *edges.first));
  text = 'b';
  SCOPE_ASSERT(!tight->allowed(&text, &text+1, *edges.first));

  edges = tight->getEdges(edges.first->StateOffset);
  SCOPE_ASSERT_EQUAL(1u, edges.second - edges.first);
  SCOPE_ASSERT(tight->allowed(&text, &text+1, *edges.first));
  text = 'a';
  SCOPE_ASSERT(!tight->allowed(&text, &text+1, *edges.first));

  edges = tight->getEdges(edges.first->StateOffset);
  SCOPE_ASSERT_EQUAL(0u, edges.second - edges.first);
  SCOPE_ASSERT_EQUAL(edges.first, edges.second);
  SCOPE_ASSERT_EQUAL(0u, (uint64)edges.first);
}

SCOPE_TEST(aOrbAndC) {
  DynamicFSM fsm(4);
  fsm[boost::add_edge(0, 1, fsm).first].reset(new LitState('a'));
  fsm[boost::add_edge(0, 2, fsm).first].reset(new LitState('b'));
  fsm[boost::add_edge(1, 3, fsm).first].reset(new LitState('c'));
  fsm[boost::add_edge(2, 3, fsm).first].reset(new LitState('c'));

  boost::shared_ptr<StaticFSM> tight(convert_to_static(fsm));
  SCOPE_ASSERT(tight);
  SCOPE_ASSERT_EQUAL(4u, tight->numStates());
  SCOPE_ASSERT_EQUAL(4u, tight->numEdges());
  StaticFSM::StateT s0 = tight->getFirstState(),
                    s1, s2;
  StaticFSM::EdgeRange edges = tight->getEdges(s0);
  SCOPE_ASSERT_EQUAL(2u, edges.second - edges.first);
  byte text = 'a';
  SCOPE_ASSERT(tight->allowed(&text, &text+1, *edges.first));
  text = 'b';
  SCOPE_ASSERT(tight->allowed(&text, &text+1, *(edges.first+1)));
  s1 = edges.first->StateOffset;
  s2 = (edges.first+1)->StateOffset;
  edges = tight->getEdges(s1);
  SCOPE_ASSERT_EQUAL(1u, edges.second - edges.first);
  text = 'c';
  SCOPE_ASSERT(tight->allowed(&text, &text+1, *edges.first));
  edges = tight->getEdges(s2);
  SCOPE_ASSERT_EQUAL(1u, edges.second - edges.first);
  SCOPE_ASSERT_EQUAL(edges.first->StateOffset, tight->getLastState());
  text = 'c';
  SCOPE_ASSERT(tight->allowed(&text, &text+1, *edges.first));
  edges = tight->getEdges(edges.first->StateOffset);
  SCOPE_ASSERT_EQUAL(0u, edges.second - edges.first);
}

SCOPE_TEST(staticStateSize) {
  DynamicFSM fsm = createAfsm();
  SCOPE_ASSERT_EQUAL(4 + 8 + sizeof(LitState), staticStateSize(0, fsm));
  SCOPE_ASSERT_EQUAL(sizeof(uint32), staticStateSize(1, fsm));
}

SCOPE_TEST(codeGenDiscoveryVertex) {
  DynamicFSM fsm(2);
  fsm[boost::add_edge(0, 1, fsm).first].reset(new LitState('a'));
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(fsm)));
  CodeGenVisitor vis(cg);

  vis.discover_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].first);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[0].second);
  SCOPE_ASSERT_EQUAL(1u, cg->Guard);

   vis.discover_vertex(1, fsm);
   SCOPE_ASSERT_EQUAL(1u, cg->Snippets[1].first);
   SCOPE_ASSERT_EQUAL(2u, cg->Snippets[1].second);
   SCOPE_ASSERT_EQUAL(3u, cg->Guard);
}

SCOPE_TEST(codeGenFinishVertex) {
  DynamicFSM fsm(2);
  fsm[boost::add_edge(0, 1, fsm).first].reset(new LitState('a'));
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(fsm)));
  cg->Snippets[0] = std::make_pair(0u, 1u);
  cg->Snippets[1] = std::make_pair(1u, 2u);
  cg->Guard = 3;

  CodeGenVisitor vis(cg);
  vis.finish_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(1u, cg->Program.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(1), cg->Program[0]);
}
