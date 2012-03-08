#pragma once

#include <iostream>

int parseHexChar(int c);

template <typename Iterator>
int parseHexShort(Iterator& i, const Iterator& end) {
  int val = parseHexChar(*i++);
  if (val < 0 || i == end) {
    return -1;
  }
  val <<= 4;
  val |= parseHexChar(*i++);
  return val < 0 ? -1 : val;
}

template <typename Iterator>
int parseHexLong(Iterator& i, const Iterator& iend) {
  const Iterator end = std::min(i + 7, iend);
  for (int c, val = 0; i != end; ) {
    c = *i++;
    switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      val <<= 4; 
      val |= c - '0';
      break;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
      val <<= 4; 
      val |= c - 'A' + 10;
      break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
      val <<= 4; 
      val |= c - 'a' + 10;
      break;
    case '}':
      return val;
    default:
      return -1;
    }
  }
  return -1;
}

// Should accept: \\x[0-9A-Fa-f]{2} and \\x\{[0-9A-Fa-f]{0,6}\}
template <typename Iterator>
int parseHex(Iterator& i, const Iterator& end) {
  return *i == '{' ? parseHexLong(++i, end) : parseHexShort(i, end);
}

int parseOctChar(int c);

// Should accept \\[0-7]{1,3}
template <typename Iterator>
int parseOct(Iterator& i, const Iterator& iend) {
  int oct = 0;

  const Iterator end = std::min(i + 3, iend);
  for (int digit; i != end; ) {
    digit = parseOctChar(*i);

    if (digit == -1) {
      break;
    }

    ++i;
    oct <<= 3;
    oct |= digit;
  }

  return oct > 0377 ? -1 : oct;
}
