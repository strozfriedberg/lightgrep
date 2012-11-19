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

#include "lightgrep_c_api.h"
#include "encodings.h"

#include <stdio.h>
#include <string.h>

// callback function that receives the search hit
void getHit(void* userData, const LG_SearchHit* const hit) {
  // my printf() doesn't like printing out 64-bit uints, hence the unfortunate casts
  printf("userData: %p, hit: (%u, %u, %u)\n", userData, (unsigned int)hit->Start, (unsigned int)hit->End, hit->KeywordIndex);
}

void searchText(const char** textArray, unsigned int numStrings, LG_HCONTEXT searcher) {
  // reset the search context for re-use (not necessary on first use, but harmless)
  lg_reset_context(searcher);
  uint64 offset = 0,
         len;

  // search text as if it were a contiguous array
  unsigned int i;
  for (i = 0; i < numStrings; ++i) {
    len = strlen(textArray[i]);
    lg_search(searcher, textArray[i], textArray[i] + len, offset, (void*)17, getHit);
    offset += len;
  }
  // flush any remaining hits -- done once at end of file
  lg_closeout_search(searcher, (void*)17, getHit);
}

int main() {
  const char* keys[] = {"mary", "lamb", "[a-z]+"};
  const unsigned int kcount = sizeof(keys)/sizeof(keys[0]);

  // pattern info is stored in the pattern map
  LG_HPATTERNMAP pmap = lg_create_pattern_map(kcount);

  // find the total length (in characters) of the patterns
  unsigned int klen = 0;
  for (unsigned int i = 0; i < kcount; ++i) {
    klen += strlen(keys[i]);
  }

  LG_HFSM fsm = lg_create_fsm(klen);

  // declare a pattern handle, which we'll reuse for each pattern
  LG_HPATTERN pattern = 0;

  LG_KeyOptions keyOpts;
  keyOpts.CaseInsensitive = 1;
  keyOpts.FixedString = 0;

  LG_EncodingChain enc = { "ASCII" };

  // parse the keywords one at a time
  int isgood = 1;
  LG_Error* err = 0;
  for (unsigned int i = 0; i < kcount; ++i) {
    pattern = lg_parse_pattern(pattern, keys[i], &keyOpts, &err);

    if (err) {
      fprintf(
        stderr, "Parse error on keyword %d, %s: %s", i, keys[i], err->Message
      );
      isgood = 0;
      lg_free_error(err);
      break;
    }

    lg_add_pattern(fsm, pmap, pattern, &enc, &err);

    if (err) {
      fprintf(
        stderr, "Parse error on keyword %d, %s: %s", i, keys[i], err->Message
      );
      isgood = 0;
      lg_free_error(err);
      break;
    }
  }

  // discard the pattern handle now that we've parsed all patterns
  lg_destroy_pattern(pattern);
  pattern = 0;

  int ret = 1;
  if (isgood) {
    // create a "program" from the parsed keywords
    LG_ProgramOptions opts;
    LG_HPROGRAM prog = lg_create_program(fsm, &opts);

    // discard the FSM now that we have a program
    lg_destroy_fsm(fsm);
    fsm = 0;

    // create a search context
    LG_ContextOptions ctxOpts;
    LG_HCONTEXT searcher = lg_create_context(prog, &ctxOpts);

    char filesigText[] = "lambs love mary.";
    printf("using startsWith\n");

    lg_starts_with(searcher, filesigText, filesigText + 16, 0, (void*)23, getHit);

    printf("done with startsWith\n");

    printf("beginning search\n");

    // search texts as if they were a contiguous array
    const char *mary[2] = {"Mary had a little l", "amb"},
               *twinkle[3] = {"Twin", "kle twink", "le, little star"};

    printf("searching 'Mary had a little lamb'\n");

    searchText(mary, 2, searcher);

    printf("searching 'Twinkle twinkle, little star'\n");

    searchText(twinkle, 3, searcher);

    printf("done with search\n");

    lg_destroy_context(searcher);
    lg_destroy_program(prog);

    ret = 0;
  }

  lg_destroy_pattern_map(pmap);

  return ret;
}
