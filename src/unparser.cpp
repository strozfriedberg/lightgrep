
#include "unparser.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>

#include <boost/lexical_cast.hpp>

bool is_binary(const Node* n) {
  return n->Type == Node::ALTERNATION || n->Type == Node::CONCATENATION;
}

//
// Parentheses are necessary when:
// 
// * a unary operator is the parent of a binary operator
// * concatenation is the parent of an alternation
//

void open_paren(const Node* n, std::stringstream& ss) {
  if (!is_binary(n) && is_binary(n->Left)) {
    ss << '(';
  }
} 

void close_paren(const Node *n, std::stringstream& ss) {
  if (!is_binary(n) && is_binary(n->Left)) {
    ss << ')';
  }
} 

std::string byteToCharacterString(uint32 i) {
  // all the characters fit to print unescaped
  if (i == '\\') {
    return "\\\\";
  }
  else if (0x20 <= i && i <= 0x7E) {
    return std::string(1, (char) i);
  }
  else {
    switch (i) {
    // all of the named single-character escapes
    case 0x07: return "\\a";
    case 0x08: return "\\b";
    case 0x09: return "\\t";
    case 0x0C: return "\\f";
    case 0x0D: return "\\r";
    case 0x1B: return "\\e";
    // otherwise, print the hex code
    default:  
      {
        std::stringstream ss;
        ss << "\\x" << std::hex << std::uppercase 
                    << std::setfill('0') << std::setw(2) << i;
        return ss.str();
      }
    }
  }
}

/*
 * Rules for escaping inside character classes:
 *
 * ']' must be escaped unless it is first, or immediately follows a negation
 * '^' must be escaped if it is first
 * '-' must be escaped if it would form an unwanted range
 * '\' must be escaped 
 *
 */

std::string byteSetToCharacterClass(const ByteSet& bs) {

  // check relative size of 0 and 1 ranges 
  int sizediff = -1; // negated has a 1-char disadvantage due to the '^'
  uint32 left = 0;
  
  bool hasBoth = false;  

  for (uint32 i = 1; i < 257; ++i) {
    if (i < 256 && bs[i] ^ bs[0]) {
      hasBoth = true;
    }
    
    if (i == 256 || bs[i-1] ^ bs[i]) {
      const uint32 len = std::min(i - left, (uint32) 3);
      sizediff += bs[i-1] ? len : -len;
      left = i;
    }  
  }

  // is this a full or empty character class?
  if (!hasBoth) {
    return bs[0] ? "\\x00-\\xFF" : "^\\x00-\\xFF";
  }

  // will char class will be shorter if negated?
  const bool invert = sizediff > 0;

  std::stringstream ss;
 
  if (invert) {
    ss << '^';
  }
 
  bool first = true;
  bool caret = false;
  bool hyphen = false;
  
  left = 256;

  for (uint32 i = 0; i < 257; ++i) {
    if (i < 256 && (invert ^ bs[i])) {
      if (left > 0xFF) {
        // start a new range
        left = i;
      }
    }
    else if (left <= 0xFF) {
      // write a completed range
      uint32 right = i-1;

      // shrink ranges so that the hyphen is neither endpoint
      if (left == '-') {
        hyphen = true;

        if (left == right) {
          // hyphen is the whole range
          left = 256;
          first = false; 
          continue;
        }

        ++left;
      }
      else if (right == '-') {
        hyphen = true;
        --right;
      }
  
      // shrink initial range so that the caret is not the start
      if ((first || hyphen) && left == '^') {
        caret = true;

        if (left == right) {
          // caret is the whole range
          left = 256;
          first = false; 
          continue;
        }

        ++left;
      }

      if (right - left + 1 < 4) {
        // enumerate small ranges
        for (uint32 j = left; j <= right; ++j) {
          if (j == ']') {
            if (first) {
              first = false;
            }
            else {
              ss << '\\';
            }
          }

          ss << byteToCharacterString(j);
        }
      }
      else {
        // use '-' for large ranges

        if (left == ']') {
          if (first) {
            first = false;
          }
          else {
            ss << '\\';
          }
        }

        ss << byteToCharacterString(left) << '-';

        if (right == ']') {
          ss << '\\';
        }

        ss << byteToCharacterString(right);
      }

      left = 256;
      first = false;
    }
  }

  // if there was a hyphen, put it at the end
  if (hyphen) {
    if (caret) {
      // if we haven't written anything, reverse the hyphen and caret
      if (ss.tellp() == 0) {
        ss << byteToCharacterString('-') << byteToCharacterString('^');
      }
      else {
        ss << byteToCharacterString('^') << byteToCharacterString('-');
      }
    }
    else {
      ss << byteToCharacterString('-');
    }
  }
  // if there was a caret, put it at the end
  else if (caret) {
    // if we haven't written anything, escape the caret
    if (ss.tellp() == 0) {
      ss << '\\';
    }
    ss << byteToCharacterString('^');  
  } 

  return ss.str();
}

void unparse(const Node* n, std::stringstream& ss) {
  switch (n->Type) {
  case Node::REGEXP:
    if (!n->Left) {
      return;
    }

    unparse(n->Left, ss);
    break;

  case Node::ALTERNATION:
    unparse(n->Left, ss);
    ss << '|';
    unparse(n->Right, ss);
    break;

  case Node::CONCATENATION:
    if (n->Left->Type == Node::ALTERNATION) {
      ss << '(';
      unparse(n->Left, ss);
      ss << ')';
    }
    else {
      unparse(n->Left, ss);
    }

    if (n->Right->Type == Node::ALTERNATION) {
      ss << '(';
      unparse(n->Right, ss);
      ss << ')';
    }
    else {
      unparse(n->Right, ss);
    }
    break;

  case Node::PLUS:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << '+';
    break;

  case Node::STAR:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << '*';
    break;

  case Node::QUESTION:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << '?';
    break;

  case Node::PLUS_NG:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << "+?";
    break;

  case Node::STAR_NG:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << "*?";
    break;

  case Node::QUESTION_NG:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << "??";
    break;

  case Node::DOT:
    ss << '.';
    break;

  case Node::CHAR_CLASS:
    ss << '[' << byteSetToCharacterClass(n->Bits) << ']';
    break;

  case Node::LITERAL:
    ss << (char) n->Val;
    break;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}

std::string unparse(const ParseTree& tree) {
  std::stringstream ss;
  unparse(tree.Root, ss);
  return ss.str();
}

