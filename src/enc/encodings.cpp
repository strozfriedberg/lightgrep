/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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

#include "basic.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <cstring>
#include <vector>

#include <unicode/ucnv.h>

void throw_on_error(UErrorCode err) {
  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("ICU error: " << u_errorName(err));
  }
}

int main(int, char**) {
  // print copyright notice, ifdef guards, open extern "C" block
  std::cout <<
R"(// Copyright 2011-2012, Lightbox Technologies, Inc. All Rights Reserved.

#ifndef LIGHTGREP_C_ENCODINGS_H_
#define LIGHTGREP_C_ENCODINGS_H_

#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

)";

  // Preference ordering for standards, to resolve name conficts
  //
  // UTR22 > IANA > MIME > IBM > WINDOWS > JAVA > ""
  //
  const std::vector<std::string> standards{
    "UTR22", "IANA", "MIME", "IBM", "WINDOWS", "JAVA", ""
  };

  // Encodings to skip
  const std::set<std::string> skip{
    // skip these because they have BOMs
    "UTF-16",
    "UTF-16,version=1",
    "UTF-16,version=2",
    "UTF-16LE,version=1",
    "UTF-16BE,version=1",
    "UTF-32",
    // skip these because they have system-dependent behavior
    "UTF16_OppositeEndian",
    "UTF16_PlatformEndian",
    "UTF32_OppositeEndian",
    "UTF32_PlatformEndian",
    // skip these because we can't handle stateful encodings yet
    "BOCU-1",
    "HZ",
    "IMAP-mailbox-name",
    "ISCII,version=0",
    "ISCII,version=1",
    "ISCII,version=2",
    "ISCII,version=3",
    "ISCII,version=4",
    "ISCII,version=5",
    "ISCII,version=6",
    "ISCII,version=7",
    "ISCII,version=8",
    "ISO_2022,locale=ja,version=0",
    "ISO_2022,locale=ja,version=1",
    "ISO_2022,locale=ja,version=2",
    "ISO_2022,locale=ja,version=3",
    "ISO_2022,locale=ja,version=4",
    "ISO_2022,locale=ko,version=0",
    "ISO_2022,locale=ko,version=1",
    "ISO_2022,locale=zh,version=0",
    "ISO_2022,locale=zh,version=1",
    "ISO_2022,locale=zh,version=2",
    "LMBCS-1",
    "SCSU",
    "UTF-7",
    "ibm-930_P120-1999",
    "ibm-933_P110-1995",
    "ibm-935_P110-1999",
    "ibm-937_P110-1999",
    "ibm-939_P120-1999",
    "ibm-1364_P110-2007",
    "ibm-1371_P100-1999",
    "ibm-1388_P103-2001",
    "ibm-1390_P110-2003",
    "ibm-1399_P110-2003",
    "ibm-16684_P110-2003",
    "x11-compound-text"
  };

  // Encodings to add
  const std::vector<std::string> add{};

  std::vector<std::string> canonical;
  std::map<std::string,uint32_t> idmap;
  size_t longest = 0, longest_canonical = 0;

  UErrorCode err = U_ZERO_ERROR;

  const int32_t clen = ucnv_countAvailable();
  for (int32_t i = 0; i < clen; ++i) {
    // get the canonical name for the ith encoding
    const char* cname = ucnv_getAvailableName(i);

    // skip encodings we want to omit
    if (skip.find(cname) != skip.end()) {
      continue;
    }

    canonical.emplace_back(cname);

    const int32_t alen = ucnv_countAliases(cname, &err);
    throw_on_error(err);

    longest_canonical = std::max(longest_canonical, strlen(cname));
    longest = std::max(longest, longest_canonical);

    for (int32_t j = 0; j < alen; ++j) {
      // get the jth alias for this encoding
      const char* aname = ucnv_getAlias(cname, j, &err);
      throw_on_error(err);

      // add this alias if not already present
      auto x = idmap.insert({aname, canonical.size()-1});
      if (x.second) {
        longest = std::max(longest, strlen(aname));
      }
      else {
        // check which standards define the old and new aliases
        for (const std::string& std : standards) {
          const char* sname = std.c_str();

          const char* olds = ucnv_getStandardName(x.first->first.c_str(), sname, &err);
          throw_on_error(err);

          const char* news = ucnv_getStandardName(aname, sname, &err);
          throw_on_error(err);

          if (olds) {
            // olds exists in std, keep it
            break;
          }
          else if (news) {
            // olds does not exist in std, but news does, replace olds
            idmap[aname] = i;
            break;
          }
        }
      }
    }
  }

  // add extra encodings to the id and canonical maps
  for (const std::string& extra : add) {
    canonical.push_back(extra);
    auto x = idmap.insert({extra, canonical.size()-1});
    if (!x.second) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(
        "Extra encoding '" << extra << "' conficts with existing encoding!"
      );
    }
  }

  // print the name to encoding id map
  std::cout <<
