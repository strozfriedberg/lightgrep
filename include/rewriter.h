#pragma once

#include "parsenode.h"

#include <stack>

bool has_zero_length_match(const ParseNode* root);

bool reduce_empty_subtrees(ParseNode* root);
bool reduce_useless_repetitions(ParseNode* root);
bool reduce_trailing_nongreedy_then_empty(ParseNode* root);

bool combine_consecutive_repetitions(ParseNode* root);
bool make_binops_right_associative(ParseNode* root);


void splice_out_parent(ParseNode* gp, const ParseNode* p, ParseNode* c);
