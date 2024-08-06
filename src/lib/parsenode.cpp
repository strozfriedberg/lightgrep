/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "parsenode.h"

void repetition(std::ostream& out, uint32_t min, uint32_t max) {
  if (min == 0) {
    if (max == 1) {
      // ? is {0,1}
      out << '?';
      return;
    }
    else if (max == UNBOUNDED) {
      // * is {0,}
      out << '*';
      return;
    }
  }
  else if (min == 1 && max == UNBOUNDED) {
    // + is {1,}
    out << '+';
    return;
  }

  out << '{' << min;

  if (max == UNBOUNDED) {
    out << ',';
  }
  else if (max != min) {
    out << ',' << max;
  }

  out << '}';
}

std::ostream& operator<<(std::ostream& out, const ParseNode& n) {
  switch (n.Type) {
  case ParseNode::REGEXP:
    return out << "REGEXP";
  case ParseNode::LOOKBEHIND_POS:
    return out << "(?<=)";
  case ParseNode::LOOKBEHIND_NEG:
    return out << "(?<!)";
  case ParseNode::LOOKAHEAD_POS:
    return out << "(?=)";
  case ParseNode::LOOKAHEAD_NEG:
    return out << "(?!)";
  case ParseNode::ALTERNATION:
    return out << '|';
  case ParseNode::CONCATENATION:
    return out << '&';
  case ParseNode::REPETITION:
    repetition(out, n.Child.Rep.Min, n.Child.Rep.Max);
    return out;
  case ParseNode::REPETITION_NG:
    repetition(out, n.Child.Rep.Min, n.Child.Rep.Max);
    return out << '?';
  case ParseNode::DOT:
    return out << '.';
  case ParseNode::CHAR_CLASS:
    return out << n.Set.CodePoints
               << (n.Set.Breakout.Additive ? '+' : '-') << ' '
               << n.Set.Breakout.Bytes;
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    return out << std::hex << n.Val << std::dec;
  case ParseNode::TEMPORARY:
    return out << "TEMPORARY";
  default:
    return out << "WTF";
  }
}

/*
void printTreeDetails(std::ostream& out, const ParseNode& n) {
  if ((n.Type == ParseNode::CONCATENATION ||
       n.Type == ParseNode::ALTERNATION) && n.Child.Right) {
    printTreeDetails(out, *n.Child.Right);
  }

  if (n.Left) {
    printTreeDetails(out, *n.Child.Left);
  }

  out << &n << ' ' << n.Type << ' ' << n.Child.Left << ' ';

  switch (n.Type) {
  case ParseNode::CONCATENATION:
  case ParseNode::ALTERNATION:
    out << n.Right;
    break;
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    out << n.Rep.Min << ' ' << n.Rep.Max;
    break;
  case ParseNode::LITERAL:
  case ParseNode::BYTE:
    out << n.Val;
    break;
  case ParseNode::CHAR_CLASS:
  default:
    break;
  }

  out << '\n';
}
*/
