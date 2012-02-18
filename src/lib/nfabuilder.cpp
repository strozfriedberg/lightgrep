#include "nfabuilder.h"

#include "concrete_encodings.h"
#include "states.h"
#include "transitionfactory.h"
#include "utility.h"

#include <iostream>
#include <utility>

#include <boost/shared_ptr.hpp>

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
  out << "in " << f.InList << ", out " << f.OutList
      << ", skip " << f.Skippable;
  return out;
}

NFABuilder::NFABuilder():
  CaseInsensitive(false),
  CurLabel(0),
  ReserveSize(0),
  Fsm(new NFA(1)),
  TransFac(new TransitionFactory())
{
  setEncoding(boost::shared_ptr<Encoding>(new Ascii));
  init();
}

void NFABuilder::reset() {
  if (Fsm) {
    Fsm->clear();
    Fsm->addVertex();
  }
  else {
    Fsm.reset(new NFA(1));
//    Fsm.reset(new NFA(1, ReserveSize));
  }

  while (!Stack.empty()) {
    Stack.pop();
  }

  init();
}

void NFABuilder::init() {
  IsGood = false;
  TempFrag.initFull(0, ParseNode());
  Stack.push(TempFrag);
  Fsm->TransFac = TransFac;
}

void NFABuilder::setEncoding(const boost::shared_ptr<Encoding>& e) {
  Enc = e;
  TempBuf.reset(new byte[Enc->maxByteLength()]);
}

void NFABuilder::setCaseInsensitive(bool insensitive) {
  CaseInsensitive = insensitive;
}

void NFABuilder::setSizeHint(uint64 reserveSize) {
  ReserveSize = reserveSize;
}

void NFABuilder::setLiteralTransition(NFA& g, const NFA::VertexDescriptor& v, byte val) {
  if (!CaseInsensitive || !std::isalpha(val)) {
    g[v].Trans = g.TransFac->getLit(val);
  }
  else {
    g[v].Trans = g.TransFac->getEither(std::toupper(val), std::tolower(val));
    g.Deterministic = false;
  }
}

void NFABuilder::patch_mid(OutListT& src, const InListT& dst, uint32 dstskip) {
  // Make an edge from each vertex in src to each vertex in dst. Edges
  // to vertices in dst before dstskip go before the insertion point in
  // src, edges to vertices in dst after dstskip go after the insertion
  // point in src.
  const InListT::const_iterator skip_stop(dst.begin() + dstskip);

  for (OutListT::iterator oi(src.begin()); oi != src.end(); ++oi) {
    uint32 pos = oi->second;

    InListT::const_iterator ii(dst.begin());

    // make edges before dstskip, inserting before src insertion point
    for ( ; ii != dst.end() && ii < skip_stop; ++ii) {
      Fsm->insertEdge(oi->first, *ii, pos++);
    }

    // save the new insertion point for dst
    const uint32 spos = pos;

    // make edges after dstskip, inserting after src insertion point
    for ( ; ii != dst.end(); ++ii) {
      Fsm->insertEdge(oi->first, *ii, pos++);
    }

    // set the new insertion point for dst
    oi->second = spos;
  }
}

void NFABuilder::patch_pre(OutListT& src, const InListT& dst) {
  // Put all new edges before dst's insertion point.
  patch_mid(src, dst, dst.size());
}

void NFABuilder::patch_post(OutListT& src, const InListT& dst) {
  // Put all new edges after dst's insertion point.
  patch_mid(src, dst, 0);
}

void NFABuilder::literal(const ParseNode& n) {
  const uint32 len = Enc->write(n.Val, TempBuf.get());
  if (0 == len) {
    // FXIME: should we really be checking this if it's supposed to be
    // an impossible condition?
    throw std::logic_error("bad things");
  }
  else {
    NFA& g(*Fsm);
    NFA::VertexDescriptor first, prev, last;
    first = prev = last = g.addVertex();
    setLiteralTransition(g, first, TempBuf[0]);
    for (uint32 i = 1; i < len; ++i) {
      last = g.addVertex();
      g.addEdge(prev, last);
      setLiteralTransition(g, last, TempBuf[i]);
      prev = last;
    }
    TempFrag.reset(n);
    TempFrag.InList.push_back(first);
    TempFrag.OutList.push_back(std::make_pair(last, 0));
    Stack.push(TempFrag);
  }
}

