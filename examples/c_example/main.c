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

#include "lightgrep/api.h"

#include <stdio.h>
#include <string.h>

// declarations for functions below, to avoid warnings, although not necessary
void getHit(void*, const LG_SearchHit* const);
void searchText(const char**, unsigned int, LG_HCONTEXT);


// callback function that receives the search hit
void getHit(void* userData, const LG_SearchHit* const hit) {
  // my printf() doesn't like printing out 64-bit uints, hence the unfortunate casts
  printf("userData: %p, hit: (%u, %u, %u)\n", userData, (unsigned int)hit->Start, (unsigned int)hit->End, hit->KeywordIndex);
}

void searchText(const char** textArray, unsigned int numStrings, LG_HCONTEXT searcher) {
  // reset the search context for re-use (not necessary on first use, but harmless)
  lg_reset_context(searcher);
  uint64_t offset = 0,
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

int main(int, char**) {
  const char* keys[] = {"mary", "lamb", "[a-z]+"};
  const unsigned int kcount = sizeof(keys)/sizeof(keys[0]);

  // find the total length (in characters) of the patterns
  unsigned int klen = 0;
  for (unsigned int i = 0; i < kcount; ++i) {
    klen += strlen(keys[i]);
  }

  LG_HFSM fsm = lg_create_fsm(kcount, klen);

  // create a pattern handle, which we'll reuse for each pattern
  LG_HPATTERN pattern = lg_create_pattern();

  LG_KeyOptions keyOpts;
  keyOpts.FixedString = 0;
  keyOpts.CaseInsensitive = 1;
  keyOpts.UnicodeMode = 0;

  // parse the keywords one at a time
  int isgood = 1;
  LG_Error* err = 0;
  for (unsigned int i = 0; i < kcount; ++i) {
    lg_parse_pattern(pattern, keys[i], &keyOpts, &err);

    if (err) {
      fprintf(
        stderr, "Parse error on keyword %d, %s: %s", i, keys[i], err->Message
      );
      isgood = 0;
      lg_free_error(err);
      break;
    }

    lg_add_pattern(fsm, pattern, "ASCII", i, &err);

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
    opts.DeterminizeDepth = UINT32_MAX;

    LG_HPROGRAM prog = lg_create_program(fsm, &opts);
    if (!prog) {
      fprintf(stderr, "Failed to compile program");
    }

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

  return ret;
}
