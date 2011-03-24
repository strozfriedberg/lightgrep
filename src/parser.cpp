#include "parser.h"

#include "states.h"
#include "concrete_encodings.h"
#include "utility.h"

#include <iostream>
#include <utility>

std::ostream& operator<<(std::ostream& out, const InListT& list) {
  out << '[';
  for (InListT::const_iterator it(list.begin()); it != list.end(); ++it) {
    if (it != list.begin()) {
      out << ", ";
    }
    out << *it;
  }
  out << ']';
  return out;
}

std::ostream& operator<<(std::ostream& out, const OutListT& list) {
  out << '[';
  for (OutListT::const_iterator i(list.begin()); i != list.end(); ++i) {
    if (i != list.begin()) {
      out << ", ";
    }

    out << '(' << i->first << ',' << i->second << ')';
  }
  out << ']';
  return out;
}

std::ostream& operator<<(std::ostream& out, const Fragment& f) {
  out << "in " << f.InList << ", out " << f.OutList;
  return out;
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

void Parser::addElement(const Node&) {
  // don't really have to do anything here
}

void Parser::setLiteralTransition(TransitionPtr& state, byte val) {
  if (CaseSensitive || !std::isalpha(val)) {
// FIXME: Labeled vertices can't be shared. We don't know which will be
// labeled (permanently) until after walking back labels. If the memory
// we were saving this way was really important, we need to figure out
// something else to do here.
//    state = LitFlyweights[val];
    state = TransitionPtr(new LitState(val));
  }
  else {
    state.reset(new EitherState(std::toupper(val), std::tolower(val)));
  }
}

void Parser::patch_pre(OutListT& src, const InListT& dst) {
  // make an edge from each vertex in src to each vertex in dst, putting
  // these edges before the src vertex insertion points
  for (OutListT::iterator oi(src.begin()); oi != src.end(); ++oi) {
    uint32 pos = oi->second;
    for (InListT::const_iterator ii(dst.begin()); ii != dst.end(); ++ii) {
      Fsm->addEdgeAt(oi->first, *ii, pos++);
    }
    *oi = std::make_pair(oi->first, pos);
  }
}

void Parser::patch_post(const OutListT& src, const InListT& dst) {
  // make an edge from each vertex in src to each vertex in dst, putting
  // these edges after the src vertex insertion points
  for (OutListT::const_iterator oi(src.begin()); oi != src.end(); ++oi) {
    uint32 pos = oi->second;
    for (InListT::const_iterator ii(dst.begin()); ii != dst.end(); ++ii) {
      Fsm->addEdgeAt(oi->first, *ii, pos++);
    }
  }
}

void Parser::literal(const Node& n) {
  uint32 len = Enc->write(n.Val, TempBuf.get());
  if (0 == len) {
    // bad things
  }
  else {
    Graph& g(*Fsm);
    Graph::vertex first, prev, last;
    first = prev = last = g.addVertex();
    setLiteralTransition(g[first], TempBuf[0]);
    for (uint32 i = 1; i < len; ++i) {
      last = g.addVertex();
      addNewEdge(prev, last, g);
      setLiteralTransition(g[last], TempBuf[i]);
      prev = last;
    }
    TempFrag.reset(n);
    TempFrag.InList.push_back(first);
    TempFrag.OutList.push_back(std::make_pair(last, 0));
    Stack.push(TempFrag);
  }
}

void Parser::dot(const Node& n) {
  Graph::vertex v = Fsm->addVertex();
  (*Fsm)[v].reset(new RangeState(0, 255));
  TempFrag.initFull(v, n);
  Stack.push(TempFrag);
}

void Parser::charClass(const Node& n, const std::string& lbl) {
  Graph::vertex v = Fsm->addVertex();
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

void Parser::question(const Node&) {
  Fragment& optional = Stack.top();
  if (optional.Skippable > optional.InList.size()) {
    optional.Skippable = optional.InList.size(); 
  }
}

void Parser::question_ng(const Node&) {
  Fragment& optional = Stack.top();
  optional.Skippable = 0;
}

void Parser::plus(const Node& n) {
  Fragment& repeat = Stack.top();
  repeat.N = n;
  
  // make back edges
  patch_pre(repeat.OutList, repeat.InList);
}

void Parser::plus_ng(const Node& n) {
  Fragment& repeat = Stack.top();
  repeat.N = n;

  // make back edges
  patch_post(repeat.OutList, repeat.InList);
}

void Parser::star(const Node& n) {
  plus(n);
  question(n);
}

void Parser::star_ng(const Node& n) {
  plus_ng(n);
  question_ng(n);
}

void Parser::group(const Node&) {
  // nothing to do here
}

void Parser::alternate(const Node& n) {
  Fragment second = Stack.top();
  Stack.pop();
  Fragment first = Stack.top();
  Stack.pop();

  if (first.Skippable != NOSKIP) {
    // leave first.Skippable unchanged
  }
  else if (second.Skippable != NOSKIP) {
    first.Skippable = first.InList.size() + second.Skippable;
  }
  else {
    first.Skippable = NOSKIP;
  }

  first.InList.insert(first.InList.end(),
                      second.InList.begin(), second.InList.end());
  first.OutList.insert(first.OutList.end(),
                       second.OutList.begin(), second.OutList.end()); 

  first.N = n;

  Stack.push(first);
}

void Parser::concatenate(const Node& n) {
  TempFrag = Stack.top();
  Stack.pop();
  Fragment& first = Stack.top();

  // patch left out to right in
  if (first.Skippable == NOSKIP || first.Skippable < TempFrag.Skippable) {
    patch_pre(first.OutList, TempFrag.InList);
  }
  else {
    patch_post(first.OutList, TempFrag.InList);
  }

  // build new in list
  if (first.Skippable != NOSKIP) {
    first.InList.insert(first.InList.begin() + first.Skippable,
                        TempFrag.InList.begin(), TempFrag.InList.end());
  }

  // build new out list
  if (TempFrag.Skippable != NOSKIP) {
    first.OutList.insert(first.OutList.end(),
                         TempFrag.OutList.begin(), TempFrag.OutList.end()); 
  }
  else {
    first.OutList = TempFrag.OutList;
  }

  // set new skippable
  first.Skippable = first.Skippable == NOSKIP || TempFrag.Skippable == NOSKIP
    ? NOSKIP : first.Skippable + TempFrag.Skippable;

  first.N = n;
}

void Parser::finish(const Node& n) {
  if (2 == Stack.size()) {
    concatenate(n);
    Fragment& start(Stack.top());

    const uint32 numOut = start.OutList.size();
    for (uint32 i = 0; i < numOut; ++i) {
      // std::cout << "marking " << *it << " as a match" << std::endl;
      Graph::vertex v = start.OutList[i].first;
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
    case Node::PLUS:
      plus(n);
      break;
    case Node::STAR:
      star(n);
      break;
    case Node::QUESTION:
      question(n);
      break;
    case Node::PLUS_NG:
      plus_ng(n);
      break;
    case Node::STAR_NG:
      star_ng(n);
      break;
    case Node::QUESTION_NG:
      question_ng(n);
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
