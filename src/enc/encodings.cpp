#include <algorithm>
#include <cctype>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include <unicode/ucnv.h>

#include "basic.h"

void throw_on_error(UErrorCode err) {
  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("ICU error: " << u_errorName(err));
  }
}

int main(int, char**) {
  // print copyright notice, ifdef guards, open extern "C" block
  std::cout <<
"// Copyright 2011-2012, Lightbox Technologies, Inc. All Rights Reserved.\n"
"\n"
"#ifndef __ENCODINGS_H_\n"
"#define __ENCODINGS_H_\n"
"\n"
"#ifdef __cplusplus\n"
"extern \"C\" {\n"
"#endif\n"
"\n";

  // Preference ordering for standards, to resolve name conficts
  //
  // UTR22 > IANA > MIME > IBM > WINDOWS > JAVA > ""
  //
  const std::vector<std::string> standards{
    "UTR22", "IANA", "MIME", "IBM", "WINDOWS", "JAVA", ""
  };

  // Encodings to skip
  const std::set<std::string> skip{
    "UTF-16", "UTF-32", "UTF-16,version=1", "UTF-16,version=2"
  };

  std::vector<std::string> canonical;
  std::map<std::string,uint32> idmap;
  size_t longest = 0, longest_canonical = 0;

  UErrorCode err = U_ZERO_ERROR;

  const int32 clen = ucnv_countAvailable();
  for (int32 i = 0; i < clen; ++i) {
    // get the canonical name for the ith encoding
    const char* cname = ucnv_getAvailableName(i);

    // skip encodings we want to omit
    if (skip.find(cname) != skip.end()) {
      continue;
    }

    canonical.emplace_back(cname);

    const int32 alen = ucnv_countAliases(cname, &err);
    throw_on_error(err);

    longest_canonical = std::max(longest_canonical, strlen(cname));
    longest = std::max(longest, longest_canonical);

    for (int32 j = 0; j < alen; ++j) {
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

  // print the name to encoding id map
  std::cout <<
"typedef struct {\n"
"  const char* const name;\n"
"  unsigned int idx;\n"
"} LG_SUPPORTED_ENCODING;\n"
"\n"
"static const LG_SUPPORTED_ENCODING LG_SUPPORTED_ENCODINGS[] = {";

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
"};\n"
"\n";

  // print the encoding id to canonical name map
  std::cout <<
"static const char* const LG_CANONICAL_ENCODINGS[] = {\n";

  longest_canonical += 3;
  const int32 csize = canonical.size();
  for (int32 i = 0; i < csize; ++i) {
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
  std::vector<std::pair<std::string,uint32>> aliases(idmap.begin(), idmap.end());
  std::sort(aliases.begin(), aliases.end(),
    [](const std::pair<std::string,uint32>& a,
       const std::pair<std::string,uint32>& b)
    {
      return a.second < b.second || (a.second == b.second && a.first < b.first);
    }
  );
  
  std::pair<std::string,uint32> prev{"", std::numeric_limits<uint32>::max()};

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

    std::stringstream ss;
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
      std::cout << "\nstatic const int LG_ENC_" << alias
                << " = " << p.second << ';' << ss.str();
      prev.first = alias;
    }
  }

  // close the extern block and ifdefs
  std::cout <<
"\n"
"\n"
"int lg_get_encoding_id(const char* const name);\n"
"\n"
"#ifdef __cplusplus\n"
"}\n"
"#endif\n"
"\n"
"#endif /* __ENCODINGS_H_ */"
  << std::endl;

  return 0;
}
