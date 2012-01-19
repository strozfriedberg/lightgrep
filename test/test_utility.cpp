#include <scope/test.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/dynamic_property_map.hpp>

#include "codegen.h"
#include "compiler.h"
#include "states.h"
#include "mockcallback.h"

#include "test_helper.h"

/*
std::ostream& operator<<(std::ostream& os, const boost::shared_ptr<TransitionPtr>& p) {
  return os;
}
*/

/*
bool buildNFA(NFA& fsm, const std::string& dot) {
  std::istringstream is(dot);

  // Vertex properties
  typedef boost::property<boost::vertex_name_t, std::string> vertex_p;
  // Edge properties
  typedef boost::property<boost::edge_name_t, std::string> edge_p;
  // adjacency_list-based type
  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                vertex_p, edge_p> graph_t;

  // Construct an empty graph and prepare the dynamic_property_maps
  graph_t src(0);
  boost::dynamic_properties dp;

  boost::property_map<graph_t, boost::vertex_name_t>::type node_label =
    get(boost::vertex_name, src);
  dp.property("node_id", node_label);

  boost::property_map<graph_t, boost::edge_name_t>::type edge_label =
    get(boost::edge_name, src);
  dp.property("label", edge_label);

  if (!boost::read_graphviz(is, src, dp, "node_id")) return false;

  // Convert this graph to a NFA (annoying!)

  typedef boost::graph_traits<graph_t>::vertex vertex_t;
  typedef boost::graph_traits<graph_t>::edge_iterator edge_iterator;

  edge_iterator e, e_end;
  for (boost::tie(e, e_end) = boost::edges(src); e != e_end; ++e) {
    const unsigned int u = boost::lexical_cast<unsigned int>(
      boost::get(node_label, boost::source(*e, src)));

    const unsigned int v = boost::lexical_cast<unsigned int>(
      boost::get(node_label, boost::target(*e, src)));

    const char lit = boost::lexical_cast<char>(boost::get(edge_label, *e));

    edge(u, v, fsm, new LitState(lit));
  }

  return true;
}
*/

std::ostream& operator<<(std::ostream& out, const StateLayoutInfo& state) {
  out << "(" << state.Start << ", " << state.NumEval << ", " << state.NumOther << ", " << state.CheckIndex << ")";
  return out;
}

SCOPE_TEST(acOrbcProgram) {
  NFA fsm(4);

  edge(0, 1, fsm, new LitState('a')); // ac|bc
  edge(0, 2, fsm, new LitState('b'));
  edge(1, 3, fsm, new LitState('c'));
  edge(2, 3, fsm, new LitState('c'));
  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);

  SCOPE_ASSERT_EQUAL(10u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[0], 5), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('c'), prog[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeCheckHalt(1), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(&prog[6], 2), prog[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[8]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[9]);
}

SCOPE_TEST(keywordLabelsProgram) {
  NFA fsm(4);
  edge(0, 1, fsm, new LitState('a'));
  edge(0, 2, fsm, new LitState('b'));
  edge(2, 3, fsm, new LitState('c'));

  fsm[1].trans->Label = 0;
  fsm[3].trans->Label = 1;

  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);

  SCOPE_ASSERT_EQUAL(9u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[0], 5), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(0), prog[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('c'), prog[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(1), prog[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[7]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[8]);
}

SCOPE_TEST(twoFixedStrings) {
  std::vector< std::string > kws;
  kws.push_back("one");
  kws.push_back("two");
  GraphPtr fsm = createGraph(kws);
  SCOPE_ASSERT_EQUAL(7u, fsm->verticesSize());
}

SCOPE_TEST(twoUnicode) {
  std::vector< std::string > kws;
  kws.push_back("aa");
  kws.push_back("ab");
  GraphPtr fsm = createGraph(kws, CP_UCS16);
  NFA& g = *fsm;
  
  SCOPE_ASSERT_EQUAL(7u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(2));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(2, 0));
  SCOPE_ASSERT_EQUAL(4, g.outVertex(2, 1));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(3));
  SCOPE_ASSERT_EQUAL(6, g.outVertex(3, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(4));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(4));
  SCOPE_ASSERT_EQUAL(5, g.outVertex(4, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(5));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(5));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(6));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(6));

  SCOPE_ASSERT(!g[0].trans);
  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(!g[2].trans->IsMatch);
  SCOPE_ASSERT(!g[3].trans->IsMatch);
  SCOPE_ASSERT(!g[4].trans->IsMatch);
  SCOPE_ASSERT(g[5].trans->IsMatch);
  SCOPE_ASSERT(g[6].trans->IsMatch);

  ByteSet abs, ebs;

  const byte exp[] = { 'a', 0, 'a', 'b', 0, 0 };
  for (uint32 i = 1; i < g.verticesSize(); ++i) {
    abs.reset();
    ebs.reset();

    ebs[exp[i-1]] = true;
    g[i].trans->getBits(abs);

    SCOPE_ASSERT_EQUAL(ebs, abs);
  }
}

