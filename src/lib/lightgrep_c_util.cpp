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

/*
#include "container_out.h"
#include "pair_out.h"
#include <iostream>
*/

#include <algorithm>
#include <cctype>
#include <memory>
#include <string>

#include "decoders/decoder.h"
#include "decoders/decoderfactory.h"
#include "decoders/utf8.h"

#include "c_api_util.h"
#include "lightgrep/util.h"
#include "lightgrep/transforms.h"
#include "lightgrep/encodings.h"

int find_trans_id(const LG_TRANS* beg, const LG_TRANS* end, const char* const name) {
  std::string ns(name);
  std::transform(ns.begin(), ns.end(), ns.begin(), ::tolower);

// TODO: encodings are sorted by name, so do a binary search
  const LG_TRANS* ptr = std::find_if(
    beg,
    end,
    [&](const LG_TRANS& t) -> bool {
      std::string ts(t.name);
// FIXME: why ::tolower instead of std::tolower?
// ::tolower() comes from cctype where std::tolower comes from <locale>
// I'm uncertain we should really be doing case-insensitive comparison here. -- JLS
      std::transform(ts.begin(), ts.end(), ts.begin(), ::tolower);
      return ns == ts;
    }
  );

  return ptr == end ? -1 : ptr->idx;
}

int lg_get_char_char_transformation_id(const char* const name) {
  return trapWithRetval(
    [name](){
      return find_trans_id(
        LG_CHAR_CHAR_TRANSFORMATIONS,
        LG_CHAR_CHAR_TRANSFORMATIONS +
          sizeof(LG_CHAR_CHAR_TRANSFORMATIONS)/sizeof(LG_TRANS),
        name
      );
    },
    -1
  );
}

int lg_get_encoding_id(const char* const name) {
  return trapWithRetval(
    [name](){
      return find_trans_id(
        LG_ENCODINGS,
        LG_ENCODINGS +
          sizeof(LG_ENCODINGS)/sizeof(LG_TRANS),
        name
      );
    },
    -1
  );
}

int lg_get_byte_byte_transformation_id(const char* const name) {
  return trapWithRetval(
    [name](){
      return find_trans_id(
        LG_BYTE_BYTE_TRANSFORMATIONS,
        LG_BYTE_BYTE_TRANSFORMATIONS +
          sizeof(LG_BYTE_BYTE_TRANSFORMATIONS)/sizeof(LG_TRANS),
        name
      );
    },
    -1
  );
}

unsigned int decode(const byte* beg, const byte* end, Decoder& dec, std::vector<std::pair<int32_t,const byte*>>& cps) {
  dec.reset(beg, end);

  unsigned int bad = 0;

  std::pair<int32_t,const byte*> cp;
  while ((cp = dec.next()).first != Decoder::END) {
    if (cp.first < 0) {
      ++bad;
    }
    cps.push_back(cp);
  }

  cps.push_back(cp);

  return bad;
}

unsigned int lg_read_window(
  const char* bufStart,
  const char* bufEnd,
  uint64_t dataOffset,
  const LG_Window* inner,
  const char* encoding,
  size_t preContext,
  size_t postContext,
  int32_t** characters,
  size_t** offsets,
  size_t* clen)
{
// FIXME: it's stupid to recreate the factory each time
  DecoderFactory dfac;
  std::shared_ptr<Decoder> dec(dfac.get(encoding));

  unsigned int bad = 0;

  std::pair<int32_t,const byte*> cp;
  std::vector<std::pair<int32_t,const byte*>> cps;

  const byte* bbeg = reinterpret_cast<const byte*>(bufStart);
  const byte* bend = reinterpret_cast<const byte*>(bufEnd);

  const byte* hbeg =
    reinterpret_cast<const byte*>(bufStart) + inner->begin - dataOffset;
  const byte* hend =
    reinterpret_cast<const byte*>(bufStart) + inner->end - dataOffset;

// FIXME: bufStart and bufEnd might be nowhere near the window, so we could
// be doing tons of extra work here

  if (bbeg != hbeg) {
    bad += decode(bbeg, hbeg, *dec, cps);
    // drop the END marker for the leading context
    cps.pop_back();
  }
  bad += decode(hbeg, bend, *dec, cps);

  auto wbeg = std::find_if(
    cps.begin(), cps.end(),
    [hbeg](const std::pair<int32_t,const byte*>& p) {
      return p.second == hbeg;
    }
  );

  // back up by preContext, but don't run off the front
  wbeg = ((size_t)(wbeg - cps.begin()) > preContext) ?
    wbeg - preContext : cps.begin();

  auto wend = std::find_if(
    wbeg, cps.end(),
    [hend](const std::pair<int32_t,const byte*>& p) {
      return p.second == hend;
    }
  );

  // advance by postContext (+1 for END element), but don't run off the end
  wend = ((size_t)(cps.end() - wend) > postContext) ?
    wend + postContext + 1 : cps.end();

  *clen = wend - wbeg;
  *characters = new int32_t[*clen];
  *offsets = new size_t[*clen];

  auto wi = wbeg;
  for (size_t i = 0; wi != wend; ++i, ++wi) {
    (*characters)[i] = wi->first;
    (*offsets)[i] = wi->second - bbeg;
  }

  (*characters)[*clen-1] = Decoder::END;

  return bad;
}

unsigned int lg_hit_context(const char* bufStart,
                            const char* bufEnd,
                            uint64_t dataOffset,
                            const LG_Window* inner,
                            const char* encoding,
                            size_t windowSize,
                            uint32_t replacement,
                            const char** utf8,
                            LG_Window* outer)
{
  // decode the hit and its context using the deluxe decoder
  int32_t* characters;
  size_t* offsets;
  size_t clen;

  const unsigned int bad = lg_read_window(
    bufStart,
    bufEnd,
    dataOffset,
    inner,
    encoding,
    windowSize,
    windowSize,
    &characters,
    &offsets,
    &clen
  );

  std::unique_ptr<int32_t[],void(*)(int32_t*)> pchars(
    characters, lg_free_window_characters
  );

  std::unique_ptr<size_t[],void(*)(size_t*)> poff(
    offsets, lg_free_window_offsets
  );

  outer->begin = dataOffset + offsets[0];
  outer->end = dataOffset + offsets[clen-1];

  // convert the code points to UTF-8
  std::vector<char> bytes;
  char buf[4];
  size_t produced;

  // encode to UTF-8, replacing bad or null elements with the replacement
  // code point, stopping one short since the last element of characters
  // is END
  for (const int32_t* i = characters; i < characters+clen-1; ++i) {
    produced = cp_to_utf8(*i <= 0 ? replacement : *i, buf);
    std::copy(buf, buf+produced, std::back_inserter(bytes));
  }

  // null-terminate the UTF-8 bytes
  bytes.push_back(0);

  char* str = new char[bytes.size()];
  std::copy(bytes.begin(), bytes.end(), str);

  *utf8 = str;

  return bad;
}


void lg_free_window_characters(int32_t* characters) {
  delete[] characters;
}

void lg_free_window_offsets(size_t* offsets) {
  delete[] offsets;
}

void lg_free_hit_context_string(const char* utf8) {
  delete[] utf8;
}