R"(static const LG_TRANS LG_ENCODINGS[] = {)";

  auto itr = idmap.begin();
  const auto end = idmap.end();

  if (itr != end) {
    longest += 3;

    std::string n = '"' + itr->first + "\",";
    std::cout << "\n  { "
              << std::left << std::setw(longest) << n << ' '
              << std::right << std::setw(3) << itr->second << " }";

    for (++itr; itr != end; ++itr) {
      n = '"' + itr->first + "\",";
      std::cout << ",\n  { "
                << std::left << std::setw(longest) << n << ' '
                << std::right << std::setw(3) << itr->second << " }";
    }

    std::cout << '\n';
  }

  std::cout <<
R"(};

)";

  // print the encoding id to canonical name map
  std::cout <<
R"(static const char* const LG_CANONICAL_ENCODINGS[] = {
)";

  longest_canonical += 3;
  const int32_t csize = canonical.size();
  for (int32_t i = 0; i < csize; ++i) {
    std::string n(canonical[i]);
    n = '"' + n + '"';
    if (i + 1 < clen) {
      n += ',';
    }
    std::cout << "  " << std::left << std::setw(longest_canonical) << n
              << " // " << std::right << std::setw(3) << i << '\n';
  }

  std::cout <<
"};";

  // sort the aliases by the indices of their canonical names
  std::vector<std::pair<std::string,uint32_t>> aliases(idmap.begin(), idmap.end());
  std::sort(aliases.begin(), aliases.end(),
    [](const std::pair<std::string,uint32_t>& a,
       const std::pair<std::string,uint32_t>& b)
    {
      return a.second < b.second || (a.second == b.second && a.first < b.first);
    }
  );

  std::pair<std::string,uint32_t> prev{"", std::numeric_limits<uint32_t>::max()};

  for (const auto& p : aliases) {
    // print the canonical name for the encoding
    if (p.second != prev.second) {
      std::cout << "\n\n// " << canonical[p.second];
      prev.second = p.second;
    }

    // create a valid variable name
    std::string alias(p.first);
    std::transform(alias.begin(), alias.end(), alias.begin(), toupper);
    std::replace_if(alias.begin(), alias.end(),
      [](char c){ return !isalnum(c); }, '_'
    );

    std::ostringstream ss;
    if (prev.first != alias) {
      ss << " //";
    }

    for (const std::string& s : standards) {
      UEnumeration *nameEnum =
        ucnv_openStandardNames(canonical[prev.second].c_str(), s.c_str(), &err);
      throw_on_error(err);

      bool first = true;
      const char* standardName;
      while ((standardName = uenum_next(nameEnum, nullptr, &err))) {
        if (!strcmp(standardName, p.first.c_str())) {
          if (!s.empty()) {
            ss << ' ' << s;

            if (first) {
              ss << '*';
            }
          }
        }

        first = false;
      }

      uenum_close(nameEnum);
    }

    if (ss.str().length() == 3) {
      ss.str("");
    }

    if (prev.first == alias) {
      std::cout << ss.str();
    }
    else {
      std::cout << "\nstatic const int LG_ENCODING_" << alias
                << " = " << p.second << ';' << ss.str();
      prev.first = alias;
    }
  }

  // close the extern block and ifdefs
  std::cout <<
R"(

#ifdef __cplusplus
}
#endif

#endif /* LIGHTGREP_C_ENCODINGS_H_ */)"
  << std::endl;

  return 0;
}
