#include "parser.h"

#include "states.h"
#include "concrete_encodings.h"
#include "utility.h"

#include <iostream>
#include <cctype>

std::ostream& operator<<(std::ostream& out, const FastVList& list) {
  out << '{';
  if (list.List) {
    for (VList::const_iterator it(list.List->begin()); it != list.List->end(); ++it) {
      if (it != list.List->begin()) {
        out << ", ";
      }
      out << *it;
    }
  }
  else if (list.Single != 0xffffffff) {
    out << list.Single;
  }
  out << '}';
  return out;
}

std::ostream& operator<<(std::ostream& out, const Fragment& f) {
  out << "in " << f.InList << ", out " << f.OutList;
  return out;
}

FastVList::FastVList() {
  Single = 0xffffffff;
}

FastVList::FastVList(Graph::vertex_descriptor v) {
  Single = v;
}

FastVList::FastVList(const FastVList& x)
{
  if (x.Single != 0xffffffff) {
    Single = x.Single;
    if (x.List) {
      List.reset(new VList(*x.List));
    }
  }
}

FastVList& FastVList::operator=(const FastVList& x) {
  if (x.Single == 0xffffffff) {
    Single = 0xffffffff;
    List.reset();
  }
  else {
    if (x.List) {
      if (List) {
        *List = *x.List;
      }
      else {
        List.reset(new VList(*x.List));
      }
      Single = (*List)[0];
    }
    else {
      Single = x.Single;
      List.reset();
    }
  }
  return *this;
}

size_t FastVList::size() const {
  return Single == 0xffffffff ? 0: List ? List->size(): 1;
}

Graph::vertex_descriptor FastVList::operator[](unsigned int i) const {
  return List ? (*List)[i]: Single;
}

void FastVList::reset() {
  Single = 0xffffffff;
  if (List) {
    List.reset();
  }
}

void FastVList::reset(Graph::vertex_descriptor v) {
  Single = v;
  if (List) {
    List.reset();
  }
}

void FastVList::add(Graph::vertex_descriptor v) {
  if (Single == 0xffffffff) {
    Single = v;
  }
  else {
    if (!List) {
      List.reset(new VList(1, Single));
    }
    if (std::find(List->begin(), List->end(), v) == List->end()) {
      List->push_back(v);
    }
  }
}

void FastVList::merge(const FastVList& x) {
  if (x.Single != 0xffffffff) {
    if (x.List) {
      if (!List) {
        if (Single == 0xffffffff) {
          List.reset(new VList(*x.List));
          Single = (*List)[0];
          return;
        }
        else {
          List.reset(new VList(1, Single));
        }
      }
      for (VList::const_iterator it(x.List->begin()); it != x.List->end(); ++it) {
        if (std::find(List->begin(), List->end(), *it) == List->end()) {
          List->push_back(*it);
        }
      }
    }
    else if (Single == 0xffffffff) {
      Single = x.Single;
    }
    else {
      if (!List) {
        List.reset(new VList(1, Single));
      }
      if (std::find(List->begin(), List->end(), x.Single) == List->end()) {
        List->push_back(x.Single);
      }
    }
  }
}

void FastVList::patch(const FastVList& targets, Graph& fsm) const {
  if (Single == 0xffffffff || targets.Single == 0xffffffff) {
    return;
  }
  if (List) {
    if (targets.List) {
      for (VList::const_iterator srcIt(List->begin()); srcIt != List->end(); ++srcIt) {
        for (VList::const_iterator targetIt(targets.List->begin()); targetIt != targets.List->end(); ++targetIt) {
          // std::cout << "Making edge (" << *srcIt << ", " << *targetIt << ")" << std::endl;
          addNewEdge(*srcIt, *targetIt, fsm);
        }
      }
    }
    else {
      for (VList::const_iterator srcIt(List->begin()); srcIt != List->end(); ++srcIt) {
        addNewEdge(*srcIt, targets.Single, fsm);
      }
    }
  }
  else if (targets.List) {
    for (VList::const_iterator targetIt(targets.List->begin()); targetIt != targets.List->end(); ++targetIt) {
      addNewEdge(Single, *targetIt, fsm);
    }
  }
  else {
    addNewEdge(Single, targets.Single, fsm);
  }
}

