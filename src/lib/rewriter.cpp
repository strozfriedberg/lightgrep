
#include "rewriter.h"

#include <iostream>
#include <stack>

#include <boost/lexical_cast.hpp>

void print_tree(std::ostream& out, const ParseNode& n) {
  if (n.Left) {
    // this node has a left child
    print_tree(out, *n.Left);
  }

  if ((n.Type == ParseNode::CONCATENATION ||
       n.Type == ParseNode::ALTERNATION) && n.Right) {
    // this node has a right child
    print_tree(out, *n.Right);
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

void splice_out_parent(ParseNode* gp, const ParseNode* p, ParseNode* c) {
  if (gp->Left == p) {
    gp->Left = c;
  }
  else if (gp->Right == p) {
    gp->Right = c;
  }
  else {
    throw std::logic_error("wtf");
  }
}

bool has_zero_length_match(const ParseNode *n) {
  switch (n->Type) {
  case ParseNode::REGEXP:
    return !n->Left || has_zero_length_match(n->Left);

  case ParseNode::ALTERNATION:
    return has_zero_length_match(n->Left) || has_zero_length_match(n->Right);

  case ParseNode::CONCATENATION:
    return has_zero_length_match(n->Left) && has_zero_length_match(n->Right);

  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    return n->Rep.Min == 0 || has_zero_length_match(n->Left);

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
    return !n->Left || prefers_zero_length_match(n->Left);

  case ParseNode::ALTERNATION:
    // Left has priority, so we don't need to check right.
    return prefers_zero_length_match(n->Left);

  case ParseNode::CONCATENATION:
    return prefers_zero_length_match(n->Left) &&
           prefers_zero_length_match(n->Right);

  case ParseNode::REPETITION:
    return n->Rep.Max == 0 || prefers_zero_length_match(n->Left);

  case ParseNode::REPETITION_NG:
    return n->Rep.Min == 0 || prefers_zero_length_match(n->Left);

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
    return !n->Left || has_only_zero_length_match(n->Left);

  case ParseNode::ALTERNATION:
    // Left has priority, so we don't need to check right.
    return has_only_zero_length_match(n->Left);

  case ParseNode::CONCATENATION:
    return has_only_zero_length_match(n->Left) &&
           has_only_zero_length_match(n->Right);

  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    return (n->Rep.Min == 0 && n->Rep.Max == 0) ||
           has_only_zero_length_match(n->Left);

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

bool reduce_empty_subtrees(ParseNode* n, std::stack<ParseNode*>& branch) {

  // ST{0}Q = ST{0}?Q = T{0}QS = T{0}?Q = S
  // R(S{0}Q|T) = (S{0}Q|T)R = R
  // (S|T{0}Q) = S?

  bool ret = false;
  branch.push(n);

  if (has_only_zero_length_match(n)) {
    switch (n->Type) {
    case ParseNode::REGEXP:
      // prune the whole tree
      n->Left = 0;
      break;

    case ParseNode::ALTERNATION:
    case ParseNode::CONCATENATION:
    case ParseNode::REPETITION:
    case ParseNode::REPETITION_NG:
      // replace this subtree with a dummy
      n->Type = ParseNode::REPETITION;
      n->Rep.Min = n->Rep.Max = 0;

      // this is safe---we know that n must have a left child if it is
      // not the root and has a zero length match
      n->Left->Type = ParseNode::LITERAL;
      n->Left->Left = n->Left->Right = 0;
      n->Left->Val = 'x';
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
      ret = reduce_empty_subtrees(n->Left, branch);
      break;

    case ParseNode::ALTERNATION:
    case ParseNode::CONCATENATION:
      ret = reduce_empty_subtrees(n->Left, branch);
      ret |= reduce_empty_subtrees(n->Right, branch);
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
    if (has_only_zero_length_match(n->Left)) {
      splice_out_parent(branch.top(), n, n->Right);
    }
    else if (has_only_zero_length_match(n->Right)) {
      splice_out_parent(branch.top(), n, n->Left);
    }
  }
  else if (n->Type == ParseNode::ALTERNATION) {
    if (has_only_zero_length_match(n->Right)) {
      // convert S|T{0} into S?
      n->Type = ParseNode::REPETITION;
      n->Rep.Min = 0;
      n->Rep.Max = 1;
    }
  }

  return ret;
}

bool reduce_empty_subtrees(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return reduce_empty_subtrees(root, branch);
}

bool prune_useless_repetitions(ParseNode* n, const std::stack<ParseNode*>& branch) {
  if ((n->Type == ParseNode::REPETITION ||
       n->Type == ParseNode::REPETITION_NG) &&
      n->Rep.Min == 1 && n->Rep.Max == 1) {
    // remove {1,1}, {1,1}?
    ParseNode* parent = branch.top();
    if (n == parent->Left) {
      parent->Left = n->Left;
    }
    else {
      parent->Right = n->Left;
    }

    // recurse, to handle consecutive repetitions
    prune_useless_repetitions(n->Left, branch);
    return true;
  }
  else if (n->Type == ParseNode::REPETITION_NG &&
           n->Rep.Min == n->Rep.Max) {
    // reduce {n}? to {n}
    n->Type = ParseNode::REPETITION;
    return true;
  }

  return false;
}

bool reduce_useless_repetitions(ParseNode* n, std::stack<ParseNode*>& branch) {
  // T{1} = T{1}? = T
  // T{n}? = T{n}

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Left) {
      return ret;
    }
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    ret = prune_useless_repetitions(n->Left, branch);
    ret |= reduce_useless_repetitions(n->Left, branch);
    break;

  case ParseNode::ALTERNATION:
  case ParseNode::CONCATENATION:
    ret = prune_useless_repetitions(n->Left, branch);
    ret |= reduce_useless_repetitions(n->Left, branch);
    ret |= prune_useless_repetitions(n->Right, branch);
    ret |= reduce_useless_repetitions(n->Right, branch);
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

bool reduce_useless_repetitions(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return reduce_useless_repetitions(root, branch);
}

bool combinable(ParseNode* x, ParseNode* y) {
  return
  (
    (x->Type == ParseNode::REPETITION && y->Type == ParseNode::REPETITION) ||
    (x->Type == ParseNode::REPETITION_NG && y->Type == ParseNode::REPETITION_NG)
  ) && *x == *y;
}

bool combine_consecutive_repetitions(ParseNode* n, std::stack<ParseNode*>& branch) {
  // T{a,b}T{c,d} == T{a+c,b+d}
  // T{a,b}?T{c,d}? == T{a+c,b+d}?

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Left) {
      return ret;
    }
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    ret = combine_consecutive_repetitions(n->Left, branch);
    break;

  case ParseNode::ALTERNATION:
    ret = combine_consecutive_repetitions(n->Left, branch);
    ret |= combine_consecutive_repetitions(n->Right, branch);
    break;

  case ParseNode::CONCATENATION:
    ret = combine_consecutive_repetitions(n->Left, branch);
    ret |= combine_consecutive_repetitions(n->Right, branch);

    if (combinable(n->Left, n->Right)) {
      // the repetitions are siblings
      n->Left->Rep.Min += n->Right->Rep.Min;
      n->Left->Rep.Max =
        (n->Left->Rep.Max == UNBOUNDED || n->Right->Rep.Max == UNBOUNDED)
        ? UNBOUNDED : n->Left->Rep.Max + n->Right->Rep.Max;

      branch.pop();
      splice_out_parent(branch.top(), n, n->Left);
      branch.push(n->Left);
      ret = true;
    }
    else if (n->Left->Type == ParseNode::CONCATENATION &&
             combinable(n->Left->Right, n->Right)) {
      // the second repetition is the right uncle of the first
      n->Right->Rep.Min += n->Left->Right->Rep.Min;
      n->Right->Rep.Max =
        (n->Right->Rep.Max == UNBOUNDED || n->Left->Right->Rep.Max == UNBOUNDED)
        ? UNBOUNDED : n->Right->Rep.Max + n->Left->Right->Rep.Max;
      n->Left = n->Left->Left;
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

bool combine_consecutive_repetitions(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return combine_consecutive_repetitions(root, branch);
}

bool make_binops_right_associative(ParseNode* n, std::stack<ParseNode*>& branch) {
  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Left) {
      return ret;
    }
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    ret = make_binops_right_associative(n->Left, branch);
    break;

  case ParseNode::ALTERNATION:
  case ParseNode::CONCATENATION:
    ret = make_binops_right_associative(n->Left, branch);
    ret |= make_binops_right_associative(n->Right, branch);

    if (n->Left->Type == n->Type) {
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
      ParseNode* c = n->Left;
      ParseNode* f = n->Left->Right;

      (b == a->Left ? a->Left : a->Right) = c;
      c->Right = b;
      b->Left = f;

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

bool make_binops_right_associative(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return make_binops_right_associative(root, branch);
}

bool reduce_trailing_nongreedy_then_greedy(ParseNode* n, std::stack<ParseNode*>& branch) {
  // T{a,b}?T{c,d} == T{a+c,a+d}

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Left) {
      return ret;
    }
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    ret = reduce_trailing_nongreedy_then_greedy(n->Left, branch);
    break;

  case ParseNode::ALTERNATION:
    ret = reduce_trailing_nongreedy_then_greedy(n->Left, branch);
    ret |= reduce_trailing_nongreedy_then_greedy(n->Right, branch);
    break;

  case ParseNode::CONCATENATION:
    ret = reduce_trailing_nongreedy_then_greedy(n->Right, branch);

    if (n->Left->Type == ParseNode::REPETITION_NG) {
      if (n->Right->Type == ParseNode::REPETITION &&
          *n->Left->Left == *n->Right->Left) {
        const uint32 a = n->Left->Rep.Min;
        const uint32 c = n->Right->Rep.Min;
        const uint32 d = n->Right->Rep.Max;

        n->Left->Rep.Min = a + c;
        n->Left->Rep.Max = d == UNBOUNDED ? UNBOUNDED : a + d;
        n->Left->Type = ParseNode::REPETITION;

        branch.pop();
        splice_out_parent(branch.top(), n, n->Left);
        reduce_trailing_nongreedy_then_greedy(n->Left, branch);

        ret = true;
      }
      else if (*n->Left->Left == *n->Right) {
        const uint32 a = n->Left->Rep.Min;
        const uint32 c = 1;
        const uint32 d = 1;

        n->Left->Rep.Min = a + c;
        n->Left->Rep.Max = a + d;
        n->Left->Type = ParseNode::REPETITION;

        branch.pop();
        splice_out_parent(branch.top(), n, n->Left);
        reduce_trailing_nongreedy_then_greedy(n->Left, branch);
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

bool reduce_trailing_nongreedy_then_greedy(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return reduce_trailing_nongreedy_then_greedy(root, branch);
}

bool reduce_trailing_nongreedy_then_empty(ParseNode* n, std::stack<ParseNode*>& branch) {
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
  */

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case ParseNode::REGEXP:
    if (!n->Left) {
      return ret;
    }
  case ParseNode::REPETITION:
    ret = reduce_trailing_nongreedy_then_empty(n->Left, branch);
    break;

  case ParseNode::REPETITION_NG:
    // replace S{n,m}? with S{n}
    n->Type = ParseNode::REPETITION;
    n->Rep.Max = n->Rep.Min;
    reduce_trailing_nongreedy_then_empty(n->Left, branch);
    ret = true;
    break;

  case ParseNode::ALTERNATION:
    ret = reduce_trailing_nongreedy_then_empty(n->Left, branch);
    ret |= reduce_trailing_nongreedy_then_empty(n->Right, branch);
    break;

  case ParseNode::CONCATENATION:
    if (has_zero_length_match(n->Right)) {
      if (n->Left->Type == ParseNode::REPETITION_NG) {
        // the left child is S{n,m}?, the right child is T

        // replace S{n,m}? with S{n}
        n->Left->Type = ParseNode::REPETITION;
        n->Left->Rep.Max = n->Left->Rep.Min;

        ret = true;
      }
      else if (n->Left->Type == ParseNode::CONCATENATION &&
               n->Left->Right->Type == ParseNode::REPETITION_NG) {
        // the right grandchild is S{n,m}?, the right child is T

        // replace S{n,m}? with S{n}
        n->Left->Right->Type = ParseNode::REPETITION;
        n->Left->Right->Rep.Max = n->Left->Right->Rep.Min;

        ret = true;

        // check the left left, if trailed by an empty-matching subpattern
        if (has_zero_length_match(n->Left->Right)) {
          reduce_trailing_nongreedy_then_empty(n->Left->Left, branch);
        }
      }
      else {
        // check the left, it is trailed by an empty-matching subpattern
        ret = reduce_trailing_nongreedy_then_empty(n->Left, branch);
      }
    }

    ret |= reduce_trailing_nongreedy_then_empty(n->Right, branch);
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

bool reduce_trailing_nongreedy_then_empty(ParseNode* root) {
  std::stack<ParseNode*> branch;
  return reduce_trailing_nongreedy_then_empty(root, branch);
}
