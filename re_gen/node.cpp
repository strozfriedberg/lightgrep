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

#include "node.h"

void repetition(std::ostream& out, uint32 min, uint32 max) {
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

std::ostream& operator<<(std::ostream& out, const Node& n) {
  switch (n.Type) {
  case Node::REGEXP:
    return out << "REGEXP";
  case Node::ALTERNATION:
    return out << '|';
  case Node::CONCATENATION:
    return out << '&';
  case Node::REPETITION:
    repetition(out, n.Min, n.Max);
    return out;
  case Node::REPETITION_NG:
    repetition(out, n.Min, n.Max);
    return out << '?';
  case Node::ELEMENT:
    return out << "ELEMENT";
  case Node::DOT:
    return out << '.';
  case Node::CHAR_CLASS:
    return out << n.Bits;
  case Node::LITERAL:
    return out << (char) n.Val;
  case Node::IGNORE:
    return out << "IGNORE";
  default:
    return out << "WTF";
  }
}

void printTree(std::ostream& out, const Node& n) {
  if (n.Right) {
    printTree(out, *n.Right);
  }

  if (n.Left) {
    printTree(out, *n.Left);
  }

  out << n << '\n';
}

void printTreeDetails(std::ostream& out, const Node& n) {
  if (n.Right) {
    printTreeDetails(out, *n.Right);
  }

  if (n.Left) {
    printTreeDetails(out, *n.Left);
  }

  out << &n << ' ' << n.Type << ' ' << n.Left << ' ' << n.Right << ' '
      << n.Val << ' ' << n.Min << ' ' << n.Max << '\n';
}

