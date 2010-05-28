
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

typedef std::vector< DynamicFSM::vertex_descriptor > VList;

std::ostream& operator<<(std::ostream& out, const VList& list) {
  out << '{';
  for (VList::const_iterator it(list.begin()); it != list.end(); ++it) {
    if (it != list.begin()) {
      out << ", ";
    }
    out << *it;
  }
  out << '}';
  return out;
}

struct Fragment {
  Fragment(VList in, const Node& n): InList(in), N(n) {}
  Fragment(DynamicFSM::vertex_descriptor in, const Node& n): N(n) { InList.push_back(in); }
  Fragment(VList in, const Node& n, const VList& out):
    InList(in), OutList(out), N(n) {}

  std::vector< DynamicFSM::vertex_descriptor > InList, OutList;
  Node N;

  void addToOut(DynamicFSM::vertex_descriptor v) {
    add(v, OutList);
  }

  void addToIn(DynamicFSM::vertex_descriptor v) {
    add(v, InList);
  }

  void add(DynamicFSM::vertex_descriptor v, VList& list) {
    if (std::find(list.begin(), list.end(), v) == list.end()) {
      list.push_back(v);
    }
  }

  void merge(const Fragment& f) {
    // std::cout << "merge in " << InList << ", " << f.InList << ", out " << OutList << ", " << f.OutList << std::endl;
    for (VList::const_iterator it(f.InList.begin()); it != f.InList.end(); ++it) {
      add(*it, InList);
    }
    for (VList::const_iterator it(f.OutList.begin()); it != f.OutList.end(); ++it) {
      add(*it, OutList);
    }
    // std::cout << "merged in " << InList << ", out " << OutList << std::endl;
  }
};

class Parser {
public:
  Parser(): Fsm(new DynamicFSM(1)) {}

  void callback(const std::string& type, Node n);

  void patch(const VList& sources, const VList& targets, DynamicFSM& fsm) {
    // std::cout << "patch " << sources << "->" << targets << std::endl;
    for (VList::const_iterator srcIt(sources.begin()); srcIt != sources.end(); ++srcIt) {
      for (VList::const_iterator targetIt(targets.begin()); targetIt != targets.end(); ++targetIt) {
        // std::cout << "Making edge (" << *srcIt << ", " << *targetIt << ")" << std::endl;
        boost::add_edge(*srcIt, *targetIt, fsm);
      }
    }
  }

  void addAtom(const Node& n) {
    Stack.push(Fragment(boost::add_vertex(*Fsm), n));
  }

  void alternate(const Node& n) {
    Fragment second = Stack.top();
    Stack.pop();
    Fragment first = Stack.top();
    Stack.pop();
    // std::cout << "alternation, in " << second.InList << ", " << first.InList << ", out " << second.OutList << ", " << first.OutList << std::endl;
    first.merge(second);
    first.N = n;
    Stack.push(first);
  }

  void concatenate(const Node& n) {
    Fragment second = Stack.top();
    Stack.pop();
    Fragment first = Stack.top();
    Stack.pop();
    if (first.OutList.empty()) {
      patch(first.InList, second.InList, *Fsm);
    }
    else {
      patch(first.OutList, second.InList, *Fsm);
    }
    Stack.push(Fragment(first.InList, n, second.OutList));
  }

  void finish(const Node&) {
    if (1 == Stack.size()) {
      Fragment path = Stack.top();
      Stack.pop();
      VList src;
      src.push_back(0);
      patch(src, path.InList, *Fsm);
    }
    else {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Final parse stack size should be 1, was " << Stack.size());
    }
  }

  DynamicFSMPtr getFsm() const { return Fsm; }

private:
  DynamicFSMPtr Fsm;
  std::stack< Fragment > Stack;
};

void Parser::callback(const std::string&, Node n) {
  // std::cout << type << std::endl;
  switch (n.Type) {
    case REGEXP:
      finish(n);
      break;
    case ALTERNATION:
      alternate(n);
      break;
    case CONCATENATION:
      concatenate(n);
      break;
    case ATOM:
      addAtom(n);
      break;
    default:
      break;
  }
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
