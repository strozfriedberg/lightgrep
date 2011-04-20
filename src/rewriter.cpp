
#include "rewriter.h"

#include <iostream>
#include <stack>

#include <boost/lexical_cast.hpp>

void print_tree(std::ostream& out, const Node& n) {
  if (n.Left) {
    // this node has a left child
    print_tree(out, *n.Left);
  }

  if (n.Right) {
    // this node has a right child
    print_tree(out, *n.Right);
  }

  out << n << '\n';
}

void print_branch(std::ostream& out, std::stack<Node*>& branch) {
  std::stack<Node*> tmp;

  while (!branch.empty()) {
    tmp.push(branch.top());
    branch.pop();
  }

  Node* n;
  while (!tmp.empty()) {
    n = tmp.top();
    out << *n << '\n';
    branch.push(n);
    tmp.pop();
  }
}

bool has_zero_length_match(const Node *n) {
  switch (n->Type) {
  case Node::REGEXP:
    return has_zero_length_match(n->Left);

  case Node::ALTERNATION:
    return has_zero_length_match(n->Left) || has_zero_length_match(n->Right);

  case Node::CONCATENATION:
    return has_zero_length_match(n->Left) && has_zero_length_match(n->Right);

  case Node::REPETITION:
  case Node::REPETITION_NG:
    return n->Min == 0 || has_zero_length_match(n->Left);

  case Node::DOT:
  case Node::CHAR_CLASS:
  case Node::LITERAL:
    return false;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}

bool prefers_zero_length_match(const Node* n) {
  switch (n->Type) {
  case Node::REGEXP:
    return prefers_zero_length_match(n->Left);

  case Node::ALTERNATION:
    // Left has priority, so we don't need to check right.
    return prefers_zero_length_match(n->Left);

  case Node::CONCATENATION:
    return prefers_zero_length_match(n->Left) &&
           prefers_zero_length_match(n->Right);

  case Node::REPETITION:
    return n->Max == 0 || prefers_zero_length_match(n->Left);

  case Node::REPETITION_NG:
    return n->Min == 0 || prefers_zero_length_match(n->Left);

  case Node::DOT:
  case Node::CHAR_CLASS:
  case Node::LITERAL:
    return false;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}

bool has_only_zero_length_match(const Node* n) {
  switch (n->Type) {
  case Node::REGEXP:
    return has_only_zero_length_match(n->Left);

  case Node::ALTERNATION:
    // Left has priority, so we don't need to check right.
    return has_only_zero_length_match(n->Left);

  case Node::CONCATENATION:
    return has_only_zero_length_match(n->Left) &&
           has_only_zero_length_match(n->Right);

  case Node::REPETITION:
  case Node::REPETITION_NG:
    return (n->Min == 0 && n->Max == 0) || has_only_zero_length_match(n->Left);

  case Node::DOT:
  case Node::CHAR_CLASS:
  case Node::LITERAL:
    return false;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}

bool reduce_empty_subtrees(Node* n, std::stack<Node*>& branch) {
  
  // ST{0}Q = ST{0}?Q = T{0}QS = T{0}?Q = S
  // R(S{0}Q|T) = (S{0}Q|T)R = R
  // (R|S{0}Q|T) = R?
 
  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case Node::REGEXP:
    if (!n->Left) {
      return ret;
    }
    
    if (has_only_zero_length_match(n->Left)) {
      // prune away the whole tree 
      n->Left = 0;
      ret = true;
    }
    else {
      ret = reduce_empty_subtrees(n->Left, branch);
    }
    branch.pop();
    break;

  case Node::ALTERNATION:
    // We don't check the left alternative for zero-length matches only
    // here because if it did, then the whole alternation would, so we
    // would already have pruned it away.

    if (has_only_zero_length_match(n->Right)) {
      Node* l = n->Left;
      Node* old = n->Right;

      // prune away right alternative
      prune_subtree(n->Right, branch);
      n = branch.top();
      branch.pop();

      // insert a ? as the parent of the left alternative,
      // reusing a pruned node
      old->Type = Node::REPETITION;
      old->Min = 0;
      old->Max = 1;
      old->Left = l;

      if (l == n->Left) {
        n->Left = old;
      }
      else {
        n->Right = old;
      }

      reduce_empty_subtrees(old, branch);
      ret = true;
    }
    else {
      ret = reduce_empty_subtrees(n->Left, branch);
      ret |= reduce_empty_subtrees(n->Right, branch);
      branch.pop();
    }
    break;

  case Node::CONCATENATION:
    if (has_only_zero_length_match(n->Left)) {
      // prune away left conjunct
      prune_subtree(n->Left, branch);
      n = branch.top();
      branch.pop();
      reduce_empty_subtrees(n, branch);
      ret = true;
    }
    else if (has_only_zero_length_match(n->Right)) {
      // prune away right conjunct
      prune_subtree(n->Right, branch);
      n = branch.top();
      branch.pop(); 
      reduce_empty_subtrees(n, branch);
      ret = true;
    }
    else {
      ret = reduce_empty_subtrees(n->Left, branch);
      ret |= reduce_empty_subtrees(n->Right, branch);
      branch.pop();
    }
    break;

  case Node::REPETITION:
  case Node::REPETITION_NG:
  case Node::DOT:
  case Node::CHAR_CLASS:
  case Node::LITERAL:
    // branch finished
    ret = false;
    branch.pop();
    break;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }

  return ret;
}

bool reduce_empty_subtrees(Node* root) {
  std::stack<Node*> branch;
  return reduce_empty_subtrees(root, branch);
}

bool prune_useless_repetitions(Node* n, const std::stack<Node*>& branch) {
  if ((n->Type == Node::REPETITION || n->Type == Node::REPETITION_NG) &&
       n->Min == 1 && n->Max == 1) {
    // remove {1,1}, {1,1}?
    Node* parent = branch.top();
    if (n == parent->Left) {
      parent->Left = n->Left;
    }
    else {
      parent->Right = n->Left;
    }

    // recurse, to handle nested repetitions
    prune_useless_repetitions(n->Left, branch);
    return true;
  }
  else if (n->Type == Node::REPETITION_NG && n->Min == n->Max) {
    // reduce {n}? to {n}
    n->Type = Node::REPETITION;
    return true;
  }

  return false;
}

bool reduce_useless_repetitions(Node* n, std::stack<Node*>& branch) {
  // T{1} = T{1}? = T
  // T{n}? = T{n}
 
  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case Node::REGEXP:
    if (!n->Left) {
      return ret;
    }
    ret = prune_useless_repetitions(n->Left, branch);
    ret |= reduce_useless_repetitions(n->Left, branch);
    break;

  case Node::ALTERNATION:
  case Node::CONCATENATION:
    ret = prune_useless_repetitions(n->Left, branch);
    ret |= reduce_useless_repetitions(n->Left, branch);
    ret |= prune_useless_repetitions(n->Right, branch);
    ret |= reduce_useless_repetitions(n->Right, branch);
    break;

  case Node::REPETITION:
  case Node::REPETITION_NG:
    ret = reduce_useless_repetitions(n->Left, branch);
    break;

  case Node::DOT:
  case Node::CHAR_CLASS:
  case Node::LITERAL:
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

bool reduce_useless_repetitions(Node* root) {
  std::stack<Node*> branch;
  return reduce_useless_repetitions(root, branch);
}

bool reduce_trailing_nongreedy_then_empty(Node* n, std::stack<Node*>& branch) {
  /*
     As a postfix, S{n,m}?T = S{n}T, when T admits zero-length matches.
    
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

     As a postfix, S{n,m}? = S{n}. This is a special case of the above,
     letting T = R{0}.
  */

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case Node::REGEXP:
    if (!n->Left) {
      return ret;
    }
  case Node::REPETITION:
    ret = reduce_trailing_nongreedy_then_empty(n->Left, branch);
    break;

  case Node::REPETITION_NG:
    // replace S{n,m}? with S{n}
    n->Type = Node::REPETITION;
    n->Max = n->Min;
    reduce_trailing_nongreedy_then_empty(n->Left, branch);
    ret = true;
    break;

  case Node::ALTERNATION:
    ret = reduce_trailing_nongreedy_then_empty(n->Left, branch);
    ret |= reduce_trailing_nongreedy_then_empty(n->Right, branch);
    break;

  case Node::CONCATENATION:
    if (has_zero_length_match(n->Right)) {
      if (n->Left->Type == Node::REPETITION_NG) {
        // the left child is S{n,m}?, the right child is T

        // replace S{n,m}? with S{n}
        n->Left->Type = Node::REPETITION;
        n->Left->Max = n->Left->Min;

        ret = true;
      }
      else if (n->Left->Type == Node::CONCATENATION &&
               n->Left->Right->Type == Node::REPETITION_NG) {
        // the right grandchild is S{n,m}?, the right child is T

        // replace S{n,m}? with S{n}
        n->Left->Right->Type = Node::REPETITION;
        n->Left->Right->Max = n->Left->Right->Min;

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

  case Node::DOT:
  case Node::CHAR_CLASS:
  case Node::LITERAL:
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

bool reduce_trailing_nongreedy_then_empty(Node* root) {
  std::stack<Node*> branch;
  return reduce_trailing_nongreedy_then_empty(root, branch);
}

void prune_subtree(Node *n, std::stack<Node*>& branch) {
  if (n->Type == Node::REGEXP) {
    n->Left = 0;
    branch.push(n);
    return;
  }

  Node* p = branch.top();

  switch (p->Type) {
  case Node::REGEXP:
    // the whole pattern has been pruned!
    p->Left = 0;
    break;

  case Node::ALTERNATION:
  case Node::CONCATENATION:
    // replace the parent node with the sibling node
    {
      Node* sibling = p->Left == n ? p->Right : p->Left;

      branch.pop();
      Node* gp = branch.top();

      if (gp->Left == p) {
        gp->Left = sibling;
      }
      else {
        gp->Right = sibling;
      }
    }
    break;

  case Node::REPETITION:
  case Node::REPETITION_NG:
    // prune the parent node
    branch.pop();
    prune_subtree(p, branch);
    break;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}
