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

SCOPE_TEST(codeGen2DiscoverVertex) {
  DynamicFSM fsm(2);
  fsm[boost::add_edge(0, 1, fsm).first].reset(new LitState('a'));
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(fsm)));
  CodeGenVisitor2 vis(cg);

  vis.discover_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(1u, cg->NumDiscovered);
  SCOPE_ASSERT_EQUAL(0u, cg->DiscoverRanks[1]);

  vis.discover_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(2u, cg->NumDiscovered);
  SCOPE_ASSERT_EQUAL(1u, cg->DiscoverRanks[0]);
}

SCOPE_TEST(codeGen2FinishVertex) {
  DynamicFSM fsm(5);
  fsm[boost::add_edge(0, 1, fsm).first].reset(new LitState('a'));
  fsm[boost::add_edge(1, 2, fsm).first].reset(new LitState('b'));
  fsm[boost::add_edge(2, 3, fsm).first].reset(new LitState('c'));
  fsm[boost::add_edge(2, 4, fsm).first].reset(new LitState('d'));
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(fsm)));
  CodeGenVisitor2 vis(cg);

  cg->NumDiscovered = 3;
  cg->DiscoverRanks[0] = 0;
  cg->DiscoverRanks[1] = 1;
  cg->DiscoverRanks[2] = 2;
  cg->DiscoverRanks[3] = 3;
  cg->DiscoverRanks[4] = 4;

  vis.finish_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].first);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].second);

  vis.finish_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[1].first);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[1].second);

  vis.finish_vertex(2, fsm);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[2].first);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[2].second);

  vis.finish_vertex(3, fsm);
  SCOPE_ASSERT_EQUAL(3u, cg->Snippets[3].first);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[3].second);
  
  vis.finish_vertex(4, fsm);
  SCOPE_ASSERT_EQUAL(5u, cg->Snippets[4].first);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[4].second);
}

SCOPE_TEST(alternationCodeGen2FinishVertex) {
  DynamicFSM fsm(3);
  edge(0, 1, fsm, new LitState('a'));
  edge(0, 2, fsm, new LitState('b'));
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(fsm)));
  CodeGenVisitor2 vis(cg);
  
  cg->NumDiscovered = 3;
  cg->DiscoverRanks[0] = 0;
  cg->DiscoverRanks[1] = 1;
  cg->DiscoverRanks[2] = 2;

  vis.finish_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].first);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[0].second);
  
  vis.finish_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[1].first);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[1].second);
  
  vis.finish_vertex(2, fsm);
  SCOPE_ASSERT_EQUAL(3u, cg->Snippets[2].first);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[2].second);
}

SCOPE_TEST(twoStateBetterLayout) {
  DynamicFSM fsm(2);
  edge(0, 1, fsm, new LitState('a'));
  
  ProgramPtr p = createProgram2(fsm);
  Program& prog(*p);
  SCOPE_ASSERT_EQUAL(2u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[1]);
}

SCOPE_TEST(alternationBetterLayout) {
  DynamicFSM fsm(3);
  edge(0, 1, fsm, new LitState('a'));
  edge(0, 2, fsm, new LitState('b'));
  ProgramPtr p = createProgram2(fsm);
  Program& prog(*p);
  
  // std::cout << "alternationBetterLayout" << '\n' << prog;
  
  SCOPE_ASSERT_EQUAL(5u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(3), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[4]);
}

void createTrie(DynamicFSM& fsm) {
  edge(0, 1, fsm, new LitState('a'));
  edge(1, 2, fsm, new LitState('b'));
  edge(2, 3, fsm, new LitState('l'));
  edge(3, 4, fsm, new LitState('e'));
  edge(2, 5, fsm, new LitState('e'));
  edge(5, 6, fsm, new LitState('t'));
  edge(0, 7, fsm, new LitState('b'));
  edge(7, 8, fsm, new LitState('i'));
  edge(8, 9, fsm, new LitState('t'));
  edge(9, 10, fsm, new LitState('e'));
}

SCOPE_TEST(betterLayout) {
  // a
  //  b
  //   le
  //   et
  // b
  //  ite

  DynamicFSM fsm(11);
  createTrie(fsm);

  ProgramPtr p = createProgram2(fsm);
  Program& prog(*p);
  // std::cout << "betterLayout\n" << prog;
  SCOPE_ASSERT_EQUAL(16u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(5), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(10), prog[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(13), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('i'), prog[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('t'), prog[7]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('e'), prog[8]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[9]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('l'), prog[10]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('e'), prog[11]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[12]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('e'), prog[13]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('t'), prog[14]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[15]);
}

// SCOPE_TEST(testSpecialVisit) {
//   DynamicFSM fsm(11);
//   createTrie(fsm);
//   boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(fsm)));
//   CodeGenVisitor2 vis(cg);
//   specialVisit(fsm, 0, vis);
// }
