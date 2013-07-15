/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rewriter.h"

#include <iostream>
#include <stack>

#include <boost/lexical_cast.hpp>

void print_tree(std::ostream& out, const ParseNode& n) {
  switch (n.Type) {
  case ParseNode::REGEXP:
  case ParseNode::ALTERNATION:
  case ParseNode::CONCATENATION:
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    if (n.Child.Left) {
      // this node has a left child
      printTree(out, *n.Child.Left);
    }
    break;
  }

  if ((n.Type == ParseNode::CONCATENATION ||
       n.Type == ParseNode::ALTERNATION) && n.Child.Right) {
    // this node has a right child
    print_tree(out, *n.Child.Right);
  }

  out << n << '\n';
}

void print_branch(std::ostream& out, std::stack<ParseNode*>& branch) {
  std::stack<ParseNode*> tmp;

  while (!branch.empty()) {
    tmp.push(branch.top());
    branch.pop();
  }

  ParseNode* n;
  while (!tmp.empty()) {
    n = tmp.top();
    out << *n << '\n';
    branch.push(n);
    tmp.pop();
  }
}

void spliceOutParent(ParseNode* gp, const ParseNode* p, ParseNode* c) {
  if (gp->Child.Left == p) {
    gp->Child.Left = c;
  }
  else if (gp->Child.Right == p) {
    gp->Child.Right = c;
  }
  else {
    throw std::logic_error("wtf");
  }
}

