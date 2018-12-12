/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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
