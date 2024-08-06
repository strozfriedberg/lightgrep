/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <pcre.h>

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

void parse(const char* pattern) {
  const char* error_str;
  int error_off;

  pcre* re = pcre_compile(
    pattern,
    PCRE_DOTALL | PCRE_NO_AUTO_CAPTURE,
    &error_str,
    &error_off,
    nullptr
  );

  if (!re) { 
    std::cout << pattern << ' ' << error_str << std::endl;
  }
 
  free(re);
}

/*
  Attempt to parse with PCRE all ASCII strings <= the given length.
*/

int main(int argc, char** argv) {
  const uint32_t maxlen = boost::lexical_cast<uint32_t>(argv[1]);

  std::string pat = " "; // 0x20

  do {
    parse(pat.c_str());

    // increment
    for (std::string::iterator i(pat.begin()); ++*i == 0x7F; ) {
      *i = 0x20;
      ++i;
      if (i == pat.end()) {
        pat += ' ';
        break;
      }
    }
  } while (pat.length() <= maxlen);

  return 0;
}