SCOPE_TEST(firstBitset) {
  NFA fsm(3);
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
  GraphPtr fsm = createGraph(kws);
  SCOPE_ASSERT_EQUAL(4u, fsm->verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm->outDegree(0));
  SCOPE_ASSERT_EQUAL(2u, fsm->outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm->outDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm->outDegree(3));
}

SCOPE_TEST(codeGen2DiscoverVertex) {
  NFA fsm(2);
  edge(0, 1, fsm, new LitState('a'));
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(fsm.verticesSize()));
  CodeGenVisitor vis(cg);

  vis.discover_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(1u, cg->NumDiscovered);
  SCOPE_ASSERT_EQUAL(0u, cg->DiscoverRanks[1]);

  vis.discover_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(2u, cg->NumDiscovered);
  SCOPE_ASSERT_EQUAL(1u, cg->DiscoverRanks[0]);
}

SCOPE_TEST(codeGen2FinishVertex) {
  NFA fsm(5);
  edge(0, 1, fsm, new LitState('a'));
  edge(1, 2, fsm, new LitState('b'));
  edge(2, 3, fsm, new LitState('c'));
  edge(2, 4, fsm, new LitState('d'));
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(fsm.verticesSize()));
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
  SCOPE_ASSERT_EQUAL(3u, cg->Snippets[2].numTotal());

  vis.finish_vertex(3, fsm);
  SCOPE_ASSERT_EQUAL(4u, cg->Snippets[3].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[3].numTotal());

  vis.finish_vertex(4, fsm);
  SCOPE_ASSERT_EQUAL(5u, cg->Snippets[4].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[4].numTotal());
}

SCOPE_TEST(alternationCodeGen2FinishVertex) {
  NFA fsm(3);
  edge(0, 1, fsm, new LitState('a'));
  edge(0, 2, fsm, new LitState('b'));
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(fsm.verticesSize()));
  CodeGenVisitor vis(cg);

  cg->NumDiscovered = 3;
  cg->DiscoverRanks[0] = 0;
  cg->DiscoverRanks[1] = 1;
  cg->DiscoverRanks[2] = 2;

  vis.finish_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].Start);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[0].numTotal());

  vis.finish_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[1].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[1].numTotal());

  vis.finish_vertex(2, fsm);
  SCOPE_ASSERT_EQUAL(3u, cg->Snippets[2].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[2].numTotal());
}

SCOPE_TEST(layoutWithCheckHalt) {
  NFA fsm(3);
  edge(0, 1, fsm, new LitState('a'));
  edge(1, 2, fsm, new LitState('b'));
  edge(2, 2, fsm, new LitState('b'));

  fsm[2].trans->Label = 0;
  fsm[2].trans->IsMatch = true;

  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(fsm.verticesSize()));
  CodeGenVisitor vis(cg);
  specialVisit(fsm, 0, vis);

  SCOPE_ASSERT_EQUAL(0u, cg->DiscoverRanks[0]);
  SCOPE_ASSERT_EQUAL(1u, cg->DiscoverRanks[1]);
  SCOPE_ASSERT_EQUAL(2u, cg->DiscoverRanks[2]);
  SCOPE_ASSERT_EQUAL(StateLayoutInfo(0u, 0u, 0u, NONE), cg->Snippets[0]);
  SCOPE_ASSERT_EQUAL(StateLayoutInfo(0u, 1u, 0u, NONE), cg->Snippets[1]);
  SCOPE_ASSERT_EQUAL(StateLayoutInfo(1u, 1u, 7u, 1u), cg->Snippets[2]);
}

