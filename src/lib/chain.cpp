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

#include "lightgrep/encodings.h"
#include "lightgrep/transforms.h"
#include "lightgrep/util.h"

#include "basic.h"
#include "chain.h"

#include <boost/tokenizer.hpp>

std::tuple<
  std::vector<std::string>,
  std::string,
  std::vector<std::string>
>
parseChain(const std::string& chain) {
  // TODO: convert parsing to a yacc grammar

  typedef boost::char_separator<char> char_separator;
  typedef boost::tokenizer<char_separator> tokenizer;

  const tokenizer tokens(chain, char_separator("|"));
  tokenizer::const_iterator curTok(tokens.begin());
  const tokenizer::const_iterator endTok(tokens.end());

  int id;

  // process the char->char transformations
  std::vector<std::string> charchar;
  for ( ; curTok != endTok; ++curTok) {
    id = lg_get_char_transform_id(curTok->c_str());
    if (id < 0) {
      break;
    }

    charchar.emplace_back(LG_CANONICAL_CHAR_TRANSFORMS[id]);
  }

  if (curTok == endTok) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("No valid char->byte transformation");
  }

  // process the char->byte transformation
  id = lg_get_encoding_id(curTok->c_str());
  if (id < 0) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "'" << *curTok << "' is neither a valid char->char transformation "
      "nor a valid char->byte transformation"
    );
  }

  const std::string charbyte = LG_CANONICAL_ENCODINGS[id];
  ++curTok;

  // process the byte->byte transformations
  std::vector<std::string> bytebyte;
  for ( ; curTok != endTok; ++curTok) {
    id = lg_get_byte_transform_id(curTok->c_str());
    if (id < 0) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(
        "'" << *curTok << "' is not a valid byte->byte transformation"
      );
    }

    bytebyte.emplace_back(LG_CANONICAL_BYTE_TRANSFORMS[id]);
  }

  return std::make_tuple(
    std::move(charchar),
    std::move(charbyte),
    std::move(bytebyte)
  );
}
