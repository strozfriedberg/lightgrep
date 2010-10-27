#include <algorithm>
#include <cerrno>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <vector>

#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

char esc_to_char(char* esc)
{
  if (strlen(esc) == 1) {
    // these are the single-character escapes

    switch (esc[0]) {
    // these escape sequences are just themselves
    case '?':
    case '"':
    case '\'':
    case '\\':
      return esc[0];

    // these escape sequences need to be translated
    case '0':  return '\0';
    case 'a':  return '\a';
    case 'b':  return '\b';
    case 'f':  return '\f';
    case 'n':  return '\n';
    case 'r':  return '\r';
    case 't':  return '\t';
    case 'v':  return '\v';
  
    // everything else is junk
    default:
      throw std::exception(); 
    }
  }
  else {
    unsigned long v;

    if (esc[0] == 'x') {
      // this is a hexadecimal escape
      v = strtoul(esc+1, NULL, 16);
    }
    else {
      // this is an octal escape
      v = strtoul(esc, NULL, 8);
    }

    if (errno) {
      // conversion failed
      throw std::exception();
    }

    return boost::numeric_cast<unsigned char>(v);
  }
}

void debruijn(unsigned int t,
              unsigned int p,
              const unsigned int k,
              const unsigned int n,
              unsigned int* a,
              boost::function<void (unsigned int*,unsigned int*)> callback)
{
  if (t > n) {
    // we want only necklaces, not pre-necklaces or Lyndon words
    if (n % p == 0) {
      callback(a+1, a+p+1);
    }
  }
  else {
    a[t] = a[t-p];

    debruijn(t+1, p, k, n, a, callback);
      
    for (unsigned int j = a[t-p]+1; j < k; ++j) {
      a[t] = j;
      debruijn(t+1, t, k, n, a, callback);
    }
  }
}

struct seq_printer {
  const std::vector<char>& _alpha;

  seq_printer(const std::vector<char>& alpha) : _alpha(alpha) {}

  void operator() (unsigned int* a, unsigned int* a_end) const {
    for (unsigned int* i = a; i < a_end; ++i) {
      std::cout << _alpha[*i];
    }
  }
};

const char* help_short()
{
  return
    "Usage: debruijn n a [b [c]]...\n"
    "Try `debruijn --help' for more information.";
}

const char* help_long()
{
  return
    "Usage: debruijn n a [b [c]]...\n"
    "Generates the lexicographically least de Bruijn sequence B(k,n), where\n"
    "k is the size of the alphabet and n is the sequence length. Arguments\n"
    "after the first are characters in the alphabet.\n"
    "Example: `debruijn 2 a b' gives the following output:\n"
    "\n"
    "aabba\n"
    "\n"
    "Note that all such sequences have length k^n, and hence the runtime of\n"
    "this program is O(k^n). You probably have neitehr the time to wait for\n"
    "nor enough space to store the output from any but small k and n.\n";
}

int main(int argc, char** argv)
{
  using namespace boost;
  using namespace std;

  //
  // Parse the arguments
  //
  
  switch (argc) {
  case 1:
    cerr << "Too few arguments!" << "\n"
         << help_short() << endl;
    return 1;
  
  case 2:
    if (!strcmp(argv[1], "-h")) {
      cerr << help_short() << endl;
      return 0;
    }
    else if (!strcmp(argv[1], "--help")) {
      cerr << help_long() << endl;
      return 0;
    }
    else {
      cerr << "Too few arguments!" << "\n"
           << help_short() << endl;
      return 1;
    }

  default:
    break;
  }

  // The maximal sequence length
  const uint N = lexical_cast<uint>(argv[1]);

  //
  // Get the alphabet from the command line
  //

  vector<char> alpha;

  for (uint i = 2; i < (uint) argc; ++i) {
    if (strlen(argv[i]) == 1) {
      // this is a printable literal
      alpha.push_back(argv[i][0]);
    }
    else if (argv[i][0] == '\\') {
      // this is an escape sequence, decode it
      alpha.push_back(esc_to_char(argv[i]+1));
    }
    else {
      cerr << '`' << argv[i] << "' is not a character"
           << help_short() << endl;
      return 1;
    }
  }

  //
  // Generate B(|A|,N), the lexicographically least de Bruijn sequence
  // for an alphabet of size |A| over sequences of length N.
  //
  
  unsigned int* a = new unsigned int[N+1];
  a[0] = 0;
  debruijn(1, 1, alpha.size(), N, a, seq_printer(alpha));
  if (N > 1) cout << alpha[0];
  cout << endl;

  delete[] a;
}