SCOPE_TEST(twoStateBetterLayout) {
  NFA fsm(2);
  edge(0, 1, fsm, new LitState('a'));

  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);
  SCOPE_ASSERT_EQUAL(3u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[2]);
}

SCOPE_TEST(testCodeGenVisitorShouldBeJumpTableRange) {
  NFA g(4);
  edge(0, 1, g, new LitState('a'));
  edge(0, 2, g, new LitState('b'));
  edge(0, 3, g, new LitState('c'));
  edge(0, 4, g, new LitState('e'));

  boost::shared_ptr<CodeGenHelper> cgh(new CodeGenHelper(g.verticesSize()));
  CodeGenVisitor vis(cgh);

  SCOPE_ASSERT_EQUAL(6, vis.calcJumpTableSize(0, g, g.outDegree(0)));
  SCOPE_ASSERT_EQUAL(JUMP_TABLE_RANGE_OP, cgh->Snippets[0].Op);
  SCOPE_ASSERT_EQUAL(0, vis.calcJumpTableSize(1, g, g.outDegree(1)));
  SCOPE_ASSERT_EQUAL(0, vis.calcJumpTableSize(2, g, g.outDegree(2)));
  SCOPE_ASSERT_EQUAL(0, vis.calcJumpTableSize(3, g, g.outDegree(3)));
}

SCOPE_TEST(alternationBetterLayout) {
  NFA fsm(3);
  edge(0, 1, fsm, new LitState('a'));
  edge(0, 2, fsm, new LitState('b'));

  fsm[1].trans->Label = 0;
  fsm[2].trans->Label = 0;

  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);

  SCOPE_ASSERT_EQUAL(8u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[0], 4), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(0), prog[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(0), prog[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[7]);
}

void createTrie(NFA& fsm) {
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

  NFA fsm(11);
  createTrie(fsm);

  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);

  SCOPE_ASSERT_EQUAL(18u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[0], 8), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[4], 12), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(&prog[6], 14), prog[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[8]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('i'), prog[9]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('t'), prog[10]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('e'), prog[11]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('l'), prog[12]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('e'), prog[13]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('e'), prog[14]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('t'), prog[15]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[16]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[17]);
}

SCOPE_TEST(generateCheckHalt) {
  NFA fsm(2);
  edge(0, 1, fsm, new LitState('a'));
  edge(1, 1, fsm, new LitState('a'));

  fsm[1].trans->Label = 0;
  fsm[1].trans->IsMatch = true;

  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);
  SCOPE_ASSERT_EQUAL(1u, prog.NumChecked);

  // std::cout << prog;
  SCOPE_ASSERT_EQUAL(10u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(0), prog[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeCheckHalt(1), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[3]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[4], 9), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(&prog[6], 0), prog[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[8]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[9]);
}

SCOPE_TEST(testInitVM) {
  std::vector<std::string> keys;
  SearchInfo info;
  keys.push_back("one");
  keys.push_back("two");
  boost::shared_ptr<VmInterface> search = initVM(keys, info);
               //012345678901234
  byte text[] = "a onetwothree";

  std::vector<SearchHit> hits;
  SCOPE_ASSERT(!search->search(&text[0], &text[13], 0, &mockCallback, &hits));
  search->closeOut(&mockCallback, &hits);
  SCOPE_ASSERT_EQUAL(2u, hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 8, 1), hits[1]);
}

