#include <sstream>
#include <stdexcept>
#include <string>

template <class InputIterator> 
void throw_unrecognized_alpha(InputIterator i_beg, InputIterator i_end) {
  std::ostringstream ss;
  ss << "unrecognized alpha: " << std::string(i_beg, i_end);
  throw std::runtime_error(ss.str());
}

/*
  Parses an alphabet string into tokens suitable for insertion into a
  regex form. 
*/

template<class InputIterator, class OutputIterator>
void alphabet_parser(InputIterator i, InputIterator i_end, OutputIterator o) {

  InputIterator i_start(i);

  enum State { ANY, ESC, HEX1, HEX2, OCT2, OCT3 };

  State state = ANY;

  std::string tok;

  for ( ; i != i_end; ++i) { 
    switch (state) {
    case ANY:
      switch (*i) {
      case '\\':
        tok = "\\";
        state = ESC;
        break;

      default:
        tok += *i;
        *(o++) = tok;
        tok.clear();
        break;
      }
      break;

    case ESC:
      switch (*i) {
      // named escapes  
      case '?':
      case '"':
      case '\'':
      case '\\':
      case 'a':
      case 'b':
      case 'f':
      case 'n':
      case 'r':
      case 't':
      case 'v':
        tok += *i;
        *(o++) = tok;
        tok.clear();
        state = ANY;
        break;
  
      // the start of a hex escape
      case 'x':
        tok += 'x';
        state = HEX1;
        break; 

      // either an octal escape, or \0
      case '0':
        tok += *i;

        if (i+1 != i_end && '0' <= *i && *i <= '7') {
          state = OCT2;
        }
        else {
          *(o++) = tok;
          tok.clear();
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
        tok += *i;
        state = OCT2;
        break;
    
      default:
        throw_unrecognized_alpha(i_start, i_end);
      }
      break;

    case HEX1:
      if (isxdigit(*i)) {
        tok += *i;
        state = HEX2;
      }
      else {
        throw_unrecognized_alpha(i_start, i_end);
      }
      break;

    case HEX2:
      if (isxdigit(*i)) {
        tok += *i;
        *(o++) = tok;
        tok.clear();
        state = ANY;
      }
      else {
        throw_unrecognized_alpha(i_start, i_end);
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
        tok += *i;
        state = OCT3;
        break;

      default:
        throw_unrecognized_alpha(i_start, i_end);
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
        tok += *i;
        *(o++) = tok;
        tok.clear();
        state = ANY;
        break;

      default:
        throw_unrecognized_alpha(i_start, i_end);
      }
      break;
    }
  }

  if (state != ANY) {
    throw_unrecognized_alpha(i_start, i_end);
  }
}
