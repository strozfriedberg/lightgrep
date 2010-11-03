#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>

#include "alphabet_parser.h"
#include "quantifier_parser.h"

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

std::string instantiate(const std::string& form,
                        const std::vector<std::string>& atoms,
                        const std::vector<unsigned int>& aslots,
                        const std::vector<std::string>& quant,
                        const std::vector<unsigned int>& qslots)
{
  using namespace std;

  string instance;

  vector<unsigned int>::const_iterator a(aslots.begin());
  vector<unsigned int>::const_iterator q(qslots.begin());

  for (string::const_iterator f(form.begin()); f != form.end(); ++f) {
    switch (*f) {
    case 'a':
      instance += atoms[*(a++)];
      break;

    case 'q':
      instance += quant[*(q++)];
      break;

    default:
      instance += *f;
      break;
    }
  }

  return instance;
}

void make_slots(const std::string& form,
                const bool have_quant,
                std::vector<unsigned int>& aslots,
                std::vector<unsigned int>& qslots) {
  for (std::string::const_iterator i(form.begin()); i != form.end(); ++i) {
    switch (*i) {
    case 'a':
      aslots.push_back(0);
      break;

    case 'q':
      if (!have_quant) {
        std::cerr << "No quantifiers specified, but saw pattern: " << form
             << std::endl;
        exit(1);
      }
      qslots.push_back(0);
      break;

    default:
      // skip chars which are neither atoms nor quantifiers;
      // these are already concrete
      break;
    }
  }
}

bool skip(const std::vector<unsigned int>& aslots,
          const unsigned int asize) {
  using namespace std;

  vector<unsigned int>::const_iterator i = aslots.begin();
  vector<unsigned int>::const_iterator j;
  for (unsigned int x = 0; x < asize; ++x) {
    j = find(aslots.begin(), aslots.end(), x);
    if (j < i) return true;
    i = j;
  }

  return false;
}

bool increment_vector(std::vector<unsigned int>& v, const unsigned int vlim) {
  for (std::vector<unsigned int>::iterator i(v.begin()); i != v.end(); ++i) {
    // check whether incrementing pushed us past the digit limit
    if (++(*i) < vlim) return true;
    // otherwise zero and carry
    *i = 0;
  }
  return false;
}

bool next_instance(std::vector<unsigned int>& aslots,
                   const unsigned int asize,
                   std::vector<unsigned int>& qslots,
                   const unsigned int qsize)
{
  return increment_vector(aslots, asize) || increment_vector(qslots, qsize);
}

bool next_instance_noniso(std::vector<unsigned int>& aslots,
                          const unsigned int asize,
                          std::vector<unsigned int>& qslots,
                          const unsigned int qsize)
{
  // FIXME: There should be a way to iterate over these directly,
  // without skipping.
  while (increment_vector(aslots, asize)) {
    if (!skip(aslots, asize)) return true;
  }

  return increment_vector(qslots, qsize);
}

const char* help_short() {
  return
    "Usage: inst a[b[c]]... [q [q [q]]]...\n"
    "Try `inst --help' for more information.";
}

const char* help_long() {
  return
    "Usage: inst a[b[c]]... [q [q [q]]]...\n"
    "Instantiates regular expression forms with the given alphabet.\n"
    "Regex forms are read from standard input, one per line.\n"
    "Example: `echo aq | inst x +' gives the following output:\n"
    "\n"
    "x+\n"
    ".+\n"
    "[x]+\n"
    "[^x]+\n"
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

  if (argc < 2) {
    cerr << "too few arguments!\n"
         << help_short() << endl;
    return 1;
  }

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

  //
  // Get the alphabet from the command line
  //

  vector<string> alpha;
  alphabet_parser(argv[1], argv[1]+strlen(argv[1]), back_inserter(alpha));

  //
  // Get the quantifiers from the command line
  // 

  vector<string> quant;
  for (unsigned int i = 2; i < (unsigned int) argc; ++i) {
    quantifier_parser(argv[i], argv[i]+strlen(argv[i]), back_inserter(quant));
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
    // in the (sorted) range
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
    do {
      string s(join(v, ""));
      atoms.push_back(op_class(s));
      atoms.push_back(op_negclass(s));
    } while (next_permutation(v.begin(), v.end()));
  }

  //
  // Concretize forms
  //

  bool (* const next)(vector<unsigned int>&, const unsigned int,
                      vector<unsigned int>&, const unsigned int) =
    &next_instance;

  string form;
  while (cin >> form) {

    vector<unsigned int> aslots;
    vector<unsigned int> qslots;
  
    make_slots(form, !quant.empty(), aslots, qslots);

    const unsigned int asize = aslots.size();
    const unsigned int qsize = qslots.size();

    // Iterate through all instantiations of the form
    do {
      cout << instantiate(form, atoms, aslots, quant, qslots) << "\n";
    } while (next(aslots, asize, qslots, qsize));
  }
}