bool hasZeroLengthMatch(const ParseNode *n) {
  switch (n->Type) {
  case ParseNode::REGEXP:
    return !n->Child.Left || hasZeroLengthMatch(n->Child.Left);

  case ParseNode::ALTERNATION:
    return hasZeroLengthMatch(n->Child.Left) || hasZeroLengthMatch(n->Child.Right);

  case ParseNode::CONCATENATION:
    return hasZeroLengthMatch(n->Child.Left) && hasZeroLengthMatch(n->Child.Right);

  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    return n->Child.Rep.Min == 0 || hasZeroLengthMatch(n->Child.Left);

  case ParseNode::DOT:
  case ParseNode::CHAR_CLASS:
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    return false;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}

bool prefers_zero_length_match(const ParseNode* n) {
  switch (n->Type) {
  case ParseNode::REGEXP:
    return !n->Child.Left || prefers_zero_length_match(n->Child.Left);

  case ParseNode::ALTERNATION:
    // Left has priority, so we don't need to check right.
    return prefers_zero_length_match(n->Child.Left);

  case ParseNode::CONCATENATION:
    return prefers_zero_length_match(n->Child.Left) &&
           prefers_zero_length_match(n->Child.Right);

  case ParseNode::REPETITION:
    return n->Child.Rep.Max == 0 || prefers_zero_length_match(n->Child.Left);

  case ParseNode::REPETITION_NG:
    return n->Child.Rep.Min == 0 || prefers_zero_length_match(n->Child.Left);

  case ParseNode::DOT:
  case ParseNode::CHAR_CLASS:
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    return false;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}

bool has_only_zero_length_match(const ParseNode* n) {
  switch (n->Type) {
  case ParseNode::REGEXP:
    return !n->Child.Left || has_only_zero_length_match(n->Child.Left);

  case ParseNode::ALTERNATION:
    // Left has priority, so we don't need to check right.
    return has_only_zero_length_match(n->Child.Left);

  case ParseNode::CONCATENATION:
    return has_only_zero_length_match(n->Child.Left) &&
           has_only_zero_length_match(n->Child.Right);

  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    return (n->Child.Rep.Min == 0 && n->Child.Rep.Max == 0) ||
           has_only_zero_length_match(n->Child.Left);

  case ParseNode::DOT:
  case ParseNode::CHAR_CLASS:
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    return false;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}

bool reduceEmptySubtrees(ParseNode* n, std::stack<ParseNode*>& branch) {

  // ST{0}Q = ST{0}?Q = T{0}QS = T{0}?Q = S
  // R(S{0}Q|T) = (S{0}Q|T)R = R
  // (S|T{0}Q) = S?

  bool ret = false;
  branch.push(n);

  if (has_only_zero_length_match(n)) {
    switch (n->Type) {
    case ParseNode::REGEXP:
      // prune the whole tree
      n->Child.Left = 0;
      break;

    case ParseNode::ALTERNATION:
    case ParseNode::CONCATENATION:
    case ParseNode::REPETITION:
    case ParseNode::REPETITION_NG:
      // replace this subtree with a dummy
      n->Type = ParseNode::REPETITION;
      n->Child.Rep.Min = n->Child.Rep.Max = 0;

      // this is safe---we know that n must have a left child if it is
      // not the root and has a zero length match
      n->Child.Left->Type = ParseNode::LITERAL;
      n->Child.Left->Child.Left = n->Child.Left->Child.Right = 0;
      n->Child.Left->Val = 'x';
      break;

    default:
      // WTF?
      throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
    }
    ret = true;
  }
  else {
    switch (n->Type) {
    case ParseNode::REGEXP:
    case ParseNode::REPETITION:
    case ParseNode::REPETITION_NG:
      ret = reduceEmptySubtrees(n->Child.Left, branch);
      break;

    case ParseNode::ALTERNATION:
    case ParseNode::CONCATENATION:
      ret = reduceEmptySubtrees(n->Child.Left, branch);
      ret |= reduceEmptySubtrees(n->Child.Right, branch);
      break;

    case ParseNode::DOT:
    case ParseNode::CHAR_CLASS:
    case ParseNode::LITERAL:
    case ParseNode::BYTE:
      // branch finished
      ret = false;
      break;

    default:
      // WTF?
      throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
    }
  }

  branch.pop();

  // fix concatenations and alternations with dead children on the way up
  if (n->Type == ParseNode::CONCATENATION) {
    // convert ST{0} and T{0}S into S
    if (has_only_zero_length_match(n->Child.Left)) {
      spliceOutParent(branch.top(), n, n->Child.Right);
    }
    else if (has_only_zero_length_match(n->Child.Right)) {
      spliceOutParent(branch.top(), n, n->Child.Left);
    }
  }
  else if (n->Type == ParseNode::ALTERNATION) {
    if (has_only_zero_length_match(n->Child.Right)) {
      // convert S|T{0} into S?
      n->Type = ParseNode::REPETITION;
      n->Child.Rep.Min = 0;
      n->Child.Rep.Max = 1;
    }
  }

  return ret;
}

bool reduceEmptySubtrees(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return reduceEmptySubtrees(root, branch);
}

bool prune_useless_repetitions(ParseNode* n, const std::stack<ParseNode*>& branch) {
  if ((n->Type == ParseNode::REPETITION ||
       n->Type == ParseNode::REPETITION_NG) &&
      n->Child.Rep.Min == 1 && n->Child.Rep.Max == 1) {
    // remove {1,1}, {1,1}?
    ParseNode* parent = branch.top();
    if (n == parent->Child.Left) {
      parent->Child.Left = n->Child.Left;
    }
    else {
      parent->Child.Right = n->Child.Left;
    }

    // recurse, to handle consecutive repetitions
    prune_useless_repetitions(n->Child.Left, branch);
    return true;
  }
  else if (n->Type == ParseNode::REPETITION_NG &&
           n->Child.Rep.Min == n->Child.Rep.Max) {
    // reduce {n}? to {n}
    n->Type = ParseNode::REPETITION;
    return true;
  }

  return false;
}

bool reduceUselessRepetitions(ParseNode* n, std::stack<ParseNode*>& branch) {
  // T{1} = T{1}? = T
  // T{n}? = T{n}

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Child.Left) {
      return ret;
    }
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    ret = prune_useless_repetitions(n->Child.Left, branch);
    ret |= reduceUselessRepetitions(n->Child.Left, branch);
    break;

  case ParseNode::ALTERNATION:
  case ParseNode::CONCATENATION:
    ret = prune_useless_repetitions(n->Child.Left, branch);
    ret |= reduceUselessRepetitions(n->Child.Left, branch);
    ret |= prune_useless_repetitions(n->Child.Right, branch);
    ret |= reduceUselessRepetitions(n->Child.Right, branch);
    break;

  case ParseNode::DOT:
  case ParseNode::CHAR_CLASS:
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    // branch finished
    ret = false;
    break;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }

  branch.pop();
  return ret;
}

bool reduceUselessRepetitions(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return reduceUselessRepetitions(root, branch);
}

bool combinable(ParseNode* x, ParseNode* y) {
  return
  (
    (x->Type == ParseNode::REPETITION && y->Type == ParseNode::REPETITION) ||
    (x->Type == ParseNode::REPETITION_NG && y->Type == ParseNode::REPETITION_NG)
  ) && *x == *y;
}

bool combineConsecutiveRepetitions(ParseNode* n, std::stack<ParseNode*>& branch) {
  // T{a,b}T{c,d} == T{a+c,b+d}
  // T{a,b}?T{c,d}? == T{a+c,b+d}?

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Child.Left) {
      return ret;
    }
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    ret = combineConsecutiveRepetitions(n->Child.Left, branch);
    break;

  case ParseNode::ALTERNATION:
    ret = combineConsecutiveRepetitions(n->Child.Left, branch);
    ret |= combineConsecutiveRepetitions(n->Child.Right, branch);
    break;

  case ParseNode::CONCATENATION:
    ret = combineConsecutiveRepetitions(n->Child.Left, branch);
    ret |= combineConsecutiveRepetitions(n->Child.Right, branch);

    if (combinable(n->Child.Left, n->Child.Right)) {
      // the repetitions are siblings
      n->Child.Left->Child.Rep.Min += n->Child.Right->Child.Rep.Min;
      n->Child.Left->Child.Rep.Max =
        (n->Child.Left->Child.Rep.Max == UNBOUNDED || n->Child.Right->Child.Rep.Max == UNBOUNDED)
        ? UNBOUNDED : n->Child.Left->Child.Rep.Max + n->Child.Right->Child.Rep.Max;

      branch.pop();
      spliceOutParent(branch.top(), n, n->Child.Left);
      branch.push(n->Child.Left);
      ret = true;
    }
    else if (n->Child.Right->Type == ParseNode::CONCATENATION &&
             combinable(n->Child.Left, n->Child.Right->Child.Left)) {
      // the second repetition is the left nephew of the first
      n->Child.Left->Child.Rep.Min += n->Child.Right->Child.Left->Child.Rep.Min;
      n->Child.Left->Child.Rep.Max =
        (n->Child.Left->Child.Rep.Max == UNBOUNDED || n->Child.Right->Child.Left->Child.Rep.Max == UNBOUNDED)
        ? UNBOUNDED : n->Child.Left->Child.Rep.Max + n->Child.Right->Child.Left->Child.Rep.Max;
      n->Child.Right = n->Child.Right->Child.Right;
      ret = true;
    }
    break;

  case ParseNode::DOT:
  case ParseNode::CHAR_CLASS:
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    // branch finished
    ret = false;
    break;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }

  branch.pop();
  return ret;
}

