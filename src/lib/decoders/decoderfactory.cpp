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

#include "chain.h"
#include "decoders/asciidecoder.h"
#include "decoders/bytesource.h"
#include "decoders/icudecoder.h"
#include "decoders/decoderfactory.h"
#include "decoders/ocedecoder.h"
#include "decoders/rotdecoder.h"
#include "decoders/utf8decoder.h"
#include "decoders/utf16decoder.h"
#include "decoders/utf32decoder.h"
#include "decoders/xordecoder.h"

#include <boost/lexical_cast.hpp>

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
    enc.reset(new ICUDecoder(charbyte.c_str(), std::move(enc)));
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
