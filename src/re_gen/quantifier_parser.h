#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/lexical_cast.hpp>

std::string op_nquant(unsigned int n) {
  return '{' + boost::lexical_cast<std::string>(n) + '}';
}

std::string op_nxquant(unsigned int n) {
  return '{' + boost::lexical_cast<std::string>(n) + ",}";
}

std::string op_nmquant(unsigned int n, unsigned int m) {
  return '{' + boost::lexical_cast<std::string>(n) + ','
             + boost::lexical_cast<std::string>(m) + '}';
}

template <class InputIterator>
void throw_unrecognized_quant(InputIterator i, InputIterator i_end) {
  std::ostringstream ss;
  ss << "unrecognized quantifier: " << std::string(i, i_end);
  throw std::runtime_error(ss.str());
}

/*
  Parses quantifier specifiers into concrete quantifiers.

  These quantifiers are accepted as-is:

  * + ? *? +? ?? {n} {n,} {n,m} {n}? {n,}? {n,m}?

  Ranges are expanded:

  {n0-n1}       => {n0},...,{n1}
  {n0-n1,}      => {n0,},...,{n1,}
  {n0-n1,m0-m1} => {n0,m0},{n0,m0+1},...,{n1,m1-1},{n1,m1}

*/

template<class InputIterator, class OutputIterator>
void quantifier_parser(InputIterator i, InputIterator i_end, OutputIterator o) {

  InputIterator i_start(i);

  enum State { ANY, GREEDY, LOW_FIRST, LOW, LOW_RANGE, LOW_RANGE_FIRST,
               HIGH_FIRST, HIGH, HIGH_RANGE_FIRST, HIGH_RANGE, END };

  State state = ANY;

  char q = '\0';
  std::string n0_str, n1_str;
  std::string m0_str, m1_str;

  bool unbounded = false;
  bool greedy = true;

  for ( ; i != i_end; ++i) {
    switch (state) {
    case ANY:
      switch (*i) {
      case '*':
      case '+':
      case '?':
        q = *i;
        state = GREEDY;
        break;

      case '{':
        state = LOW_FIRST;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case GREEDY:
      switch (*i) {
      case '?':
        greedy = false;
        state = END;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case LOW_FIRST:
      switch (*i) {
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
        n0_str += *i;
        state = LOW;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case LOW:
      switch (*i) {
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
        n0_str += *i;
        break;

      case '-':
        state = LOW_RANGE;
        break;

      case ',':
        state = HIGH_FIRST;
        break;

      case '}':
        state = GREEDY;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case LOW_RANGE_FIRST:
      switch (*i) {
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
        n1_str += *i;
        state = LOW_RANGE;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case LOW_RANGE:
      switch (*i) {
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
        n1_str += *i;
        break;

      case ',':
        state = HIGH_FIRST;
        break;

      case '}':
        state = GREEDY;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case HIGH_FIRST:
      switch (*i) {
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
        m0_str += *i;
        state = HIGH;
        break;

      case '}':
        unbounded = true;
        state = GREEDY;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case HIGH:
      switch (*i) {
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
        m0_str += *i;
        break;

      case '-':
        state = HIGH_RANGE;
        break;

      case '}':
        state = GREEDY;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case HIGH_RANGE_FIRST:
      switch (*i) {
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
        m1_str += *i;
        state = HIGH_RANGE;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case HIGH_RANGE:
      switch (*i) {
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
        m1_str += *i;
        break;

      case '}':
        state = GREEDY;
        break;

      default:
        throw_unrecognized_quant(i_start, i_end);
      }
      break;

    case END:
      throw_unrecognized_quant(i_start, i_end);
    }
  }

  // NB: GREEDY is an accepting state
  if (state != END && state != GREEDY) {
    throw_unrecognized_quant(i_start, i_end);
  }

  if (!n0_str.empty()) {
    // output a range quantifier

    const unsigned int n0 = boost::lexical_cast<unsigned int>(n0_str);
    const unsigned int n1 = n1_str.empty() ? n0 :
                            boost::lexical_cast<unsigned int>(n1_str);

    if (!m0_str.empty()) {
      const unsigned int m0 = boost::lexical_cast<unsigned int>(m0_str);
      const unsigned int m1 = m1_str.empty() ? m0 :
                              boost::lexical_cast<unsigned int>(m1_str);

      // this is the {n,m} case
      for (unsigned int j = n0; j <= n1; ++j) {
        for (unsigned int k = std::max(j, m0); k <= m1; ++k) {
          *(o++) = op_nmquant(j,k) + (greedy ? "" : "?");
        }
      }
    }
    else {
      if (unbounded) {
        // this is the {n,} case
        for (unsigned int j = n0; j <= n1; ++j) {
          *(o++) = op_nxquant(j) + (greedy ? "" : "?");
        }
      }
      else {
        // this is the {n} case, no range
        for (unsigned int j = n0; j <= n1; ++j) {
          *(o++) = op_nquant(j) + (greedy ? "" : "?");
        }
      }
    }
  }
  else {
    // output a simple quantifier
    *(o++) = std::string(1, q) + (greedy ? "" : "?");
  }
}
