
#include "rewriter.h"

#include <stack>

void splice_out_parent(Node* node, std::stack<Node*>& branch) {
  Node* parent = branch.top();
  branch.pop();
  Node* gparent = branch.top();

  if (gparent->Left == parent) {
    gparent->Left = node;
  }
  else {
    gparent->Right = node;
  }
}

void prune_tree(Node *root, std::stack<Node*> branch) {
  Node* n = root;

  // follow the rightmost branch
  while (n) {
    branch.push(n);

    switch (n->Type) {
    case Node::REGEXP:
    case Node::CONCATENATION:
    case Node::PLUS:
    case Node::STAR:
    case Node::QUESTION:
      // keep going
      break;
    case Node::ALTERNATION:
      prune_tree(n->Right, branch);

      if (n->Right == 0) {
        if (n->Left == 0) {
          // roll up back to the root
          while (!branch.empty()) {
            n = branch.top();
            branch.pop();
          }

          n->Left = 0; 
        }
        else {
          splice_out_parent(n->Left, branch);
          n = branch.top();
        }
      }
      else {
        prune_tree(n->Left, branch);
        if (n->Left == 0) {
          splice_out_parent(n->Right, branch);
          n = branch.top();
        }
        else {
          return;
        }
      }
      break;
    case Node::PLUS_NG:
      // prune out +?, then continue from parent of +?
      splice_out_parent(n->Left, branch);
      n = branch.top();
      break;
    case Node::STAR_NG:
    case Node::QUESTION_NG:
      // prune everything below ??, *? and all repetitions immediately above
      { 
        Node* op = n;
        branch.pop();
        Node* parent = branch.top(); 

        while (op) {
          switch (parent->Type) {
          case Node::REGEXP:
            // delete subtree rooted at op
            op = 0;
            
            parent->Left = 0; 
            n = parent;
            break;

          case Node::ALTERNATION:
            {
              // delete subtree rooted at op
              if (parent->Left == op) {
                parent->Left = 0;
              }
              else {
                parent->Right = 0;
              }            

              // check whether we have alternations back to the root
              Node* x = branch.top();
              while (x->Type == Node::ALTERNATION) {
                branch.pop();
                x = branch.top();
              }

              if (x->Type == Node::REGEXP) {
                parent->Left = parent->Right = 0;
              }

              return;
            }

          case Node::CONCATENATION:
            {
              // delete subtree rooted at op
              op = 0;
      
              splice_out_parent(parent->Left, branch);
              n = branch.top();         
            }
            break;

          case Node::PLUS:
          case Node::STAR:
          case Node::QUESTION:
            // back up one node
            op = parent;
            branch.pop();
            parent = branch.top();
            break;

          // already removed
          case Node::PLUS_NG:
          // can't be above us
          case Node::STAR_NG:
          case Node::QUESTION_NG:
          // no children
          case Node::DOT:
          case Node::CHAR_CLASS:
          case Node::LITERAL:
          default:
            // impossible
            break;
          }
        }
      }
      break;
    case Node::DOT:
    case Node::CHAR_CLASS:
    case Node::LITERAL:
      // finished
      break;
    default:
      break;
    }

    n = n->Right ? n->Right : n->Left;
  }
}

void prune_tree(Node *root) {
  prune_tree(root, std::stack<Node*>());
}
