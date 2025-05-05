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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "chain.h"
#include "decoders/asciidecoder.h"
#include "decoders/bytesource.h"
#include "decoders/decoderfactory.h"
#include "decoders/ocedecoder.h"
#include "decoders/rotdecoder.h"
#include "decoders/utf8decoder.h"
#include "decoders/utf16decoder.h"
#include "decoders/utf32decoder.h"
#include "decoders/xordecoder.h"

#ifdef HAVE_ICU
#include "decoders/icudecoder.h"
#endif

#include "boost_lexical_cast.h"

std::shared_ptr<Decoder> DecoderFactory::get(const std::string& chain) {
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
  std::unique_ptr<Decoder> enc(new ByteSource(nullptr, nullptr));

  for (auto bb = bytebyte.crbegin(); bb != bytebyte.crend(); ++bb) {
    if (*bb == "identity") {
      // do nothing
    }
    else if (*bb == "OCE") {
      enc.reset(new OCEDecoder(std::move(enc)));
    }
    else if (bb->substr(0, 3) == "XOR") {
      enc.reset(new XORDecoder(
        boost::lexical_cast<byte>(bb->substr(3)), std::move(enc)
      ));
    }
  }

  if (charbyte == "ASCII" || charbyte == "US-ASCII") {
    enc.reset(new ASCIIDecoder(std::move(enc)));
  }
  else if (charbyte == "UTF-8") {
    enc.reset(new UTF8Decoder(std::move(enc)));
  }
  else if (charbyte == "UTF-16LE") {
    enc.reset(new UTF16LEDecoder(std::move(enc)));
  }
  else if (charbyte == "UTF-16BE") {
    enc.reset(new UTF16BEDecoder(std::move(enc)));
  }
  else if (charbyte == "UTF-32LE") {
    enc.reset(new UTF32LEDecoder(std::move(enc)));
  }
  else if (charbyte == "UTF-32BE") {
    enc.reset(new UTF32BEDecoder(std::move(enc)));
  }
  else {
#ifdef HAVE_ICU
    enc.reset(new ICUDecoder(charbyte.c_str(), std::move(enc)));
#else
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Unrecognized encoding '" << charbyte << "'"
    );
#endif
  }

  for (auto cc = charchar.crbegin(); cc != charchar.crend(); ++cc) {
    if (*cc == "identity") {
      // do nothing
    }
    else if (cc->substr(0, 3) == "rot") {
      enc.reset(new RotDecoder(
        boost::lexical_cast<uint32_t>(cc->substr(3)), std::move(enc)
      ));
    }
  }

  return std::shared_ptr<Decoder>(std::move(enc));
}