void Fragment::merge(const Fragment& f) {
  // std::cout << "merge in " << InList << ", " << f.InList << ", out " << OutList << ", " << f.OutList << std::endl;
  InList.merge(f.InList);
  OutList.merge(f.OutList);
  // std::cout << "merged in " << InList << ", out " << OutList << std::endl;
}

Parser::Parser():
  CaseSensitive(true),
  CurLabel(0),
  ReserveSize(0)
{
  for (unsigned int i = 0; i < 256; ++i) {
    LitFlyweights.push_back(TransitionPtr(new LitState(i)));
  }
  setEncoding(boost::shared_ptr<Encoding>(new Ascii));
  reset();
}

void Parser::reset() {
  IsGood = false;
  if (Fsm) {
    Fsm->clear();
    Fsm->addVertex();
  }
  else {
    Fsm.reset(new Graph(1));
//    Fsm.reset(new Graph(1, ReserveSize));
  }
  while (!Stack.empty()) {
    Stack.pop();
  }
  TempFrag.initFull(0, Node());
  Stack.push(TempFrag);
}

void Parser::setEncoding(const boost::shared_ptr<Encoding>& e) {
  Enc = e;
  TempBuf.reset(new byte[Enc->maxByteLength()]);
}

void Parser::setCaseSensitive(bool caseSensitive) {
  CaseSensitive = caseSensitive;
}

void Parser::setSizeHint(uint64 reserveSize) {
  ReserveSize = reserveSize;
}

void Parser::patch(const FastVList& sources, const FastVList& targets) {
  // std::cout << "patch " << sources << "->" << targets << std::endl;
  sources.patch(targets, *Fsm);
}

void Parser::patch(Fragment& first, const Fragment& second, const Node& n) {
  // Fragment ret(first.InList, n, second.OutList);
  // std::cout << "patching states" << std::endl;
  patch(first.OutList, second.InList);
  first.N = n;
  if (first.Skippable) {
    first.InList.merge(second.InList);
  }
  if (second.Skippable) {
    first.OutList.merge(second.OutList);
  }
  else {
    first.OutList = second.OutList;
  }
  first.Skippable = false;
}

void Parser::addElement(const Node&) {
  // don't really have to do anything here
}

void Parser::alternate(const Node& n) {
  Fragment second = Stack.top();
  Stack.pop();
  Fragment first = Stack.top();
  Stack.pop();
  // std::cout << "alternation, in " << second.InList << ", " << first.InList << ", out " << second.OutList << ", " << first.OutList << std::endl;
  first.merge(second);
  first.N = n;
  first.Skippable = first.Skippable || second.Skippable;
  Stack.push(first);
}

void Parser::concatenate(const Node& n) {
  TempFrag = Stack.top();
  Stack.pop();
  Fragment& first = Stack.top();
  patch(first, TempFrag, n);
}

void Parser::setLiteralTransition(TransitionPtr& state, byte val) {
  if (CaseSensitive || !std::isalpha(val)) {
    state = LitFlyweights[val];
  }
  else {
    state.reset(new EitherState(std::toupper(val), std::tolower(val)));
  }
}

void Parser::literal(const Node& n) {
  uint32 len = Enc->write(n.Val, TempBuf.get());
  if (0 == len) {
    // bad things
  }
  else {
    Graph& g(*Fsm);
    Graph::vertex_descriptor first,
                                  prev,
                                  last;
    first = prev = last = g.addVertex();
    setLiteralTransition(g[first], TempBuf[0]);
    for (uint32 i = 1; i < len; ++i) {
      last = g.addVertex();
      addNewEdge(prev, last, g);
      setLiteralTransition(g[last], TempBuf[i]);
      prev = last;
    }
    TempFrag.reset(n);
    TempFrag.addToIn(first);
    TempFrag.addToOut(last);
    Stack.push(TempFrag);
  }
}

