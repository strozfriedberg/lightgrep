#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

std::string op_group(const std::string& s) { return '(' + s + ')'; }
std::string op_quant(const std::string& s) { return s + 'q'; }

std::string op_conj(const std::string& l, const std::string& r) {
  return l + r;
}

std::string op_disj(const std::string& l, const std::string& r) {
  return l + '|' + r;
}

/*
struct set_contains : public std::unary_function<const std::string&, bool>
{
  const std::set<std::string>& _set;

  set_contains(const std::set<std::string>& set) : _set(set) {}
    
  bool operator()(const std::string& s) {
    return _set.find(s) != _set.end();
  }
};
*/

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

int main(int argc, char** argv)
{
  using namespace boost;
  using namespace std;

  typedef unsigned int uint;

  typedef vector<string>::iterator vsit;
  typedef vector<string>::const_iterator cvsit;

  typedef set<string>::iterator ssit;
  typedef set<string>::const_iterator cssit;

  const uint N = lexical_cast<uint>(argv[1]);

  set<string> oform;
  set<string> cform;
  vector<string> nform;

  vector<string> csing(1, "a");
  vector<string> nsing;

  // Print base generation
  copy(csing.begin(), csing.end(), ostream_iterator<string>(cout, "\n"));
  cout << endl;

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

//    bind(not_equal_to<ssit>(), oform.end(), _1);

//    set<string>::const_iterator (set<string>::*fn)(const string&) = &set<string>::find;
//    bind(fn, cref(oform), _1);
  
//      bind<set<string>::const_iterator>(&set<string>::find, cref(oform), *_1);
     
//    bind(&set<string>::find, cref(oform), *_1); 

//    remove_if(ncomb.begin(), ncomb.end(), bind(not_equal_to<ssit>(), oform.end(), bind(&set<string>::find, cref(oform), *_1)));

//    remove_if(ncomb.begin(), ncomb.end(), set_contains(oform));

    set<string> tmp;
    set_difference(ncomb.begin(), ncomb.end(), oform.begin(), oform.end(),
                   inserter(tmp, tmp.begin()));
    ncomb.clear();
    swap(ncomb, tmp);

    //
    // Cleanup
    //
    
    // make all current forms old
    copy(cform.begin(), cform.end(), inserter(oform, oform.begin()));

    // make all new forms current
    cform.clear();
    copy(nform.begin(), nform.end(), inserter(cform, cform.begin()));

    // clear all new forms
    nform.clear();

    // make all current singular forms old
    copy(csing.begin(), csing.end(), inserter(oform, oform.begin()));

    // make all new singular forms current
    csing.clear();
    swap(csing, nsing);

    // make all new concatenations current
    copy(ncomb.begin(), ncomb.end(), inserter(cform, cform.begin()));

    // clear new concatenations
    ncomb.clear();

    //
    // Output
    //
    copy(csing.begin(), csing.end(), ostream_iterator<string>(cout, "\n"));
    copy(cform.begin(), cform.end(), ostream_iterator<string>(cout, "\n"));
//    cout << endl;
  }
 
  // print all generated forms
//  copy(oform.begin(), oform.end(), ostream_iterator<string>(cout, "\n"));
//  copy(csing.begin(), csing.end(), ostream_iterator<string>(cout, "\n"));
//  copy(cform.begin(), cform.end(), ostream_iterator<string>(cout, "\n"));
}

