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
#include <cstring>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

std::string op_group(const std::string& s) { return '(' + s + ')'; }
std::string op_quant(const std::string& s) { return s + 'q'; }

std::string op_conj(const std::string& l, const std::string& r) {
  return l + r;
}

std::string op_disj(const std::string& l, const std::string& r) {
  return l + '|' + r;
}

template<class InputIteratorL, class InputIteratorR,
         class OutputIterator, class BinaryOperator>
  void cartesian_prod(InputIteratorL lbeg, InputIteratorL lend,
                      InputIteratorR rbeg, InputIteratorR rend,
                      OutputIterator result, BinaryOperator op)
{
  for ( ; lbeg != lend; ++lbeg) {
    for (InputIteratorR rbeg_copy(rbeg); rbeg_copy != rend; ++rbeg_copy) {
      *result++ = op(*lbeg, *rbeg_copy);
    }
  }
}

const char* help_short() {
  return
    "Usage: forms n\n"
    "Try `forms --help' for more information.";
}

const char* help_long() {
  return
    "Usage: forms n\n"
    "Creates regular expression forms in n stages.\n"
    "Example: `forms 1' gives the following output:\n"
    "\n"
    "a\n"
    "(a)\n"
    "aa\n"
    "aq\n"
    "a|a\n"
    "\n"
    "where `a' is a variable ranging over atoms, and `q' is a variable\n"
    "ranging over quantifiers. This output is intended to be fed to inst,\n"
    "which will instantiate each form to a concrete regular expression.\n"
    "\n"
    "Note that the algorightm runs in O(n^(2n)), where n is the number of\n"
    "stages. This is not because we're being inefficient, but because we're\n"
    "generating a finite fragment of an infinite language very rapidly. You\n"
    "might not have enough RAM to run with n = 4. There might not be enough\n"
    "RAM in the universe to run with n = 10.\n";
}

int main(int argc, char** argv)
{
  //
  // Parse the arguments
  //

  if (argc < 2) {
    std::cerr << "unspecified number of stages!" << "\n"
              << help_short() << std::endl;
    return 1;
  }

  if (argc > 2) {
    std::cerr << "too many arguments!" << "\n"
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

  uint32_t u;
  try {
    u = boost::lexical_cast<uint32_t>(argv[1]);
  }
  catch (boost::bad_lexical_cast &) {
    std::cerr << "`" << argv[1]
              << "' isn't a natural number we've heard of!" << "\n"
              << help_short() << std::endl;
    return 1;
  }

  if (u > 3) {
    // If the number of stages is too high, it's likely that the program
    // will exhaust the machine's RAM rather quickly. Prompt the user for
    // confirmation of large n.
    std::cerr << "Number of stages = " << argv[1]
              << ". Are you sure? [y/N]" << std::endl;
    char reply;
    std::cin >> reply;
    if (reply != 'y') {
      std::cerr << "Aborting." << std::endl;
      return 0;
    }
  }

  //
  // Start generating forms
  //

  // N is the number of rounds to run
  const uint32_t N = u;

  std::set<std::string> oform;
  std::set<std::string> cform;
  std::vector<std::string> nform;

  std::vector<std::string> csing{"a"};
  std::vector<std::string> nsing;

  std::set<std::string> tmp;

  // Print base generation
  std::copy(
    csing.begin(), csing.end(),
    std::ostream_iterator<std::string>(std::cout, "\n")
  );

  for (uint32_t i = 0; i < N; ++i) {
    //
    // Build new regex forms
    //

    // Quantify all current singular expressions.
    // Quantification creates new forms, these go to the new list.
    std::transform(
      csing.begin(), csing.end(), std::back_inserter(nform), op_quant
    );

    // Group all current expressions.
    std::transform(
      cform.begin(), cform.end(), std::back_inserter(nsing), op_group
    );

    // Grouping creates new singular forms, these go to the new singular list.
    std::transform(
      csing.begin(), csing.end(), std::back_inserter(nsing), op_group
    );

    // Alternate and concatenate all pairs of expressions which have not
    // already been alternated or concatenated. I.e., we want the following
    // Cartesian products: old x cur, cur x old, cur x cur.
    std::set<std::string> ncomb;

    // oform x cform
    cartesian_prod(oform.begin(), oform.end(), cform.begin(), cform.end(),
                   std::inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(oform.begin(), oform.end(), cform.begin(), cform.end(),
                   std::inserter(ncomb, ncomb.begin()), op_disj);

    // cform x oform
    cartesian_prod(cform.begin(), cform.end(), oform.begin(), oform.end(),
                   std::inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(cform.begin(), cform.end(), oform.begin(), oform.end(),
                   std::inserter(ncomb, ncomb.begin()), op_disj);

    // cform x cform
    cartesian_prod(cform.begin(), cform.end(), cform.begin(), cform.end(),
                   std::inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(cform.begin(), cform.end(), cform.begin(), cform.end(),
                   std::inserter(ncomb, ncomb.begin()), op_disj);

    // cform x csing
    cartesian_prod(cform.begin(), cform.end(), csing.begin(), csing.end(),
                   std::inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(cform.begin(), cform.end(), csing.begin(), csing.end(),
                   std::inserter(ncomb, ncomb.begin()), op_disj);

    // csing x csing
    cartesian_prod(csing.begin(), csing.end(), csing.begin(), csing.end(),
                   std::inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(csing.begin(), csing.end(), csing.begin(), csing.end(),
                   std::inserter(ncomb, ncomb.begin()), op_disj);

    // kill duplicates
    tmp.clear();
    std::set_difference(
      ncomb.begin(), ncomb.end(), oform.begin(), oform.end(),
      std::inserter(tmp, tmp.begin())
    );
    ncomb.clear();
    std::swap(ncomb, tmp);

    //
    // Cleanup
    //

    // move all current forms to old
    std::copy(cform.begin(), cform.end(), std::inserter(oform, oform.begin()));

    // move all new forms to current
    cform.insert(nform.begin(), nform.end());
    nform.clear();

    // move all current singular forms to old
    std::copy(csing.begin(), csing.end(), std::inserter(oform, oform.begin()));

    // make all new singular forms current
    std::swap(nsing, csing);
    nsing.clear();

    // move all new concatenations to current
    std::copy(ncomb.begin(), ncomb.end(), std::inserter(cform, cform.begin()));
    ncomb.clear();

    //
    // Output
    //
    std::copy(
      csing.begin(), csing.end(),
      std::ostream_iterator<std::string>(std::cout, "\n")
    );

    std::copy(
      cform.begin(), cform.end(),
      std::ostream_iterator<std::string>(std::cout, "\n")
    );
  }
}