bool combineConsecutiveRepetitions(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return combineConsecutiveRepetitions(root, branch);
}

bool makeBinopsRightAssociative(ParseNode* n, std::stack<ParseNode*>& branch) {
  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Child.Left) {
      return ret;
    }
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    ret = makeBinopsRightAssociative(n->Child.Left, branch);
    break;

  case ParseNode::ALTERNATION:
  case ParseNode::CONCATENATION:
    ret = makeBinopsRightAssociative(n->Child.Left, branch);
    ret |= makeBinopsRightAssociative(n->Child.Right, branch);

    if (n->Child.Left->Type == n->Type) {
      /*
        Adjust consecutive binary nodes so that consecutive same-type
        binary ops are the right children of their parents.

                  a            a
                  |            |
                  b     =>     c
                 / \          / \
                c   d        e   b
               / \              / \
              e   f            f   d

      */

      branch.pop();
      ParseNode* a = branch.top();
      ParseNode* b = n;
      ParseNode* c = n->Child.Left;
      ParseNode* f = n->Child.Left->Child.Right;

      (b == a->Child.Left ? a->Child.Left : a->Child.Right) = c;
      c->Child.Right = b;
      b->Child.Left = f;

      branch.push(c);
      ret = true;
    }
    break;

  case ParseNode::DOT:
  case ParseNode::CHAR_CLASS:
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    // branch finished
    ret = false;
    break;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }

  branch.pop();
  return ret;
}

bool makeBinopsRightAssociative(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return makeBinopsRightAssociative(root, branch);
}

