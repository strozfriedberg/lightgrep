#include <scope/test.h>

#include <iostream>

#include "utility_impl.h"
#include "states.h"
#include "MockCallback.h"

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
  
  SCOPE_ASSERT_EQUAL(6u, program->size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(4), (*program)[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), (*program)[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('c'), (*program)[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), (*program)[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), (*program)[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(2), (*program)[5]);
}

SCOPE_TEST(keywordLabels) {
  DynamicFSM fsm(4);
  edge(0, 1, fsm, new LitState('a', 0));
  edge(0, 2, fsm, new LitState('b'));
  edge(2, 3, fsm, new LitState('c', 1));
  ProgramPtr program = createProgram(fsm);
  SCOPE_ASSERT_EQUAL(8u, program->size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(4), (*program)[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), (*program)[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(0), (*program)[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), (*program)[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), (*program)[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('c'), (*program)[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(1), (*program)[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), (*program)[7]);
}

SCOPE_TEST(twoFixedStrings) {
  std::vector< std::string > kws;
  kws.push_back("one");
  kws.push_back("two");
  DynamicFSMPtr fsm = createDynamicFSM(kws);
  SCOPE_ASSERT_EQUAL(7u, num_vertices(*fsm));
  // hmm... keeping things on the edges makes it shockingly hard to test
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
  CodeGenVisitor vis(cg);

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
  CodeGenVisitor vis(cg);

  cg->NumDiscovered = 3;
  cg->DiscoverRanks[0] = 0;
  cg->DiscoverRanks[1] = 1;
  cg->DiscoverRanks[2] = 2;
  cg->DiscoverRanks[3] = 3;
  cg->DiscoverRanks[4] = 4;

  vis.finish_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].Start);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].numTotal());

  vis.finish_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[1].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[1].numTotal());

  vis.finish_vertex(2, fsm);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[2].Start);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[2].numTotal());

  vis.finish_vertex(3, fsm);
  SCOPE_ASSERT_EQUAL(3u, cg->Snippets[3].Start);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[3].numTotal());
  
  vis.finish_vertex(4, fsm);
  SCOPE_ASSERT_EQUAL(5u, cg->Snippets[4].Start);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[4].numTotal());
}

SCOPE_TEST(alternationCodeGen2FinishVertex) {
  DynamicFSM fsm(3);
  edge(0, 1, fsm, new LitState('a'));
  edge(0, 2, fsm, new LitState('b'));
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(fsm)));
  CodeGenVisitor vis(cg);
  
  cg->NumDiscovered = 3;
  cg->DiscoverRanks[0] = 0;
  cg->DiscoverRanks[1] = 1;
  cg->DiscoverRanks[2] = 2;

  vis.finish_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[0].numTotal());
  
  vis.finish_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[1].Start);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[1].numTotal());
  
  vis.finish_vertex(2, fsm);
  SCOPE_ASSERT_EQUAL(3u, cg->Snippets[2].Start);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[2].numTotal());
}

SCOPE_TEST(twoStateBetterLayout) {
  DynamicFSM fsm(2);
  edge(0, 1, fsm, new LitState('a'));
  
  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);
  SCOPE_ASSERT_EQUAL(2u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[1]);
}

SCOPE_TEST(alternationBetterLayout) {
  DynamicFSM fsm(3);
  Transition* t1(new LitState('a', 0)),
            * t2(new LitState('b', 0));
  edge(0, 1, fsm, t1);
  edge(0, 2, fsm, t2);
  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);
  
  // std::cout << "alternationBetterLayout" << '\n' << prog;
  
  SCOPE_ASSERT_EQUAL(7u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(4), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(0), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(0), prog[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[6]);
}

void createTrie(DynamicFSM& fsm) {
  edge(0, 1, fsm, new LitState('a'));
  edge(1, 2, fsm, new LitState('b'));
  edge(2, 3, fsm, new LitState('l'));
  edge(3, 4, fsm, new LitState('e', 0));
  edge(2, 5, fsm, new LitState('e'));
  edge(5, 6, fsm, new LitState('t', 1));
  edge(0, 7, fsm, new LitState('b'));
  edge(7, 8, fsm, new LitState('i'));
  edge(8, 9, fsm, new LitState('t'));
  edge(9, 10, fsm, new LitState('e', 2));
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

  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);
  // std::cout << "betterLayout\n" << prog;
  SCOPE_ASSERT_EQUAL(19u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(5), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(11), prog[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(15), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('i'), prog[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('t'), prog[7]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('e'), prog[8]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(2), prog[9]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[10]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('l'), prog[11]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('e'), prog[12]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(0), prog[13]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[14]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('e'), prog[15]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('t'), prog[16]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(1), prog[17]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[18]);
}

SCOPE_TEST(testInitVM) {
  std::vector<std::string> keys;
  SearchInfo info;
  keys.push_back("one");
  keys.push_back("two");
  boost::shared_ptr<Vm> search = initVM(keys, info);
               //012345678901234
  byte text[] = "a onetwothree";
  MockCallback cb;
  SCOPE_ASSERT(!search->search(&text[0], &text[15], 0, cb));
  SCOPE_ASSERT_EQUAL(2u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), cb.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 3, 1), cb.Hits[1]);
}

SCOPE_TEST(testPivotTransitions) {
  DynamicFSM fsm(4);
  edge(0, 1, fsm, new LitState('a', 0));
  edge(0, 2, fsm, new LitState('a', 1));
  edge(0, 2, fsm, new LitState('z'));
  edge(0, 3, fsm, new LitState('z'));
  std::vector< std::set< DynamicFSM::vertex_descriptor > > tbl = pivotStates(0, fsm);
  SCOPE_ASSERT_EQUAL(256u, tbl.size());
  for (uint32 i = 0; i < 256; ++i) {
    if (i == 'a') {
      SCOPE_ASSERT_EQUAL(2u, tbl[i].size());
      SCOPE_ASSERT(tbl[i].find(1) != tbl[i].end());
      SCOPE_ASSERT(tbl[i].find(2) != tbl[i].end());
    }
    else if (i == 'z') {
      SCOPE_ASSERT_EQUAL(2u, tbl[i].size());
      SCOPE_ASSERT(tbl[i].find(2) != tbl[i].end());
      SCOPE_ASSERT(tbl[i].find(3) != tbl[i].end());
    }
    else {
      SCOPE_ASSERT(tbl[i].empty());
    }
  }
}