SCOPE_TEST(testPivotTransitions) {
  NFA fsm(5);
  edge(0, 1, fsm, new LitState('a', 0));
  edge(0, 2, fsm, new LitState('a', 1));
  edge(0, 3, fsm, new LitState('z'));
  edge(0, 4, fsm, new LitState('z'));
  std::vector< std::vector< NFA::VertexDescriptor > > tbl = pivotStates(0, fsm);
  SCOPE_ASSERT_EQUAL(256u, tbl.size());
  for (uint32 i = 0; i < 256; ++i) {
    if (i == 'a') {
      SCOPE_ASSERT_EQUAL(2u, tbl[i].size());
      SCOPE_ASSERT(std::find(tbl[i].begin(), tbl[i].end(), 1) != tbl[i].end());
      SCOPE_ASSERT(std::find(tbl[i].begin(), tbl[i].end(), 2) != tbl[i].end());
    }
    else if (i == 'z') {
      SCOPE_ASSERT_EQUAL(2u, tbl[i].size());
      SCOPE_ASSERT(std::find(tbl[i].begin(), tbl[i].end(), 3) != tbl[i].end());
      SCOPE_ASSERT(std::find(tbl[i].begin(), tbl[i].end(), 4) != tbl[i].end());
    }
    else {
      SCOPE_ASSERT(tbl[i].empty());
    }
  }
}

SCOPE_TEST(testBitVectorGeneration) {
  ByteSet    bits;
  bits.reset();
  bits.set('0');
  bits.set('2');
  bits.set('4');
  bits.set('8');
  NFA fsm(2);
  edge(0, 1, fsm, new CharClassState(bits));
  fsm[1].trans->Label = 0;
  fsm[1].trans->IsMatch = true;

  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);
  SCOPE_ASSERT_EQUAL(14u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeBitVector(), prog[0]);
  SCOPE_ASSERT_EQUAL(bits, *reinterpret_cast<ByteSet*>(&prog[1]));
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(0), prog[9]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[10]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[11]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[12]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[13]);
}

SCOPE_TEST(testMaxOutbound) {
  NFA fsm(5);
  edge(0, 1, fsm, new LitState('a'));
  edge(0, 2, fsm, new LitState('a'));
  edge(0, 3, fsm, new LitState('b'));
  edge(0, 4, fsm, new LitState('c'));
  std::vector< std::vector< NFA::VertexDescriptor > > tbl = pivotStates(0, fsm);
  SCOPE_ASSERT_EQUAL(2u, maxOutbound(tbl));
}

SCOPE_TEST(generateJumpTableRange) {
  NFA fsm(7); // a(b|c|d|g)f
  edge(0, 1, fsm, new LitState('a'));
  edge(1, 2, fsm, new LitState('b'));
  edge(1, 3, fsm, new LitState('c'));
  edge(1, 4, fsm, new LitState('d'));
  edge(1, 5, fsm, new LitState('g'));
  boost::shared_ptr<LitState> f(new LitState('f'));
  edge(2, 6, fsm, f);
  edge(3, 6, fsm, f);
  edge(4, 6, fsm, f);
  edge(5, 6, fsm, f);

  fsm[1].trans->Label = 0;
  fsm[6].trans->IsMatch = true;

  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);

  SCOPE_ASSERT_EQUAL(25u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(0), prog[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJumpTableRange('b', 'g'), prog[2]);
  SCOPE_ASSERT_EQUAL(10, *(uint32*) &prog[3]); // b
  SCOPE_ASSERT_EQUAL(10, *(uint32*) &prog[4]); // c
  SCOPE_ASSERT_EQUAL(10, *(uint32*) &prog[5]); // d
  SCOPE_ASSERT_EQUAL(0xffffffff, *(uint32*) &prog[6]); // e
  SCOPE_ASSERT_EQUAL(0xffffffff, *(uint32*) &prog[7]); // f
  SCOPE_ASSERT_EQUAL(10, *(uint32*) &prog[8]); // g
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[9]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('f'), prog[10]);
  SCOPE_ASSERT_EQUAL(Instruction::makeCheckHalt(1), prog[11]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[12]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[13]);
// From here on, this is garbage---maybe don't even test this?
/*
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('c'), prog[13]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(&prog[14], 9), prog[14]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('d'), prog[14]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(&prog[15], 9), prog[15]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('g'), prog[17]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(&prog[18], 9), prog[18]);
*/
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[23]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[24]);
}

