#pragma once

#include "node.h"

#include <stack>

bool has_zero_length_match(const Node* root);

bool reduce_empty_subtrees(Node* root);
bool reduce_useless_repetitions(Node* root);
bool reduce_trailing_nongreedy_then_empty(Node* root);

void splice_out_parent(Node* gp, const Node* p, Node* c);
