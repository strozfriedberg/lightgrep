
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
    // We don't check the left alternative for preferring zero-length
    // matches here because if it did, then the whole alternation would,
    // so we would already have pruned it away.

    if (has_only_zero_length_match(n->Right)) {
      // prune away right alternative
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
    ret = reduce_useless_repetitions(n->Left, branch);
    break;

  case Node::ALTERNATION:
  case Node::CONCATENATION:
    ret = reduce_useless_repetitions(n->Left, branch);
    ret |= reduce_useless_repetitions(n->Right, branch);
    break;

  case Node::REPETITION:
  case Node::REPETITION_NG:
    if (n->Min == 1 && n->Max == 1) {
      // remove {1,1}, {1,1}?
      branch.pop();
      Node* parent = branch.top();
      if (n == parent->Left) {
        parent->Left = n->Left;
      }
      else {
        parent->Right = n->Left;
      }

      reduce_useless_repetitions(n->Left, branch);
      ret = true;
    }
    else if (n->Min == n->Max && n->Type == Node::REPETITION_NG) {
      // reduce {n}? to {n}
      n->Type = Node::REPETITION;
      reduce_useless_repetitions(n->Left, branch);
      ret = true;
    }
    else {
      ret = reduce_useless_repetitions(n->Left, branch);
    }

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
     As as postfix, S+?T = ST, when T admits zero-length matches.
    
     In the tree, the adjacency can show up as either S+? and T being
     children of the same concatenation, or as T being the right uncle
     of S+?:
    
         &            &
        / \    OR    / \
       +?  T        &   T
        |          / \
        S            +?
                      |
                      S
  */

  bool ret = false;
  branch.push(n);

  switch (n->Type) {
  case Node::REGEXP:
    if (!n->Left) {
      return ret;
    }
  case Node::REPETITION:
  case Node::REPETITION_NG:
    // these are not the nodes you're looking for
    ret = reduce_trailing_nongreedy_then_empty(n->Left, branch);
    break;

  case Node::ALTERNATION:
    ret = reduce_trailing_nongreedy_then_empty(n->Left, branch);
    ret |= reduce_trailing_nongreedy_then_empty(n->Right, branch);
    break;

  case Node::CONCATENATION:

    if (has_zero_length_match(n->Right)) {
      // check whether the left child is {n,m}?, n > 0
      if (n->Left->Type == Node::REPETITION_NG && n->Left->Min > 0) {
        if (n->Left->Min == 1) {
          // strip out {1,m}?
          n->Left = n->Left->Left;
        }
        else {
          // replace {n,m}? with {n}
          n->Left->Type = Node::REPETITION;
          n->Left->Max = n->Left->Min;
        }
        ret = true;
      }
      // check whether the left nephew is {n,m}?, n > 0
      else if (n->Left->Type == Node::CONCATENATION &&
               n->Left->Right->Type == Node::REPETITION_NG &&
               n->Left->Right->Min > 0) { 
        if (n->Left->Right->Min == 1) {
          // strip out {1,m}?
          n->Left->Right = n->Left->Right->Left;
        }
        else {
          // replace {n,m}? with {n}
          n->Left->Right->Type = Node::REPETITION;
          n->Left->Right->Max = n->Left->Right->Min;
        }
        ret = true;
      }
    }

    if (!ret) {
      ret = reduce_trailing_nongreedy_then_empty(n->Right, branch);
    }

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

bool reduce_trailing_nongreedy(Node* n, std::stack<Node*>& branch) {
  switch (n->Type) {
  case Node::REGEXP:
    if (!n->Left) {
      return false;
    }
  case Node::REPETITION:
    branch.push(n);
    return reduce_trailing_nongreedy(n->Left, branch);

  case Node::CONCATENATION:
    branch.push(n);
    return reduce_trailing_nongreedy(n->Right, branch);

  case Node::ALTERNATION:
    {
      branch.push(n);
      std::stack<Node*> orig_branch(branch);

      const bool lreduce = reduce_trailing_nongreedy(n->Left, branch);

      if (n->Left) {
        // The left alternative wasn't pruned away, so we have to traverse
        // the subtree of the right alternative ourselves.
        return reduce_trailing_nongreedy(n->Right, orig_branch) || lreduce;
      }
      else {
        // The left alternative was pruned away, so the right alternative
        // was moved up the tree and has already been traversed.
        return lreduce;
      }
    }

  case Node::REPETITION_NG:
    if (n->Min > 0) {
      if (n->Min == 1) {
        // strip out {1,m}?
        Node* p = branch.top();

        if (p->Left == n) {
          p->Left = n->Left;
        }
        else {
          p->Right = n->Left;
        }
      }
      else {
        // convert {n,m}? to {n}
        n->Type = Node::REPETITION;
        n->Max = n->Min;
      }

      reduce_trailing_nongreedy(n->Left, branch);
    }
    else {
      // prune this subtree
      prune_subtree(n, branch);
      n = branch.top();
      branch.pop();
      reduce_trailing_nongreedy(n, branch);
    }
    return true;

  case Node::DOT:
  case Node::CHAR_CLASS:
  case Node::LITERAL:
    // branch finished
    return false;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}

bool reduce_trailing_nongreedy(Node* root) {
  std::stack<Node*> branch;
  return reduce_trailing_nongreedy(root, branch);
}
