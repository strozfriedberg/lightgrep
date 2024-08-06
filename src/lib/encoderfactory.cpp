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
      enc.reset(new RotEncoder(
        boost::lexical_cast<uint32_t>(cc->substr(3)), std::move(enc)
      ));
    }
// FIXME: Shouldn't XOR be a byte-byte transformation?
    else if (cc->substr(0, 3) == "XOR") {
      enc.reset(new XOREncoder(
        boost::lexical_cast<byte>(cc->substr(3)), std::move(enc)
      ));
    }
  }

  return std::shared_ptr<Encoder>(new CachingEncoder(std::move(enc)));
}
