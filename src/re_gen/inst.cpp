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

#include <algorithm>
#include <cstdlib>
#include <functional>
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
  std::vector<std::string> v;
  std::vector<std::string>::const_iterator i(alpha.begin());
  for ( ; i != alpha.end(); ++i) {
    if (bits & (1 << (i-alpha.begin()))) {
      v.push_back(*i);
    }
  }

  return v;
}

std::string instantiate(const std::string& form,
                        const std::vector<std::string>& atoms,
                        const std::vector<unsigned int>& aslots,
                        const std::vector<std::string>& quant,
                        const std::vector<unsigned int>& qslots)
{
  std::string instance;

  std::vector<unsigned int>::const_iterator a(aslots.begin());
  std::vector<unsigned int>::const_iterator q(qslots.begin());

  for (std::string::value_type c : form) {
    switch (c) {
    case 'a':
      instance += atoms[*(a++)];
      break;

    case 'q':
      instance += quant[*(q++)];
      break;

    default:
      instance += c;
      break;
    }
  }

  return instance;
}

void make_slots(const std::string& form,
                const bool have_quant,
                std::vector<unsigned int>& aslots,
                std::vector<unsigned int>& qslots) {
  for (std::string::value_type c : form) {
    switch (c) {
    case 'a':
      aslots.push_back(0);
      break;

    case 'q':
      if (!have_quant) {
        std::cerr << "No quantifiers specified, but saw pattern: " << form
                  << std::endl;
        std::exit(1);
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

bool increment_vector(std::vector<unsigned int>& v, const unsigned int vlim) {
  for (std::vector<unsigned int>::iterator i(v.begin()); i != v.end(); ++i) {
    // check whether incrementing pushed us past the digit limit
    if (++(*i) < vlim) return true;
    // otherwise zero and carry
    *i = 0;
  }
  return false;
}

struct next_instance {
  bool operator() (std::vector<unsigned int>& aslots,
                   const unsigned int asize,
                   std::vector<unsigned int>& qslots,
                   const unsigned int qsize)
  {
    return increment_vector(aslots, asize) || increment_vector(qslots, qsize);
  }
};

bool skip(const std::vector<unsigned int>& aslots,
          const unsigned int asize) {
  std::vector<unsigned int>::const_iterator i(aslots.begin());
  std::vector<unsigned int>::const_iterator j;
  for (unsigned int x = 0; x < asize; ++x) {
    j = std::find(aslots.begin(), aslots.end(), x);
    if (j < i) {
      return true;
    }
    i = j;
  }

  return false;
}

struct next_instance_iso {
  const unsigned int _alphasize;

  next_instance_iso(const unsigned int alphasize): _alphasize(alphasize) {}

  bool operator() (std::vector<unsigned int>& aslots,
                   const unsigned int asize,
                   std::vector<unsigned int>& qslots,
                   const unsigned int qsize)
  {
    if (increment_vector(qslots, qsize)) {
      return true;
    }

    // FIXME: There should be a way to iterate over these directly,
    // without skipping.
    while (increment_vector(aslots, asize)) {
      // The alphabet is the first alphasize indices; we care about
      // generating only the lexicographically least representative
      // of each isomorphism equivalence class over the alphabet.
      if (!skip(aslots, _alphasize)) {
        return true;
      }
    }

    return false;
  }
};

void make_character_classes(const std::vector<std::string>& alpha,
                            std::vector<std::string>& atoms)
{
// TODO: Don't create isomorphic character classes...

  // Each ordering of each nonempty subset of the alphabet defines a
  // character class and a negated character class.
  const uint32_t abitsmax = 1 << alpha.size();

  for (uint32_t abits = 1; abits < abitsmax; ++abits) {
    // get the base character class corresponding to this bit vector
    std::vector<std::string> v(bits_to_vector(abits, alpha));

    // try all the (internal) insertion points for the range marker
    // in the (sorted) range
    const uint32_t rbitsmax = 1 << (v.size()-1);

    for (uint32_t rbits = 1; rbits < rbitsmax; ++rbits) {
      // skip rbits which have adjacent range markers; [a-b-c] is illegal
      // X & (X >> 1) > 0 iff X has two consecutive 1s somewhere
      if (rbits & (rbits >> 1)) {
        continue;
      }

      std::string r;

      // put range markers in the locations indicated by rbits
      std::vector<std::string>::const_iterator i(v.begin());
      for ( ; i != v.end(); ++i) {
        r += *i;
        if (rbits & (1 << (i-v.begin()))) r += '-';
      }

      atoms.push_back(op_class(r));
      atoms.push_back(op_negclass(r));
    }

    // try all the permutations of the elements of the character class
    do {
      std::string s(boost::algorithm::join(v, ""));
      atoms.push_back(op_class(s));
      atoms.push_back(op_negclass(s));
    } while (next_permutation(v.begin(), v.end()));
  }
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
  //
  // Parse the arguments
  //

  if (argc < 2) {
    std::cerr << "too few arguments!\n"
              << help_short() << std::endl;
    return 1;
  }

  if (!std::strcmp(argv[1], "-h")) {
    // -h prints the short help
    std::cerr << help_short() << std::endl;
    return 0;
  }
  else if (!std::strcmp(argv[1], "--help")) {
    // --help prints the long help
    std::cerr << help_long() << std::endl;
    return 0;
  }

  //
  // Get the alphabet from the command line
  //

  std::vector<std::string> alpha;
  alphabet_parser(
    argv[1], argv[1]+std::strlen(argv[1]), std::back_inserter(alpha)
  );

  //
  // Get the quantifiers from the command line
  //

  std::vector<std::string> quant;
  for (unsigned int i = 2; i < (unsigned int) argc; ++i) {
    quantifier_parser(
      argv[i], argv[i]+std::strlen(argv[i]), std::back_inserter(quant)
    );
  }

  //
  // Build all the atoms
  //

  // Each character in the alphabet is an atom
  std::vector<std::string> atoms(alpha.begin(), alpha.end());

  // Dot is an atom
  atoms.push_back(".");

  // Build the character classes
  make_character_classes(atoms, alpha);

  //
  // Concretize forms
  //

  const std::function<
    bool (std::vector<unsigned int>&, const unsigned int,
          std::vector<unsigned int>&, const unsigned int)> next =
    next_instance_iso(alpha.size());

  std::string form;
  while (std::cin >> form) {
    std::vector<unsigned int> aslots;
    std::vector<unsigned int> qslots;

    make_slots(form, !quant.empty(), aslots, qslots);

    const unsigned int asize = atoms.size();
    const unsigned int qsize = quant.size();

    // Iterate through all instantiations of the form
    do {
      std::cout << instantiate(form, atoms, aslots, quant, qslots) << "\n";
    } while (next(aslots, asize, qslots, qsize));
  }

  return 0;
}
