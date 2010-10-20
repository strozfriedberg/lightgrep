#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>

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

std::string op_class(const std::string& s) { return '[' + s + ']'; }
std::string op_negclass(const std::string& s) { return "[^" + s + ']'; }

std::vector<std::string> bits_to_vector(unsigned int bits,
                                        const std::vector<std::string>& alpha) {
  using namespace std;
  
  vector<string> v;

  for (vector<string>::const_iterator i(alpha.begin()); i != alpha.end(); ++i) {
    if (bits & (1 << (i-alpha.begin()))) v.push_back(*i);
  } 
  
  return v;
}

std::string instantiate(const std::vector<int>& inst,
                        const std::string& form,
                        const std::vector<std::string>& atoms,
                        const std::vector<std::string>& quant)
{
  using namespace std;

  string instance;

  vector<int>::const_iterator i(inst.begin());
  for (string::const_iterator f(form.begin()); f != form.end(); ++f) {
    switch (*f) {
    case 'a':
      instance += atoms[*i];
      ++i;
      break;

    case 'q':
      instance += quant[-(*i+1)];
      ++i;
      break;

    default:
      instance += *f;
      break;
    }
  }

  return instance;
}

bool next_instance(std::vector<int>& inst,
                   const std::vector<std::string>& atoms,
                   const std::vector<std::string>& quant)
{
  using namespace std;

  for (vector<int>::iterator i(inst.begin()); i != inst.end(); ++i) {
    // increment this position
    if (*i < 0) {
      // remember that quants are negative
      --(*i);

      // check whether incrementing pushed us off the end of the quant list
      if ((unsigned int)(-(*i+1)) != quant.size()) return true;

      // otherwise zero and carry (remember that quant offset is -(x+1))
      // so here, "zero" is actually -1.
      *i = -1;
    }
    else {
      ++(*i);

      // check whether incrementing pushed us off the end of the atoms list
      if ((unsigned int)(*i) != atoms.size()) return true;

      // otherwise zero and carry
      *i = 0;
    }
  }

  return false;
}

char* help_short() {
  return
    "Usage: inst a [b [c]]...\n"
    "Try `inst --help' for more information.";
}

char* help_long() {
  return
    "Usage: inst a [b [c]]...\n"
    "Instantiates regular expression forms with the given alphabet.\n"
    "Regex forms are read from standard input, one per line.\n"
    "Example: `echo aq | inst x' gives the following (partial) output:\n"
    "\n"
    "x*\n"
    ".*\n"
    "x+\n"
    ".+\n"
    "x?\n"
    ".?\n"
    "\n"
    "Note that the (optimal!) runtime for producing all instantiations for a\n"
    "given regex form is O(m^n), where m is the size of the alphabet and n is\n"
    "the number of atomic variables (`a') in the form.\n";
}

int main(int argc, char** argv)
{
  using namespace boost::algorithm;
  using namespace std;

  typedef unsigned int uint;

  //
  // Parse the arguments
  //

  // NB: No arguments means that we're using the empty alphabet. That's
  // ok, we just don't need to check for the help options in this case.

  if (argc > 1) {
    if (!strcmp(argv[1], "-h")) {
      // -h prints the short help
      cerr << help_short() << endl;
      return 0;
    } 
    else if (!strcmp(argv[1], "--help")) {
      // --help prints the long help
      cerr << help_long() << endl;
      return 0;
    }   
  }

  //
  // Get the alphabet from the command line
  //
  const vector<string> alpha(argv+1, argv+argc);

  //
  // Build all the quantifiers
  //

  const char* q[] = { "*", "+", "?", "*?", "+?", "??" };
  vector<string> quant(q, q+sizeof(q)/sizeof(q[0]));

  // Add {n}, {n}? quantifiers from 1 to 3
  for (uint n = 1; n < 4; ++n) {
    quant.push_back(op_nquant(n));
    quant.push_back(op_nquant(n) + '?');
  }

  // Add {n,}, {n,}? quantifiers from 0 to 3
  for (uint n = 0; n < 4; ++n) {
    quant.push_back(op_nxquant(n));
    quant.push_back(op_nxquant(n) + '?');
  }

  // Add {n,m}, {n,m}? quantifiers from {0,1} to {3,3}
  for (uint n = 0; n < 4; ++n) {
    for (uint m = n; m < 4; ++m) {
      // Don't generate useless {0,0}
      if ((n == m) && (m == 0)) continue;

      quant.push_back(op_nmquant(n, m));
      quant.push_back(op_nmquant(n, m) + '?');
    }
  }

  //
  // Build all the atoms
  //

  // Each character in the alphabet is an atom
  vector<string> atoms(alpha.begin(), alpha.end());
  
  // Dot is an atom
  atoms.push_back(".");

  // Each ordering of each nonempty subset of the alphabet defines a
  // character class and a negated character class.
  const uint abitsmax = 1 << alpha.size();
  
  for (uint abits = 1; abits < abitsmax; ++abits) {
    // get the base character class corresponding to this bit vector
    vector<string> v(bits_to_vector(abits, alpha));

    // try all the (internal) insertion points for the range marker
    const uint rbitsmax = 1 << (v.size()-1);

    for (uint rbits = 1; rbits < rbitsmax; ++rbits) {
      // skip rbits which have adjacent range markers; [a-b-c] is illegal
      // X & (X >> 1) > 0 iff X has two consecutive 1s somewhere
      if (rbits & (rbits >> 1)) continue;

      string r;

      // put range markers in the locations indicated by rbits
      for (vector<string>::const_iterator i(v.begin()); i != v.end(); ++i) {
        r += *i;
        if (rbits & (1 << (i-v.begin()))) r += '-';
      }

      atoms.push_back(op_class(r));
      atoms.push_back(op_negclass(r));
    }

    // try all the permutations of the elements of the character class
    while (next_permutation(v.begin(), v.end())) {
      string s(join(v, ""));

      atoms.push_back(op_class(s));
      atoms.push_back(op_negclass(s));
    }
  }

  //
  // Concretize forms
  //

  string form;
  while (cin >> form) {
    // Build the instance vector for the atoms and quantifiers. Elements
    // which are nonnegative indicate indices into the atom vector, elements
    // which are negative indicate indices into the quantifier vector. (For
    // quantifiers, x -> -(x+1) is the mapping to offsets in the quantifier
    // vector. Yes, this is fiddly, but it's a small program.)
    vector<int> concr;
    
    for (string::const_iterator i(form.begin()); i != form.end(); ++i) {
      switch (*i) {
      case 'a':
        concr.push_back(0);
        break;

      case 'q':
        concr.push_back(-1);
        break;

      default:
        // skip chars which are neither atoms nor quantifiers;
        // these are already concrete
        break;
      }
    }

    // Iterate through all instantiations of the form
    do {
      cout << instantiate(concr, form, atoms, quant) << "\n";
    } while (next_instance(concr, atoms, quant));
  }
}
