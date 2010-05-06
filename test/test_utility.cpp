#include <scope/test.h>

#include <iostream>

#include "utility_impl.h"
#include "states.h"

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
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(1), cg->Program[0]);

  vis.finish_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(3u, cg->Program.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), cg->Program[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), cg->Program[2]);
}

void edge(DynamicFSM::vertex_descriptor source, DynamicFSM::vertex_descriptor target, DynamicFSM& fsm, Transition* tPtr) {
  fsm[boost::add_edge(source, target, fsm).first].reset(tPtr);
}

SCOPE_TEST(acOrbcProgram) {
  DynamicFSM fsm(4);
  fsm[boost::add_edge(0, 1, fsm).first].reset(new LitState('a'));
  fsm[boost::add_edge(0, 2, fsm).first].reset(new LitState('b'));
  fsm[boost::add_edge(1, 3, fsm).first].reset(new LitState('c'));
  fsm[boost::add_edge(2, 3, fsm).first].reset(new LitState('c'));
  boost::shared_ptr< std::vector<Instruction> > program = createProgram(fsm);
  // for (uint32 i = 0; i < program->size(); ++i) {
  //   std::cout << i << '\t' << (*program)[i].toString() << std::endl;
  // }
  SCOPE_ASSERT_EQUAL(8u, program->size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(2), (*program)[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(4), (*program)[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), (*program)[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(6), (*program)[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), (*program)[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(6), (*program)[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('c'), (*program)[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), (*program)[7]);
}

SCOPE_TEST(keywordLabels) {
  DynamicFSM fsm(4);
  edge(0, 1, fsm, new LitState('a', 0));
  edge(0, 2, fsm, new LitState('b'));
  edge(2, 3, fsm, new LitState('c', 1));
  ProgramPtr program = createProgram(fsm);
  SCOPE_ASSERT_EQUAL(10u, program->size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(2), (*program)[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(5), (*program)[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), (*program)[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeSaveLabel(0), (*program)[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), (*program)[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), (*program)[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(7), (*program)[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('c'), (*program)[7]);
  SCOPE_ASSERT_EQUAL(Instruction::makeSaveLabel(1), (*program)[8]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), (*program)[9]);
}

SCOPE_TEST(twoFixedStrings) {
  std::vector< std::string > kws;
  kws.push_back("one");
  kws.push_back("two");
  DynamicFSMPtr fsm = createDynamicFSM(kws);
  SCOPE_ASSERT_EQUAL(7u, num_vertices(*fsm));
}

SCOPE_TEST(firstBitset) {
  DynamicFSM fsm(3);
  edge(0, 1, fsm, new LitState('A'));
  edge(0, 2, fsm, new LitState('B'));

  ByteSet accepted = firstBytes(fsm);
  for (unsigned int i = 0; i < 256; ++i) {
    if (i == 'A' || i == 'B') {
      SCOPE_ASSERT(accepted[i]);
    }
    else {
      SCOPE_ASSERT(!accepted[i]);
    }
  }
}

SCOPE_TEST(simpleCollapse) {
  std::vector< std::string > kws;
  kws.push_back("ab");
  kws.push_back("ac");
  DynamicFSMPtr fsm = createDynamicFSM(kws);
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(*fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, *fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(1, *fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, *fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, *fsm));
}
