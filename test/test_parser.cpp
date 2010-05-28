
#include <scope/test.h>

#include "parser.h"
#include "dynamicFSM.h"

#include <iostream>
#include <stack>
// #include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>

void parseOutput(std::string type, Node n) {
  if (type == "whatever" && n.Type == ALTERNATION) {
    ;
  }
  // std::cout << type << ": " << n.Val << std::endl;
}

struct Fragment {
  Fragment(DynamicFSM::vertex_descriptor in, const Node& n): In(in), N(n) {}
  Fragment(DynamicFSM::vertex_descriptor in, const Node& n, const std::vector< DynamicFSM::vertex_descriptor >& out):
    In(in), OutList(out), N(n) {}

  DynamicFSM::vertex_descriptor In;
  std::vector< DynamicFSM::vertex_descriptor > OutList;
  Node N;

  void addToOut(DynamicFSM::vertex_descriptor v) {
    if (std::find(OutList.begin(), OutList.end(), v) == OutList.end()) {
      OutList.push_back(v);
    }
  }
};

class Parser {
public:
  Parser(): Fsm(new DynamicFSM(1)) {}

  void callback(const std::string& type, Node n);

  void addAtom(const Node& n) {
    Stack.push(Fragment(boost::add_vertex(*Fsm), n));
  }

  void concatenate(const Node& n) {
    Fragment second = Stack.top();
    Stack.pop();
    Fragment first = Stack.top();
    Stack.pop();
    if (first.OutList.empty()) {
      boost::add_edge(first.In, second.In, *Fsm);
    }
    else {
      for (std::vector< DynamicFSM::vertex_descriptor >::const_iterator out(first.OutList.begin()); out != first.OutList.end(); ++out) {
        boost::add_edge(*out, second.In, *Fsm);
      }
    }
    Stack.push(Fragment(first.In, n, second.OutList));
  }

  void finish(const Node&) {
    while (!Stack.empty()) {
      Fragment path = Stack.top();
      Stack.pop();
      boost::add_edge(0, path.In, *Fsm);
    }
  }

  DynamicFSMPtr getFsm() const { return Fsm; }

private:
  DynamicFSMPtr Fsm;
  std::stack< Fragment > Stack;
};

void Parser::callback(const std::string&, Node n) {
  switch (n.Type) {
    case ATOM:
      addAtom(n);
      break;
    case CONCATENATION:
      concatenate(n);
      break;
    case REGEXP:
      finish(n);
      break;
    default:
      break;
  }
}

SCOPE_TEST(parserText) {
  SyntaxTree tree;
  SCOPE_ASSERT(parse("dude|sweet", tree, &parseOutput));
  SCOPE_ASSERT_EQUAL(18u, tree.Store.size());
}

SCOPE_TEST(parseAorB) {
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b", tree, &parseOutput));
}

SCOPE_TEST(parseAorBorC) {
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b|c", tree, &parseOutput));
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
