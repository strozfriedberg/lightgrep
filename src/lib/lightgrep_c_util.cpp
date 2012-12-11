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
#include <string>

#include "decoders/decoder.h"
#include "decoders/decoderfactory.h"

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
      std::transform(ts.begin(), ts.end(), ts.begin(), ::tolower);
      return ns == ts;
    }
  );

  return ptr == end ? -1 : ptr->idx;
}

int lg_get_char_char_transformation_id(const char* const name) {
  return trap_with_retval(
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
  return trap_with_retval(
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
  return trap_with_retval(
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

/*
unsigned int lg_decode(
  const char* bufStart,
  const char* bufEnd,
  const char* encoding,
  int32_t** characters,
  const char*** offsets,
  size_t* clen)
{
  DecoderFactory dfac;
  std::shared_ptr<Decoder> dec(dfac.get(encoding));

  unsigned int bad = 0;

  std::pair<int32_t,const byte*> cp;
  std::vector<std::pair<int32_t,const byte*>> cps;

  dec->reset(
    reinterpret_cast<const byte*>(bufStart),
    reinterpret_cast<const byte*>(bufEnd)
  );

  while ((cp = dec->next()).first != Decoder::END) {
    if (cp.first < 0) {
      ++bad;
    }
    cps.push_back(cp);
  }

  cps.push_back(cp);

  *clen = cps.size();
  *characters = new int32_t[*clen];
  *offsets = new const char*[*clen];

  for (size_t i = 0; i < cps.size(); ++i) {
    (*characters)[i] = cps[i].first;
    (*offsets)[i] = reinterpret_cast<const char*>(cps[i].second);
  }

  return bad;
}
*/

unsigned int lg_read_window(
  const char* bufStart,
  const char* bufEnd,
  uint64_t dataOffset,
  const LG_Window* inner,
  const char* encoding,
  size_t preContext,
  size_t postContext,
  int32_t** characters,
  const char*** offsets,
  size_t* clen)
{
// FIXME: it's stupid to recreate the factory each time
  DecoderFactory dfac;
  std::shared_ptr<Decoder> dec(dfac.get(encoding));

  unsigned int bad = 0;

  std::pair<int32_t,const byte*> cp;
  std::vector<std::pair<int32_t,const byte*>> cps;

  dec->reset(
    reinterpret_cast<const byte*>(bufStart),
    reinterpret_cast<const byte*>(bufEnd)
  );

// FIXME: bufStart and bufEnd might be nowhere near the window, so we could
// be doing tons of extra work here
  while ((cp = dec->next()).first != Decoder::END) {
    if (cp.first < 0) {
      ++bad;
    }
    cps.push_back(cp);
  }

  cps.push_back(cp);

  const byte* hbeg =
    reinterpret_cast<const byte*>(bufStart) + inner->begin - dataOffset;
  const byte* hend =
    reinterpret_cast<const byte*>(bufStart) + inner->end - dataOffset;

  auto wbeg = std::find_if(
    cps.begin(), cps.end(),
    [hbeg](const std::pair<int32_t,const byte*>& p) {
      return p.second == hbeg;
    }
  );

  // back up by preContext, but don't run off the front
  wbeg = (wbeg - cps.begin() > preContext) ? wbeg - preContext : cps.begin();

  auto wend = std::find_if(
    wbeg, cps.end(),
    [hend](const std::pair<int32_t,const byte*>& p) {
      return p.second == hend;
    }
  );

  // advance by postContext (+1 for END element), but don't run off the end
  wend = (cps.end() - wend > postContext) ? wend + postContext + 1 : cps.end();

  *clen = wend - wbeg;
  *characters = new int32_t[*clen];
  *offsets = new const char*[*clen];

  auto wi = wbeg;
  for (size_t i = 0; wi != wend; ++i, ++wi) {
    (*characters)[i] = wi->first;
    (*offsets)[i] = reinterpret_cast<const char*>(wi->second);
  }

  (*characters)[*clen-1] = Decoder::END;

  return bad;
}

void lg_free_window_characters(int32_t* characters) {
  delete[] characters;
}

void lg_free_window_offsets(const char** offsets) {
  delete[] offsets;
}
