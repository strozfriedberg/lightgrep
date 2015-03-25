/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2015 Lightbox Technologies, Inc

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

#include <sstream>
#include <stdexcept>
#include <string>

template <class InputIterator>
void throw_unrecognized_assertion(InputIterator i_beg, InputIterator i_end) {
  std::ostringstream ss;
  ss << "unrecognized assertion: " << std::string(i_beg, i_end);
  throw std::runtime_error(ss.str());
}

template<class InputIterator, class OutputIterator>
void assertion_parser(InputIterator i, InputIterator i_end, OutputIterator o) {

  InputIterator i_start(i);

  enum State { ANY, ESC };

  State state = ANY;

  std::string tok;

  for ( ; i != i_end; ++i) {
    switch (state) {
    case ANY:
      switch (*i) {
      case '$':
      case '^':
        tok = *i;
        *(o++) = tok;
        tok.clear();
        state = ANY;
        break;

      case '\\':
        tok = "\\";
        state = ESC;
        break;

      default:
        throw_unrecognized_assertion(i_start, i_end);
      }
      break;

    case ESC:
      switch (*i) {
      case 'A':
      case 'B':
      case 'K':
      case 'Z':
      case 'b':
        tok += *i;
        *(o++) = tok;
        tok.clear();
        state = ANY;
        break;
      default:
        throw_unrecognized_assertion(i_start, i_end);
      }
      break; 
    }
  }

  if (state != ANY) {
    throw_unrecognized_assertion(i_start, i_end);
  }
}
