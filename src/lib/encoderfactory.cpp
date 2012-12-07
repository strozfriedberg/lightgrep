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

#include "chain.h"
#include "encoders/ascii.h"
#include "encoders/concrete_encoders.h"
#include "encoders/encoderfactory.h"
#include "encoders/icuencoder.h"
#include "encoders/oceencoder.h"
#include "encoders/rotencoder.h"
#include "encoders/utf8.h"
#include "encoders/utf16.h"
#include "encoders/utf32.h"
#include "encoders/xorencoder.h"

#include <boost/lexical_cast.hpp>

EncoderFactory::EncoderFactory():
  Cache{
    { "ASCII",    std::make_shared<ASCII>()          },
    { "UTF-8",    std::make_shared<CachingUTF8>()    },
    { "UTF-16LE", std::make_shared<CachingUTF16LE>() },
    { "UTF-16BE", std::make_shared<CachingUTF16BE>() },
    { "UTF-32LE", std::make_shared<CachingUTF32LE>() },
    { "UTF-32BE", std::make_shared<CachingUTF32BE>() }
  }
{}

std::shared_ptr<Encoder> EncoderFactory::get(const std::string& chain) {
  // return a cached encoder if we have one
  auto i = Cache.find(chain);
  if (i != Cache.end()) {
    return i->second;
  }

  // parse the transformation chain
  std::vector<std::string> charchar, bytebyte;
  std::string charbyte;
  std::tie(charchar, charbyte, bytebyte) = parseChain(chain);

  // assemble the transformation chain 
  std::unique_ptr<Encoder> enc;

  if (charbyte == "ASCII") {
    enc.reset(new ASCII);
  }
  else if (charbyte == "UTF-8") {
    enc.reset(new UTF8);
  }
  else if (charbyte == "UTF-16LE") {
    enc.reset(new UTF16LE);
  }
  else if (charbyte == "UTF-16BE") {
    enc.reset(new UTF16BE);
  }
  else if (charbyte == "UTF-32LE") {
    enc.reset(new UTF32LE);
  }
  else if (charbyte == "UTF-32BE") {
    enc.reset(new UTF32BE);
  }
  else {
    enc.reset(new ICUEncoder(charbyte));
  }

  for (const std::string& bb : bytebyte) {
    if (bb == "identity") {
      // do nothing
    }
    else if (bb == "OCE") {
      enc.reset(new OCEEncoder(std::move(enc)));
    }
  }

  for (auto cc = charchar.crbegin(); cc != charchar.crend(); ++cc) {
    if (*cc == "identity") {
      // do nothing
    }
    else if (cc->substr(0, 3) == "rot") {
      enc.reset(new ROTEncoder(
        boost::lexical_cast<uint32_t>(cc->substr(3)), std::move(enc)
      ));
    }
    else if (cc->substr(0, 3) == "XOR") {
      enc.reset(new XOREncoder(
        boost::lexical_cast<byte>(cc->substr(3)), std::move(enc)
      ));
    }
  }

  return std::shared_ptr<Encoder>(new CachingEncoder(std::move(enc)));
}
