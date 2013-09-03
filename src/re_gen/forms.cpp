#include <algorithm>
#include <cstring>
#include <functional>
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
  using namespace boost;
  using namespace std;

  typedef unsigned int uint;

  //
  // Parse the arguments
  //

  if (argc < 2) {
    cerr << "unspecified number of stages!" << "\n"
         << help_short() << endl;
    return 1;
  }

  if (argc > 2) {
    cerr << "too many arguments!" << "\n"
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

  uint u;
  try {
    u = lexical_cast<uint>(argv[1]);
  }
  catch (bad_lexical_cast &) {
    cerr << "`" << argv[1]
         << "' isn't a natural number we've heard of!" << "\n"
         << help_short() << endl;
    return 1;
  }

  if (u > 3) {
    // If the number of stages is too high, it's likely that the program
    // will exhaust the machine's RAM rather quickly. Prompt the user for
    // confirmation of large n.
    cerr << "Number of stages = " << argv[1] << ". Are you sure? [y/N]" << endl;
    char reply;
    cin >> reply;
    if (reply != 'y') {
      cerr << "Aborting." << endl;
      return 0;
    }
  }

  //
  // Start generating forms
  //

  // N is the number of rounds to run
  const uint N = u;

  set<string> oform;
  set<string> cform;
  vector<string> nform;

  vector<string> csing(1, "a");
  vector<string> nsing;

  std::set<std::string> tmp;

  // Print base generation
  copy(csing.begin(), csing.end(), ostream_iterator<string>(cout, "\n"));

  for (uint i = 0; i < N; ++i) {
    //
    // Build new regex forms
    //

    // Quantify all current singular expressions.
    // Quantification creates new forms, these go to the new list.
    transform(csing.begin(), csing.end(), back_inserter(nform), op_quant);    

    // Group all current expressions.
    // Grouping creates new singular forms, these go to the new singular list.
    transform(cform.begin(), cform.end(), back_inserter(nsing), op_group);
    transform(csing.begin(), csing.end(), back_inserter(nsing), op_group);

    // Alternate and concatenate all pairs of expressions which have not
    // already been alternated or concatenated. I.e., we want the following
    // Cartesian products: old x cur, cur x old, cur x cur.
    set<string> ncomb;

    // oform x cform
    cartesian_prod(oform.begin(), oform.end(), cform.begin(), cform.end(),
                   inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(oform.begin(), oform.end(), cform.begin(), cform.end(),
                   inserter(ncomb, ncomb.begin()), op_disj);

    // cform x oform
    cartesian_prod(cform.begin(), cform.end(), oform.begin(), oform.end(),
                   inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(cform.begin(), cform.end(), oform.begin(), oform.end(),
                   inserter(ncomb, ncomb.begin()), op_disj);

    // cform x cform
    cartesian_prod(cform.begin(), cform.end(), cform.begin(), cform.end(),
                   inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(cform.begin(), cform.end(), cform.begin(), cform.end(),
                   inserter(ncomb, ncomb.begin()), op_disj);

    // cform x csing
    cartesian_prod(cform.begin(), cform.end(), csing.begin(), csing.end(),
                   inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(cform.begin(), cform.end(), csing.begin(), csing.end(),
                   inserter(ncomb, ncomb.begin()), op_disj);

    // csing x csing
    cartesian_prod(csing.begin(), csing.end(), csing.begin(), csing.end(),
                   inserter(ncomb, ncomb.begin()), op_conj);

    cartesian_prod(csing.begin(), csing.end(), csing.begin(), csing.end(),
                   inserter(ncomb, ncomb.begin()), op_disj);

    // kill duplicates
    tmp.clear();
    set_difference(ncomb.begin(), ncomb.end(), oform.begin(), oform.end(),
                   inserter(tmp, tmp.begin()));
    ncomb.clear();
    swap(ncomb, tmp);

    //
    // Cleanup
    //
    
    // move all current forms to old
    copy(cform.begin(), cform.end(), inserter(oform, oform.begin()));

    // move all new forms to current
    cform.insert(nform.begin(), nform.end());
    nform.clear();

    // move all current singular forms to old
    copy(csing.begin(), csing.end(), inserter(oform, oform.begin()));

    // make all new singular forms current
    swap(nsing, csing);
    nsing.clear();

    // move all new concatenations to current
    copy(ncomb.begin(), ncomb.end(), inserter(cform, cform.begin()));
    ncomb.clear();

    //
    // Output
    //
    copy(csing.begin(), csing.end(), ostream_iterator<string>(cout, "\n"));
    copy(cform.begin(), cform.end(), ostream_iterator<string>(cout, "\n"));
  }
}
