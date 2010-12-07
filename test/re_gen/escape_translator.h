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

  enum State { ANY, ESC, HEX1, HEX2, OCT2, OCT3 };

  State state = ANY;

  char oct[4];
  char hex[3];

  hex[2] = oct[3] = '\0';

  for ( ; i != i_end; ++i) {
    switch (state) {
    case ANY:
      switch (*i) {
      case '\\':
        // the start of an escape
        state = ESC;
        break;

      default:
        // a regular character
        *(o++) = *i;
        break;
      }
      break;

    case ESC:
      switch (*i) {
      // these escape sequences are just themselves
      case '?':
      case '"':
      case '\'':
      case '\\':
        *(o++) = *i;
        state = ANY;
        break;

      // these escape sequences need to be translated
      case 'a':  *(o++) = '\a'; state = ANY; break;
      case 'b':  *(o++) = '\b'; state = ANY; break;
      case 'f':  *(o++) = '\f'; state = ANY; break;
      case 'n':  *(o++) = '\n'; state = ANY; break; 
      case 'r':  *(o++) = '\r'; state = ANY; break;
      case 't':  *(o++) = '\t'; state = ANY; break;
      case 'v':  *(o++) = '\v'; state = ANY; break;

      // the start of a hexadecimal escape
      case 'x':
        state = HEX1;
        break;
      
      // either an octal escape, or \0
      case '0':
        if (i+1 != i_end && '0' <= *i && *i <= '7') {
          oct[0] = '0';
          state = OCT2;
        }
        else {
          *(o++) = '\0';
          state = ANY;
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
        state = OCT2;
        break;

      default:
        std::ostringstream ss;
        ss << "unrecognized escape: \\" << *i;
        throw std::runtime_error(ss.str());
      }
      break;

    case HEX1:
      if (isxdigit(*i)) {
        hex[0] = *i;
        state = HEX2;
      }
      else {
        std::ostringstream ss;
        ss << "bad hex escape: \\x" << *i;
        throw std::runtime_error(ss.str());
      }
      break;
    
    case HEX2:
      if (isxdigit(*i)) {
        hex[1] = *i;
       
        const unsigned long v = strtoul(hex, NULL, 16);
        if (errno) {
          std::ostringstream ss;
          ss << "hex conversion failed: \\x" << hex << ": " << strerror(errno);
          throw std::runtime_error(ss.str());
        }        

        *(o++) = boost::numeric_cast<unsigned char>(v);

        state = ANY;
      }
      else {
        std::ostringstream ss;
        ss << "bad hex escape: \\x" << hex[0] << *i;
        throw std::runtime_error(ss.str());
      }
      break;

    case OCT2:
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
        state = OCT3;
        break;

      default:
        std::ostringstream ss;
        ss << "bad octal escape: \\" << oct[0] << *i;
        throw std::runtime_error(ss.str());
      }
      break;
  
    case OCT3:
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

          state = ANY;
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
