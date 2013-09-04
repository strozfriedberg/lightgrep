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

#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "escape_translator.h"

void debruijn(uint32_t t,
              uint32_t p,
              const uint32_t k,
              const uint32_t n,
              uint32_t* a,
              std::function<void (uint32_t*, uint32_t*)> callback)
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

    for (uint32_t j = a[t-p]+1; j < k; ++j) {
      a[t] = j;
      debruijn(t+1, t, k, n, a, callback);
    }
  }
}

struct seq_printer {
  const std::vector<char>& _alpha;

  seq_printer(const std::vector<char>& alpha): _alpha(alpha) {}

  void operator() (uint32_t* a, uint32_t* a_end) const {
    for (uint32_t* i = a; i < a_end; ++i) {
      std::cout << _alpha[*i];
    }
  }
};

const char* help_short()
{
  return
    "Usage: debruijn n a[b[c]]...\n"
    "Try `debruijn --help' for more information.";
}

const char* help_long()
{
  return
    "Usage: debruijn n a[b[c]]...\n"
    "Generates the lexicographically least de Bruijn sequence B(k,n), where\n"
    "k is the size of the alphabet and n is the sequence length. Arguments\n"
    "after the first are characters in the alphabet.\n"
    "Example: `debruijn 2 ab' gives the following output:\n"
    "\n"
    "aabba\n"
    "\n"
    "Note that all such sequences have length k^n, and hence the runtime of\n"
    "this program is O(k^n). You probably have neither the time to wait for\n"
    "nor enough space to store the output from any but small k and n.\n";
}

int main(int argc, char** argv)
{
  //
  // Parse the arguments
  //

  switch (argc) {
  case 1:
    std::cerr << "Too few arguments!" << "\n"
              << help_short() << std::endl;
    return 1;

  case 2:
    if (!std::strcmp(argv[1], "-h")) {
      std::cerr << help_short() << std::endl;
      return 0;
    }
    else if (!std::strcmp(argv[1], "--help")) {
      std::cerr << help_long() << std::endl;
      return 0;
    }
    else {
      std::cerr << "Too few arguments!" << "\n"
                << help_short() << std::endl;
      return 1;
    }

  default:
    break;
  }

  // The maximal sequence length
  const uint32_t N = boost::lexical_cast<uint32_t>(argv[1]);

  //
  // Get the alphabet from the command line
  //

  std::vector<char> alpha;
  escape_translator(
    argv[2], argv[2]+std::strlen(argv[2]), std::back_inserter(alpha)
  );

  //
  // Generate B(|A|,N), the lexicographically least de Bruijn sequence
  // for an alphabet of size |A| over sequences of length N.
  //

  std::unique_ptr<uint32_t[]> a(new uint32_t[N+1]);
  a[0] = 0;
  debruijn(1, 1, alpha.size(), N, a.get(), seq_printer(alpha));
  if (N > 1) {
    std::cout << alpha[0];
  }
  std::cout << std::endl;

  return 0;
}