void NFABuilder::dot(const ParseNode& n) {
  NFA::VertexDescriptor v = Fsm->addVertex();
  (*Fsm)[v].Trans = Fsm->TransFac->getRange(0, 255);
  Fsm->Deterministic = false;
  TempFrag.initFull(v, n);
  Stack.push(TempFrag);
}

void NFABuilder::charClass(const ParseNode& n) {
  NFA::VertexDescriptor v = Fsm->addVertex();
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
    (*Fsm)[v].Trans = Fsm->TransFac->getRange(first, last);
  }
  else {
    (*Fsm)[v].Trans = Fsm->TransFac->getCharClass(n.Bits);
  }

  Fsm->Deterministic = false;

  TempFrag.initFull(v, n);
  Stack.push(TempFrag);
}

void NFABuilder::question(const ParseNode&) {
  Fragment& optional = Stack.top();
  if (optional.Skippable > optional.InList.size()) {
    optional.Skippable = optional.InList.size();
  }
}

void NFABuilder::question_ng(const ParseNode&) {
  Fragment& optional = Stack.top();
  optional.Skippable = 0;
}

void NFABuilder::plus(const ParseNode& n) {
  Fragment& repeat = Stack.top();
  repeat.N = n;

  // make back edges
  patch_pre(repeat.OutList, repeat.InList);
}

void NFABuilder::plus_ng(const ParseNode& n) {
  Fragment& repeat = Stack.top();
  repeat.N = n;

  // make back edges
  patch_post(repeat.OutList, repeat.InList);
}

void NFABuilder::star(const ParseNode& n) {
  plus(n);
  question(n);
}

void NFABuilder::star_ng(const ParseNode& n) {
  plus_ng(n);
  question_ng(n);
}

void NFABuilder::repetition(const ParseNode& n) {
  if (n.Min == 0) {
    if (n.Max == 1) {
      question(n);
      return;
    }
    else if (n.Max == UNBOUNDED) {
      star(n);
      return;
    }
  }
  else if (n.Min == 1 && n.Max == UNBOUNDED) {
    plus(n);
    return;
  }

  // all other cases are already reduced by traverse
}

void NFABuilder::repetition_ng(const ParseNode& n) {
  if (n.Min == 0) {
    if (n.Max == 1) {
      question_ng(n);
      return;
    }
    else if (n.Max == UNBOUNDED) {
      star_ng(n);
      return;
    }
  }
  else if (n.Min == 1 && n.Max == UNBOUNDED) {
    plus_ng(n);
    return;
  }

  // all other cases are already reduced by traverse
}

void NFABuilder::alternate(const ParseNode& n) {
  Fragment second;
  second.assign(Stack.top());
  Stack.pop();

  Fragment& first(Stack.top());

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
}

void NFABuilder::concatenate(const ParseNode& n) {
  TempFrag.assign(Stack.top());
  Stack.pop();
  Fragment& first(Stack.top());

  // patch left out to right in
  patch_mid(first.OutList, TempFrag.InList, TempFrag.Skippable);

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
    first.OutList.swap(TempFrag.OutList);
  }

  // set new skippable
  first.Skippable = first.Skippable == NOSKIP || TempFrag.Skippable == NOSKIP
    ? NOSKIP : first.Skippable + TempFrag.Skippable;

  first.N = n;
}

