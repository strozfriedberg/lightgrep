#pragma once

#include "node.h"

#include <stack>

bool has_zero_length_match(const Node* root);

bool reduce_empty_repetitions(Node* root);
bool reduce_exact_nongreedy_repetitions(Node* root);
bool reduce_trailing_nongreedy(Node* root);
bool reduce_trailing_nongreedy_then_empty(Node* root);

void remove_child(Node* parent, Node* child);
void prune_subtree(Node* n, std::stack<Node*>& branch);

