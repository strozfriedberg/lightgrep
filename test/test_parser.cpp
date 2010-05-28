
#include <scope/test.h>

#include "parser.h"
#include "dynamicFSM.h"

#include <iostream>
#include <stack>
// #include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>

void parseOutput(std::string type, Node n) {
  std::cout << type << ": " << n.Val << std::endl;
}

SCOPE_TEST(parseAorB) {
  Parser     p;
  SyntaxTree tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|b", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
}

SCOPE_TEST(parseAorBorC) {
  Parser     p;
  SyntaxTree tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|b|c", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(3u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
}

SCOPE_TEST(parseAB) {
  Parser     p;
  SyntaxTree tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
}

SCOPE_TEST(parseAlternationAndConcatenation) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|bc", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
}

SCOPE_TEST(parseGroup) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a(b|c)", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
}

// 
// namespace qi = boost::spirit::qi;
// 
// namespace custom_parser { BOOST_SPIRIT_TERMINAL(iter_pos); }
// 
// enum {
//   ALTERNATE = 1,
//   CONCATENATE,
//   LITERAL,
//   DOT,
//   PARENTHESIS,
//   QUESTION,
//   STAR,
//   PLUS
// };
// 
// struct ReNode {
//   int Type,
//       N,
//       Ch;
// 
//   std::vector<ReNode> Children;
// };
// 
// void whole(std::string const& s) {
//   std::cerr << "whole: '" << s << '\'' << std::endl;
// }
// 
// void fixed(std::string const& s) {
//   std::cerr << "fixed: '" << s << '\'' << std::endl;
// }
// 
// template<typename IterType>
// struct Regrammar: qi::grammar<IterType, std::string()> {
//   
//   Regrammar(): Regrammar::base_type(Regexp) {
//     Regexp %= ((Fixed >> qi::lit('|') >> Fixed) | Fixed)[&whole];
//     Fixed %= (+qi::alnum)[&fixed];
//     // Regexp[&output];
//     // Alt = (Concat | (Alt >> '|' >> Concat));
//     // Concat = (Repeat | (Concat >> Repeat));
//     // Repeat = Single;
//     // Single = ('(' >> Alt >> ')') | qi::print;
//   }
// 
//   qi::rule<IterType, std::string()> Regexp;
//   qi::rule<IterType, std::string()> Fixed;
//                                // Alt,
//                                // Concat,
//                                // Repeat,
//                                // Single;
// };
// 
// SCOPE_TEST(parserTest) {
// 
//   Regrammar<std::string::const_iterator> g;
//   std::string text2("what|ever|dude|lebowski");
// 
//   std::string::const_iterator b = text2.begin(),
//                               e = text2.end();
// 
//   std::string result;
// 
//   // SCOPE_ASSERT(qi::parse(b, e, g, result));
//   SCOPE_ASSERT(qi::parse(b, e, g, result));
//   SCOPE_ASSERT_EQUAL(text2, result);
// }