bool reduceTrailingNongreedyThenGreedy(ParseNode* n, std::stack<ParseNode*>& branch) {
  // T{a,b}?T{c,d} == T{a+c,a+d}

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Child.Left) {
      return ret;
    }
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    ret = reduceTrailingNongreedyThenGreedy(n->Child.Left, branch);
    break;

  case ParseNode::ALTERNATION:
    ret = reduceTrailingNongreedyThenGreedy(n->Child.Left, branch);
    ret |= reduceTrailingNongreedyThenGreedy(n->Child.Right, branch);
    break;

  case ParseNode::CONCATENATION:
    ret = reduceTrailingNongreedyThenGreedy(n->Child.Right, branch);

    if (n->Child.Left->Type == ParseNode::REPETITION_NG) {
      if (n->Child.Right->Type == ParseNode::REPETITION &&
          *n->Child.Left->Child.Left == *n->Child.Right->Child.Left) {
        const uint32_t a = n->Child.Left->Child.Rep.Min;
        const uint32_t c = n->Child.Right->Child.Rep.Min;
        const uint32_t d = n->Child.Right->Child.Rep.Max;

        n->Child.Left->Child.Rep.Min = a + c;
        n->Child.Left->Child.Rep.Max = d == UNBOUNDED ? UNBOUNDED : a + d;
        n->Child.Left->Type = ParseNode::REPETITION;

        branch.pop();
        spliceOutParent(branch.top(), n, n->Child.Left);
        reduceTrailingNongreedyThenGreedy(n->Child.Left, branch);
        branch.push(n->Child.Left);

        ret = true;
      }
      else if (*n->Child.Left->Child.Left == *n->Child.Right) {
        const uint32_t a = n->Child.Left->Child.Rep.Min;
        const uint32_t c = 1;
        const uint32_t d = 1;

        n->Child.Left->Child.Rep.Min = a + c;
        n->Child.Left->Child.Rep.Max = a + d;
        n->Child.Left->Type = ParseNode::REPETITION;

        branch.pop();
        spliceOutParent(branch.top(), n, n->Child.Left);
        reduceTrailingNongreedyThenGreedy(n->Child.Left, branch);
        branch.push(n->Child.Left);
        ret = true;
      }
    }
    break;

  case ParseNode::DOT:
  case ParseNode::CHAR_CLASS:
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    // branch finished
    ret = false;
    break;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }

  branch.pop();
  return ret;
}

bool reduceTrailingNongreedyThenGreedy(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return reduceTrailingNongreedyThenGreedy(root, branch);
}

bool reduceTrailingNongreedyThenEmpty(ParseNode* n, std::stack<ParseNode*>& branch) {
  /*
     As a suffix, S{n,m}?T = S{n}T, when T admits zero-length matches.

     In the tree, the adjacency can show up as either S{n,m}? and T as
     children of the same concatenation, or as T being the right uncle
     of S{n,m}?:

         &            &
        / \    OR    / \
       +?  T        &   T
        |          / \
        S            +?
                      |
                      S

     As a suffix, S{n,m}? = S{n}. This is a special case of the above,
     letting T = R{0}.

     However, the second tree is impossible if we first rewrite trees
     to be right-associative for contatenation.
  */

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Child.Left) {
      return ret;
    }
  case ParseNode::REPETITION:
    ret = reduceTrailingNongreedyThenEmpty(n->Child.Left, branch);
    break;

  case ParseNode::REPETITION_NG:
    // replace S{n,m}? with S{n}
    n->Type = ParseNode::REPETITION;
    n->Child.Rep.Max = n->Child.Rep.Min;
    reduceTrailingNongreedyThenEmpty(n->Child.Left, branch);
    ret = true;
    break;

  case ParseNode::ALTERNATION:
    ret = reduceTrailingNongreedyThenEmpty(n->Child.Left, branch);
    ret |= reduceTrailingNongreedyThenEmpty(n->Child.Right, branch);
    break;

  case ParseNode::CONCATENATION:
    if (hasZeroLengthMatch(n->Child.Right)) {
      if (n->Child.Left->Type == ParseNode::REPETITION_NG) {
        // the left child is S{n,m}?, the right child is T

        // replace S{n,m}? with S{n}
        n->Child.Left->Type = ParseNode::REPETITION;
        n->Child.Left->Child.Rep.Max = n->Child.Left->Child.Rep.Min;

        ret = true;
      }
      else {
        // check the left, it is trailed by an empty-matching subpattern
        ret = reduceTrailingNongreedyThenEmpty(n->Child.Left, branch);
      }
    }

    ret |= reduceTrailingNongreedyThenEmpty(n->Child.Right, branch);
    break;

  case ParseNode::DOT:
  case ParseNode::CHAR_CLASS:
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    // branch finished
    ret = false;
    break;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }

  branch.pop();
  return ret;
}

bool reduceTrailingNongreedyThenEmpty(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return reduceTrailingNongreedyThenEmpty(root, branch);
}