SCOPE_TEST(generateJumpTableRangePreLabel) {
  NFA fsm(7); // a(b|c|d|g)fg + a(b|c|d|g)fh
  edge(0, 1, fsm, new LitState('a'));
  edge(1, 2, fsm, new LitState('b'));
  edge(1, 3, fsm, new LitState('c'));
  edge(1, 4, fsm, new LitState('d'));
  edge(1, 5, fsm, new LitState('g'));
  boost::shared_ptr<LitState> f(new LitState('f'));
  edge(2, 6, fsm, f);
  edge(3, 6, fsm, f);
  edge(4, 6, fsm, f);
  edge(5, 6, fsm, f);
  edge(6, 7, fsm, new LitState('g'));
  edge(6, 8, fsm, new LitState('h'));

  fsm[7].trans->Label = 0;
  fsm[8].trans->Label = 1;
  fsm[7].trans->IsMatch = true;
  fsm[8].trans->IsMatch = true;

  ProgramPtr p = createProgram(fsm);
  Program& prog(*p);

  SCOPE_ASSERT_EQUAL(34u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJumpTableRange('b', 'g'), prog[1]);
  SCOPE_ASSERT_EQUAL(9, *(uint32*) &prog[2]); // b
  SCOPE_ASSERT_EQUAL(9, *(uint32*) &prog[3]); // c
  SCOPE_ASSERT_EQUAL(9, *(uint32*) &prog[4]); // d
  SCOPE_ASSERT_EQUAL(0xffffffff, *(uint32*) &prog[5]); // e
  SCOPE_ASSERT_EQUAL(0xffffffff, *(uint32*) &prog[6]); // f
  SCOPE_ASSERT_EQUAL(9, *(uint32*) &prog[7]); // g
//  SCOPE_ASSERT_EQUAL(Instruction::makeLit('b'), prog[8]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('f'), prog[9]);
  SCOPE_ASSERT_EQUAL(Instruction::makeCheckHalt(1), prog[10]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[11], 28), prog[11]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(&prog[13], 24), prog[13]);
// intervening crap
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('g'), prog[24]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(0), prog[25]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[26]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[27]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('h'), prog[28]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(1), prog[29]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[30]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[31]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[32]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[33]);
}

SCOPE_TEST(testFirstChildNext) {
  NFA g;
  edge(0, 1, g, new LitState('0'));
  edge(1, 2, g, new LitState('0'));
  boost::shared_ptr<LitState> zero(new LitState('0'));
  edge(1, 3, g, zero);
  edge(2, 3, g, zero);

  g[1].trans->Label = 0;
  g[3].trans->IsMatch = true;

  ProgramPtr p = createProgram(g);
  Program& prog(*p);

  SCOPE_ASSERT_EQUAL(11u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('0'), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(0), prog[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[2], 5), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('0'), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('0'), prog[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeCheckHalt(1), prog[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[7]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[8]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[9]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[10]);
}

SCOPE_TEST(testFirstChildPrev) {
  NFA g;
  edge(0, 1, g, new LitState('0'));
  boost::shared_ptr<RangeState> dot(new RangeState(0, 255));
  edge(1, 2, g, dot);
  edge(2, 2, g, dot);
  boost::shared_ptr<LitState> zero(new LitState('0'));
  edge(2, 3, g, zero);
  edge(1, 3, g, zero);

  g[1].trans->Label = 0;
  g[3].trans->IsMatch = true;

  ProgramPtr p = createProgram(g);
  Program& prog(*p);

  SCOPE_ASSERT_EQUAL(16u, prog.size());
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('0'), prog[0]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLabel(0), prog[1]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[2], 10), prog[2]);
  SCOPE_ASSERT_EQUAL(Instruction::makeAny(), prog[4]);
  SCOPE_ASSERT_EQUAL(Instruction::makeCheckHalt(1), prog[5]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFork(&prog[6], 10), prog[6]);
  SCOPE_ASSERT_EQUAL(Instruction::makeJump(&prog[8], 4), prog[8]);
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('0'), prog[10]);
  SCOPE_ASSERT_EQUAL(Instruction::makeCheckHalt(2), prog[11]);
  SCOPE_ASSERT_EQUAL(Instruction::makeMatch(), prog[12]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[13]);
  SCOPE_ASSERT_EQUAL(Instruction::makeHalt(), prog[14]);
  SCOPE_ASSERT_EQUAL(Instruction::makeFinish(), prog[15]);
}

