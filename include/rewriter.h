/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

#pragma once

#include "parsenode.h"

#include <stack>

bool has_zero_length_match(const ParseNode* root);

bool reduce_empty_subtrees(ParseNode* root);
bool reduce_useless_repetitions(ParseNode* root);
bool reduce_trailing_nongreedy_then_empty(ParseNode* root);
bool reduce_trailing_nongreedy_then_greedy(ParseNode* root);

bool combine_consecutive_repetitions(ParseNode* root);
bool make_binops_right_associative(ParseNode* root);


void splice_out_parent(ParseNode* gp, const ParseNode* p, ParseNode* c);
