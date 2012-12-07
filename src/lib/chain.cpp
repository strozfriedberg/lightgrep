/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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
#include "chain.h"
#include "lightgrep/encodings.h"
#include "lightgrep/transforms.h"
#include "lightgrep/util.h"

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
    id = lg_get_char_char_transformation_id(curTok->c_str());
    if (id < 0) {
      break;
    }

    charchar.emplace_back(LG_CANONICAL_CHAR_CHAR_TRANSFORMATIONS[id]);
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
    id = lg_get_byte_byte_transformation_id(curTok->c_str());
    if (id < 0) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(
        "'" << *curTok << "' is not a valid byte->byte transformation"
      );
    }

    bytebyte.emplace_back(LG_CANONICAL_BYTE_BYTE_TRANSFORMATIONS[id]);
  }

  return std::make_tuple(
    std::move(charchar),
    std::move(charbyte),
    std::move(bytebyte)
  );
}