void NFABuilder::finish(const ParseNode& n) {
  if (2 == Stack.size()) {
    concatenate(n);
    Fragment& start(Stack.top());

    for (OutListT::const_iterator i(start.OutList.begin()); i != start.OutList.end(); ++i) {
      // std::cout << "marking " << *it << " as a match" << std::endl;
      NFA::VertexDescriptor v = i->first;
      if (0 == v) { // State 0 is not allowed to be a match state; i.e. 0-length REs are not allowed
        reset();
        return;
      }
      else {
        NFA::Vertex& final((*Fsm)[v]);
        final.Label = CurLabel;
        final.IsMatch = true;
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

void NFABuilder::traverse(const ParseNode* root) {
  // holder for synthesized nodes
  std::vector<boost::shared_ptr<ParseNode>> synth;

  // wind for preorder traversal, unwind for postorder
  std::stack<const ParseNode*> wind, unwind;
  wind.push(root);

  while (!wind.empty()) {
    const ParseNode* n = wind.top();
    wind.pop();
    unwind.push(n);

    if (n->Left) {
      // This node has a left child
      if ((n->Type == ParseNode::REPETITION ||
           n->Type == ParseNode::REPETITION_NG) &&
         !((n->Min == 0 && (n->Max == 1 || n->Max == UNBOUNDED)) ||
           (n->Min == 1 && n->Max == UNBOUNDED)))
      {
        // This is a repetition, but not one of the special named ones.
        // We synthesize nodes here to eliminate counted repetitions.

        // NB: We expect that all empty ({0,0} and {0,0}?) and single
        // ({1,1}, {1,1}?) have been excised from the parse tree by now.

        //
        // T{n} = T...T
        //          ^
        //        n times
        //
        // T{n,} = T...TT*
        //           ^
        //         n times
        //
        // T{n,m} = T...TT?...T? = T...T(T(T...)?)?
        //            ^     ^
        //       n times   m-n times
        //
        // Note that the latter equivalence for T{n,m} produces
        // a graph with outdegree 2, while the former produces
        // one with outdegree m-n.
        //

        ParseNode root;
        ParseNode* none = 0;
        ParseNode* parent = &root;

        if (n->Min > 0) {
          // build the mandatory part
          for (uint32 i = 1; i < n->Min; ++i) {
            synth.push_back(boost::shared_ptr<ParseNode>(
              new ParseNode(ParseNode::CONCATENATION, n->Left, none))
            );
            ParseNode* con = synth.back().get();

            parent->Right = con;
            parent = con;
          }
        }

        if (n->Min == n->Max) {
          // finish the mandatory part
          parent->Right = n->Left;
        }
        else if (n->Max == UNBOUNDED) {
          // build the unbounded optional part
          if (n->Min == 0) {
            synth.push_back(boost::shared_ptr<ParseNode>(
              new ParseNode(n->Type, n->Left, 0, UNBOUNDED))
            );
            ParseNode* star = synth.back().get();
            parent->Right = star;
          }
          else {
            synth.push_back(boost::shared_ptr<ParseNode>(
              new ParseNode(n->Type, n->Left, 1, UNBOUNDED))
            );
            ParseNode* plus = synth.back().get();
            parent->Right = plus;
          }
        }
        else {
          if (n->Min > 0) {
            // finish the mandatory part
            synth.push_back(boost::shared_ptr<ParseNode>(
              new ParseNode(ParseNode::CONCATENATION, n->Left, none))
            );
            ParseNode* con = synth.back().get();
            parent->Right = con;
            parent = con;
          }

          // build the bounded optional part
          for (uint32 i = 1; i < n->Max - n->Min; ++i) {
            synth.push_back(boost::shared_ptr<ParseNode>(
              new ParseNode(ParseNode::CONCATENATION, n->Left, none))
            );
            ParseNode* con = synth.back().get();
            
            synth.push_back(boost::shared_ptr<ParseNode>(
              new ParseNode(n->Type, con, 0, 1))
            );
            ParseNode* question = synth.back().get();
            
            parent->Right = question;
            parent = con;
          }

          synth.push_back(boost::shared_ptr<ParseNode>(
            new ParseNode(n->Type, n->Left, 0, 1))
          );
          ParseNode* question = synth.back().get(); 
          parent->Right = question;
        }

        wind.push(root.Right);
      }
      else {
        // this is not a repetition, or is one of ? * + ?? *? +?
        wind.push(n->Left);
      }
    }

    if (n->Right) {
      wind.push(n->Right);
    }
  }

  while (!unwind.empty()) {
    const ParseNode* n = unwind.top();
    unwind.pop();

    callback(*n);
  }
}

bool NFABuilder::build(const ParseTree& tree) {
  traverse(tree.Root);
  return IsGood;
}

void NFABuilder::callback(const ParseNode& n) {
//  std::cerr << n << std::endl;
  switch (n.Type) {
    case ParseNode::REGEXP:
      finish(n);
      break;
    case ParseNode::ALTERNATION:
      alternate(n);
      break;
    case ParseNode::CONCATENATION:
      concatenate(n);
      break;
    case ParseNode::REPETITION:
      repetition(n);
      break;
    case ParseNode::REPETITION_NG:
      repetition_ng(n);
      break;
    case ParseNode::DOT:
      dot(n);
      break;
    case ParseNode::CHAR_CLASS:
      charClass(n);
      break;
    case ParseNode::LITERAL:
      literal(n);
      break;
    default:
      break;
  }

/*
  std::cerr << "Stack size is " << Stack.size() << std::endl;
  if (Stack.size() > 0) {
     std::cerr << "top is " << Stack.top() << std::endl;
  }
*/
}