void Parser::group(const Node&) {
  // don't really have to do anything here
}

void Parser::star(const Node& n) {
  plus(n);
  question(n);
}

void Parser::plus(const Node& n) {
  Fragment& repeat = Stack.top();
  repeat.N = n;
  patch(repeat.OutList, repeat.InList); // back-edges
}

void Parser::question(const Node&) {
  Fragment& optional = Stack.top();
  optional.Skippable = true;
}

void Parser::dot(const Node& n) {
  Graph::vertex_descriptor v = Fsm->addVertex();
  (*Fsm)[v].reset(new RangeState(0, 255));
  TempFrag.initFull(v, n);
  Stack.push(TempFrag);
}

void Parser::charClass(const Node& n, const std::string& lbl) {
  Graph::vertex_descriptor v = Fsm->addVertex();
  uint32 num = 0;
  byte first = 0, last = 0;
  for (uint32 i = 0; i < 256; ++i) {
    if (n.Bits.test(i)) {
      if (!num) {
        first = i;
      }
      if (++num == n.Bits.count()) {
        last = i;
        break;
      }
    }
    else {
      num = 0;
    }
  }
  if (num == n.Bits.count()) {
    (*Fsm)[v].reset(new RangeState(first, last));
  }
  else {
    (*Fsm)[v].reset(new CharClassState(n.Bits, lbl));
  }
  TempFrag.initFull(v, n);
  Stack.push(TempFrag);
}

void Parser::finish(const Node& n) {
  if (2 == Stack.size()) {
    TempFrag = Stack.top();
    Stack.pop();
    Fragment& start(Stack.top());
    patch(start, TempFrag, n);
    uint32 numOut = start.OutList.size();
    for (uint32 i = 0; i < numOut; ++i) {
      // std::cout << "marking " << *it << " as a match" << std::endl;
      Graph::vertex_descriptor v = start.OutList[i];
      if (0 == v) { // State 0 is not allowed to be a match state; i.e. 0-length REs are not allowed
        reset();
        return;
      }
      else {
        TransitionPtr final((*Fsm)[v]->clone()); // this is to make sure the transition isn't shared amongst other states
        final->Label = CurLabel;
        final->IsMatch = true;
        (*Fsm)[v] = final;
      }
    }
    // std::cout << "final is " << final << std::endl;
    IsGood = true;
    Stack.pop();
  }
  else {
    reset();
    return;
    // THROW_RUNTIME_ERROR_WITH_OUTPUT("Final parse stack size should be 2, was " << Stack.size());
  }
}

void Parser::callback(const std::string& type, const Node& n) {
  // std::cout << type << std::endl;
  type.size();
  switch (n.Type) {
    case Node::REGEXP:
      finish(n);
      break;
    case Node::ALTERNATION:
      alternate(n);
      break;
    case Node::CONCATENATION:
      concatenate(n);
      break;
    case Node::GROUP:
      group(n);
      break;
    case Node::STAR:
      star(n);
      break;
    case Node::PLUS:
      plus(n);
      break;
    case Node::QUESTION:
      question(n);
      break;
    case Node::ELEMENT:
      addElement(n);
      break;
    case Node::DOT:
      dot(n);
      break;
    case Node::CHAR_CLASS:
      charClass(n, type);
      break;
    case Node::LITERAL:
      literal(n);
      break;
    default:
      break;
  }
  // std::cout << "Stack size is " << Stack.size() << std::endl;
  // if (Stack.size() > 0) {
  //   std::cout << "top is " << Stack.top() << std::endl;
  // }
}
