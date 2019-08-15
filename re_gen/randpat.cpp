
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stack>
#include <vector>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "node.h"
#include "parsetree.h"
#include "unparser.h"

// C_17 is the largest Catalan number which fits in 32 bits
// C_33 is the largest Catalan number which fits in 64 bits 
uint64 catalan(uint32 n) {
  return n == 0 ? 1 : catalan(n-1)*2*(2*n-1)/(n+1);
}

// random integer in [lb,ub)
template <typename L, typename U>
U rand_int(L lb, U ub) {
  return (U) ((rand()/(double) RAND_MAX)*(ub-lb) + lb);
}

int main(int argc, char** argv) {

  // nmax = the maximum number of nodes in the parse tree
  //
  // 33 is the largest nmax we can handle, due to the need to compute
  // Catalan numbers for the probability distribution
  const uint32 nmax = boost::lexical_cast<uint32>(argv[1]);

  // pcount is the number of patterns to produce
  const uint32 pcount = boost::lexical_cast<uint32>(argv[2]);

  // TODO: We could put these in a table, since we can't use anything
  // above C_33. (Or, for larger patterns, we could approximate the
  // Catalan numbers, or use long doubles...)

  // C[i] is the ith Catalan number
  std::vector<uint64> C(nmax);
 
  for (uint32 i = 0; i < nmax; ++i) {
    C[i] = catalan(i);
  }

  // sumC[n] is the sum of C[i], 0 <= i < n
  std::vector<uint64> sumC(C);
  std::partial_sum(C.begin(), C.end(), sumC.begin()); 

/*
  std::copy(C.begin(), C.end(), std::ostream_iterator<uint64>(std::cout, "\n"));
  std::cout << '\n';
  std::copy(sumC.begin(), sumC.end(), std::ostream_iterator<uint64>(std::cout, "\n"));
*/

  // Seed for the PRNG
  const uint32 seed = argc > 3 ? boost::lexical_cast<uint32>(argv[3]) : time(0);
  srand(seed);

  for (uint32 pnum = 0; pnum < pcount; ++pnum) {
    // The number of non-isomorphic ordered binary trees with exactly n
    // nodes is C_{n-1}. Therefore, the number of nonempty trees with at
    // most n nodes is \sum_{k=1}^{n} C_{k-1}.

    // Determine the number of nodes in the parse tree: Find the first
    // cumulative Catalan number such that a random number in [0,sumC[nmax])
    // is less than it.
    const uint64 rc = rand_int(0, sumC[nmax-1]);
    const uint32 n = std::find_if(
      sumC.begin(), sumC.end(),
      boost::bind(std::less<uint64>(), rc, _1)) - sumC.begin();

    // Build a random n-node binary tree.
    ParseTree tree;
    tree.init(n+1); // extra node is for the REGEXP root
    
    Node* ig = tree.add(Node(Node::IGNORE, (Node*) 0, (Node*) 0));
    tree.Root = tree.add(Node(Node::REGEXP, ig));
    std::vector<Node*> available(1, ig);

    // NB: count from 1 because available starts with one node
    uint32 ni;
    for (uint32 i = 1; i < n; ++i) {
      ni = rand_int(0, available.size());
      Node* p = available[ni];
      Node* c = tree.add(Node(Node::IGNORE, (Node*) 0, (Node*) 0));

      if (!p->Left) {
        p->Left = c;  
        available.push_back(c);
      }
      else {
        p->Right = c;
        available[ni] = c;
      }
    }
 
    // Assign types to the non-root nodes.

    std::stack<Node*> stack;
    stack.push(tree.Root->Left);

    while (!stack.empty()) {
      Node* node = stack.top();
      stack.pop();

      if (node->Right) {
        // two children, choose a binary operator
        switch (rand_int(0, 2)) {
        case 0: node->Type = Node::ALTERNATION;   break;
        case 1: node->Type = Node::CONCATENATION; break;
        }
        stack.push(node->Left);
        stack.push(node->Right);
      }
      else if (node->Left) {
        // one child, choose a unary operator
        switch (rand_int(0, 6)) {
        case 0:
          // ?
          node->Type = Node::REPETITION;
          node->Min = 0;
          node->Max = 1;
          break;
        case 1:
          // *
          node->Type = Node::REPETITION;
          node->Min = 0;
          node->Max = UNBOUNDED;
          break;
        case 2:
          // +
          node->Type = Node::REPETITION;
          node->Min = 1;
          node->Max = UNBOUNDED;
          break;
        case 3:
          // ??
          node->Type = Node::REPETITION_NG;
          node->Min = 0;
          node->Max = 1;
          break;
        case 4:
          // *?
          node->Type = Node::REPETITION_NG;
          node->Min = 0;
          node->Max = UNBOUNDED;
          break;
        case 5:
          // +?
          node->Type = Node::REPETITION_NG;
          node->Min = 1;
          node->Max = UNBOUNDED;
          break;
        }
        stack.push(node->Left);
      }
      else {
        node->Type = Node::LITERAL;
        node->Val = rand_int(97, 123);  // a-z
  /*
        // no children, choose an atom
        switch (rand_int(0, 3)) {
        case 0:
          node->Type = Node::LITERAL;
          node->Val = rand_int(0, 256);
          break;
        case 1:
          node->Type = Node::DOT;
          break;
        case 2:
          node->Type = Node::CHAR_CLASS;
          for (uint32 i = 0; i < 256; ++i) {
            node->Bits[i] = rand_int(0, 2);
          }
          break;
        }
  */
      }
    }
  
    std::cout << unparse(tree) << '\n';
  }

  return 0;
}
