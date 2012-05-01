#include <algorithm>
#include <cctype>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <map>

#include <unicode/ucnv.h>

#include "basic.h"

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

  // collect the encoding names and their canonical ids
  std::map<std::string,uint32> idmap;
  size_t longest = 0, longest_canonical = 0;
 
  UErrorCode err = U_ZERO_ERROR;

  const int32 clen = ucnv_countAvailable();
  for (int32 i = 0; i < clen; ++i) {
    // get the canonical name for the encoding
    const char* n = ucnv_getAvailableName(i);
    idmap.insert(std::make_pair(n, i));

    longest_canonical = std::max(longest_canonical, strlen(n)); 
    longest = std::max(longest, longest_canonical);

    const int32 alen = ucnv_countAliases(n, &err);
    if (U_FAILURE(err)) {
      // should not happen
      THROW_RUNTIME_ERROR_WITH_OUTPUT("ICU error: " << u_errorName(err));
    }

    for (int32 j = 0; j < alen; ++j) {
      const char* a = ucnv_getAlias(n, j, &err);
      idmap.insert(std::make_pair(a, i));

      longest = std::max(longest, strlen(a));

      if (U_FAILURE(err)) {
        // should not happen
        THROW_RUNTIME_ERROR_WITH_OUTPUT("ICU error: " << u_errorName(err));
      }
    }
  }

  // print the name to encoding id map
  std::cout <<
"typedef struct {\n"
"  const char* const name;\n"
"  size_t idx;\n"
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
  for (int32 i = 0; i < clen; ++i) {
    std::string n = ucnv_getAvailableName(i);
    n = '"' + n + '"';
    if (i + 1 < clen) {
      n += ',';
    }
    std::cout << "  " << std::left << std::setw(longest_canonical) << n
              << " // " << std::right << std::setw(3) << i << '\n';
  }

  std::cout <<
"};\n"
"\n";

  // print the encoding constants
  for (int32 i = 0; i < clen; ++i) {
    if (i > 0) {
      std::cout << '\n';
    }

    // print the canonical name for the encoding
    const char* n = ucnv_getAvailableName(i);
    std::cout << "// " << n << '\n';

    // print the aliases for the encoding
    const int32 alen = ucnv_countAliases(n, &err);
    if (U_FAILURE(err)) {
      // should not happen
      THROW_RUNTIME_ERROR_WITH_OUTPUT("ICU error: " << u_errorName(err));
    }

    for (int32 j = 0; j < alen; ++j) {
      std::string alias(ucnv_getAlias(n, j, &err));
      std::transform(alias.begin(), alias.end(), alias.begin(), toupper);
      std::replace_if(alias.begin(), alias.end(),
                      [](char c){ return !isalnum(c); }, '_');

      std::cout << "static const int LG_ENC_" << alias << " = " << i << ";\n";

      if (U_FAILURE(err)) {
        // should not happen
        THROW_RUNTIME_ERROR_WITH_OUTPUT("ICU error: " << u_errorName(err));
      }
    }
  }

  // close the extern block and ifdefs
  std::cout <<
"\n"
"#ifdef __cplusplus\n"
"}\n"
"#endif\n"
"\n"
"#endif /* __ENCODINGS_H_ */"
  << std::endl;  
 
  return 0;
}
