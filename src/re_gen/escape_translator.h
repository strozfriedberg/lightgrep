/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013 Lightbox Technologies, Inc

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

#include <cerrno>
#include <cstring>
#include <sstream>
#include <stdexcept>

#include <boost/numeric/conversion/cast.hpp>

/*
  This is a state machine for translating a string containing C escsape
  sequences into a string containing the characters represented by those
  escape sequences.
*/

template<class InputIterator, class OutputIterator>
void escape_translator(InputIterator i, InputIterator i_end, OutputIterator o) {

  enum class State { ANY, ESC, HEX1, HEX2, OCT2, OCT3 };

  State state = State::ANY;

  char oct[4];
  char hex[3];

  hex[2] = oct[3] = '\0';

  for ( ; i != i_end; ++i) {
    switch (state) {
    case State::ANY:
      switch (*i) {
      case '\\':
        // the start of an escape
        state = State::ESC;
        break;

      default:
        // a regular character
        *(o++) = *i;
        break;
      }
      break;

    case State::ESC:
      switch (*i) {
      // these escape sequences are just themselves
      case '?':
      case '"':
      case '\'':
      case '\\':
        *(o++) = *i;
        state = State::ANY;
        break;

      // these escape sequences need to be translated
      case 'a':  *(o++) = '\a'; state = State::ANY; break;
      case 'b':  *(o++) = '\b'; state = State::ANY; break;
      case 'f':  *(o++) = '\f'; state = State::ANY; break;
      case 'n':  *(o++) = '\n'; state = State::ANY; break;
      case 'r':  *(o++) = '\r'; state = State::ANY; break;
      case 't':  *(o++) = '\t'; state = State::ANY; break;
      case 'v':  *(o++) = '\v'; state = State::ANY; break;

      // the start of a hexadecimal escape
      case 'x':
        state = State::HEX1;
        break;

      // either an octal escape, or \0
      case '0':
        if (i+1 != i_end && '0' <= *i && *i <= '7') {
          oct[0] = '0';
          state = State::OCT2;
        }
        else {
          *(o++) = '\0';
          state = State::ANY;
        }
        break;

      // the start of an octal escape
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        oct[0] = *i;
        state = State::OCT2;
        break;

      default:
        std::ostringstream ss;
        ss << "unrecognized escape: \\" << *i;
        throw std::runtime_error(ss.str());
      }
      break;

    case State::HEX1:
      if (std::isxdigit(*i)) {
        hex[0] = *i;
        state = State::HEX2;
      }
      else {
        std::ostringstream ss;
        ss << "bad hex escape: \\x" << *i;
        throw std::runtime_error(ss.str());
      }
      break;

    case State::HEX2:
      if (std::isxdigit(*i)) {
        hex[1] = *i;

        const unsigned long v = std::strtoul(hex, NULL, 16);
        if (errno) {
          std::ostringstream ss;
          ss << "hex conversion failed: \\x" << hex << ": "
             << std::strerror(errno);
          throw std::runtime_error(ss.str());
        }

        *(o++) = boost::numeric_cast<unsigned char>(v);

        state = State::ANY;
      }
      else {
        std::ostringstream ss;
        ss << "bad hex escape: \\x" << hex[0] << *i;
        throw std::runtime_error(ss.str());
      }
      break;

    case State::OCT2:
      switch (*i) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        oct[1] = *i;
        state = State::OCT3;
        break;

      default:
        std::ostringstream ss;
        ss << "bad octal escape: \\" << oct[0] << *i;
        throw std::runtime_error(ss.str());
      }
      break;

    case State::OCT3:
      switch (*i) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        {
          oct[2] = *i;

          const unsigned long v = strtoul(oct, NULL, 8);
          if (errno) {
            std::ostringstream ss;
            ss << "octal conversion failed: \\" << hex << ": "
               << strerror(errno);
            throw std::runtime_error(ss.str());
          }

          *(o++) = boost::numeric_cast<unsigned char>(v);

          state = State::ANY;
        }
        break;

      default:
        std::ostringstream ss;
        ss << "bad octal escape: \\" << oct[0] << oct[1] << *i;
        throw std::runtime_error(ss.str());
      }
    }
  }
}
