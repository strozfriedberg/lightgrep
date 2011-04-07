#pragma once

#include "node.h"

bool has_zero_length_match(const Node* root);

void reduce_trailing_zero_length(Node* root);

void prune_tree(Node* root);
