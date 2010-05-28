#include "parser.h"

#include "states.h"

#include <iostream>

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

void Fragment::add(DynamicFSM::vertex_descriptor v, VList& list) {
  if (std::find(list.begin(), list.end(), v) == list.end()) {
    list.push_back(v);
  }
}

void Fragment::merge(const Fragment& f) {
  // std::cout << "merge in " << InList << ", " << f.InList << ", out " << OutList << ", " << f.OutList << std::endl;
  for (VList::const_iterator it(f.InList.begin()); it != f.InList.end(); ++it) {
    add(*it, InList);
  }
  for (VList::const_iterator it(f.OutList.begin()); it != f.OutList.end(); ++it) {
    add(*it, OutList);
  }
  // std::cout << "merged in " << InList << ", out " << OutList << std::endl;
}


void Parser::patch(const VList& sources, const VList& targets, DynamicFSM& fsm) {
  // std::cout << "patch " << sources << "->" << targets << std::endl;
  for (VList::const_iterator srcIt(sources.begin()); srcIt != sources.end(); ++srcIt) {
    for (VList::const_iterator targetIt(targets.begin()); targetIt != targets.end(); ++targetIt) {
      // std::cout << "Making edge (" << *srcIt << ", " << *targetIt << ")" << std::endl;
      boost::add_edge(*srcIt, *targetIt, fsm);
    }
  }
}

void Parser::addAtom(const Node& n) {
  DynamicFSM& g(*Fsm);
  DynamicFSM::vertex_descriptor v = boost::add_vertex(g);
  g[v].reset(new LitState(n.Val));
  VList in, out;
  in.push_back(v);
  out.push_back(v);
  Stack.push(Fragment(in, n, out));
}

void Parser::alternate(const Node& n) {
  Fragment second = Stack.top();
  Stack.pop();
  Fragment first = Stack.top();
  Stack.pop();
  // std::cout << "alternation, in " << second.InList << ", " << first.InList << ", out " << second.OutList << ", " << first.OutList << std::endl;
  first.merge(second);
  first.N = n;
  Stack.push(first);
}

void Parser::concatenate(const Node& n) {
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

void Parser::finish(const Node&) {
  if (1 == Stack.size()) {
    Fragment path = Stack.top();
    Stack.pop();
    VList src;
    src.push_back(0);
    for (VList::const_iterator it(path.OutList.begin()); it != path.OutList.end(); ++it) {
      // std::cerr << "marking " << *it << " as a match" << std::endl;
      (*Fsm)[*it]->Label = 0;
    }
    patch(src, path.InList, *Fsm);
  }
  else {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("Final parse stack size should be 1, was " << Stack.size());
  }
}

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
