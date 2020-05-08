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

#ifndef LIGHTGREP_C_API_H_
#define LIGHTGREP_C_API_H_

#include "search_hit.h"

#ifdef __cplusplus
extern "C" {
#endif

  // Opaque handles to thingies
  struct PatternHandle;
  struct PatternMapHandle;
  struct FSMHandle;
  struct ProgramHandle;
  struct ContextHandle;

  typedef struct PatternHandle*    LG_HPATTERN;
  typedef struct FSMHandle*        LG_HFSM;
  typedef struct ProgramHandle*    LG_HPROGRAM;
  typedef struct ContextHandle*    LG_HCONTEXT;

  // Options for pattern parsing
  typedef struct {
    char FixedString;     // 0 => grep, non-zero => fixed-string
    char CaseInsensitive; // 0 => case sensitive, non-zero => case insensitive
    char UnicodeMode;     // 0 => ASCII mode, non-zero => Unicode mode
  } LG_KeyOptions;

  //
  // ASCII mode vs Unicode mode
  //
  // ASCII mode has two effects:
  //
  // *) The named character classes \d, \s, \w are restricted to match only
  //    ASCII characters. (E.g., \w in ASCII mode will not match Greek letters,
  //    but \w in Unicode mode will.)
  //
  // *) ASCII code points in case insensitive patterns case fold to ASCII code
  //    points only. (E.g., case-insensitive [ks] in ASCII mode is eqivalent to
  //    [KSks], but case-insensitive [ks] in Unicode mode is equivalent to
  //    [KSks\N{KELVIN SIGN}\N{LATIN SMALL LETTER LONG S}], because KELVIN SIGN
  //    case folds to k and LATIN SMALL LETTER LONG S case folds to s.
  //
  // In contrast, Unicode mode is more expansive:
  //
  // *) \d matches characters in Unicode category Nd (Number, Decimal Digit)
  //
  // *) \s matches characters in Unicode category Z (Separator), along with
  //    everything matched by \h (horizontal space) and \v (vertical space)
  //
  // *) \w matches the underscore '_' and charaters in Unicode categories L
  //    (Letter) or N (Number).
  //
  // *) Full Unicode case folding is applied to case insensitive patterns.
  //    Hence [ks] will match KELVIN SIGN and LATIN SMALL LETTER LONG S.
  //
  // See also the discussions of /a and /aa in perlre(1) and of (*UCP) in
  // pcrepattern(3).
  //

  // Encoding options for patterns
  typedef struct {
    const char* Pattern;
    const char* EncodingChain;
    uint64_t UserIndex;   // set by user when adding the pattern
  } LG_PatternInfo;

  // Options for compiling patterns
  typedef struct {
    char Determinize;     // 0 => build NFA, non-zero => build (pseudo)DFA
  } LG_ProgramOptions;

// TODO: nix these, don't expose trace in the lib
  typedef struct {
    uint64_t TraceBegin,    // starting offset of trace output
             TraceEnd;      // ending offset of trace output
  } LG_ContextOptions;

  // Error handling
  typedef struct LG_Error {
    char* Message;
    char* Pattern;
    char* EncodingChain;
    char* Source;
    int Index;
    struct LG_Error* Next;
  } LG_Error;

  void lg_free_error(LG_Error* err);

  // Create and destory an LG_HPATTERN.
  // This can be reused when parsing pattern strings to avoid re-allocating memory.
  LG_HPATTERN lg_create_pattern();

  void lg_destroy_pattern(LG_HPATTERN hPattern);

  // Returns zero on failure, positive otherwise.
  int lg_parse_pattern(LG_HPATTERN hPattern,
                       const char* pattern,
                       const LG_KeyOptions* options,
                       LG_Error** err);

  // The parameter lets you pass a hint as to the size of the finite state
  // machine that will be created from the keywords. This is important if
  // there will be a lot of keywords, as it helps minimize heap allocation
  // and fragmentation. A good rule of thumb is to pass the total number of
  // characters in all of the keywords. Everything will work fine with 0,
  // though.
  LG_HFSM lg_create_fsm(unsigned int numFsmStateSizeHint);

  void lg_destroy_fsm(LG_HFSM hFsm);

  // Returns negative on failure; otherwise returns unique index for the
  // pattern-encoding pair.
  int lg_add_pattern(LG_HFSM hFsm,
                     LG_HPROGRAM hProg,
                     LG_HPATTERN hPattern,
                     const char* encoding,
                     uint64_t userIndex,
                     LG_Error** err);

  // Adds patterns to the FSM and Program. Each line of the pattern string
  // shall be formatted as tab separated columns:
  //
  //  pattern enc1,enc2,... fixedstring casesensitive asciimode
  //
  // where "pattern" is the pattern, "enc1,enc2,..." is a comma-separated
  // list of encodings, and "fixedstring", "casesensitive", and "asciimode"
  // are each 0 or 1 to set those options on or off. Any column except the
  // first (the pattern) may be omitted from any given line, on the condition
  // that every column to the right of the omitted column is also omitted.
  // The values of defaultEncodings and defaultOptions are used in case of
  // omitted columns. The "source" parameter indicates the source of the
  // patterns string (e.g., a path) and is used in error messages.
  int lg_add_pattern_list(LG_HFSM hFsm,
                          LG_HPROGRAM hProg,
                          const char* patterns,
                          const char* source,
                          const char** defaultEncodings,
                          unsigned int defaultEncodingsNum,
                          const LG_KeyOptions* defaultOptions,
                          LG_Error** err);

  // The number of pattern-encoding pairs recognized by the Program. This
  // will be one greater than the maximum pattern index accepted by
  // lg_pattern_info().
  unsigned int lg_pattern_count(const LG_HPROGRAM hProg);

  LG_PatternInfo* lg_pattern_info(LG_HPROGRAM hProg,
                                  unsigned int patternIndex);

  // Create an empty Program. The Program houses both the search logic and
  // the list of patterns against which hits may be reported.
  LG_HPROGRAM lg_create_program(unsigned int numTotalPatternsSizeHint);

  // Compile the FSM into the search logic held by a Program. Once a Program
  // has been compiled, it may no longer be altered and the FSM may be
  // discarded.
  int lg_compile_program(const LG_HFSM hFsm, LG_HPROGRAM hProg, const LG_ProgramOptions* options);

  // The size, in bytes, of the search program. Used for serialization.
  unsigned int lg_program_size(const LG_HPROGRAM hProg);

  // Serialize the program, in binary format, to a buffer. The buffer must be
  // at least as large as lg_program_size() in bytes.
  void lg_write_program(const LG_HPROGRAM hProg, void* buffer);

  // Convert a buffer containing a serialized program to a program, given the
  // binary buffer and size. No versioning check is done so don't keep these
  // around too long. The caller is responsible for freeing the buffer after
  // calling lg_destroy_program on the handle.
  LG_HPROGRAM lg_read_program(const void* buffer, int size);

  // A Program must live as long as any associated contexts,
  // so only call this at the end.
  void lg_destroy_program(LG_HPROGRAM hProg);

  // Create a "search context" from a program. Many search contexts can be
  // associated with a single program. A context lets you search a byte stream
  // and keeps track of the necessary state so that you can treat buffers as
  // contiguous. Uses a fixed amount of RAM.
  LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg,
                                const LG_ContextOptions* options);

  void lg_destroy_context(LG_HCONTEXT hCtx);

  // Finds matches beginning at the first byte. It works like lg_search(), but
  // neither lg_closeout_search() nor lg_reset() need to be called (these are
  // done automatically). Consequently, this function cannot be called in
  // succession for searching large streams. However, if there are multiple
  // matches beginning at byte 0, it will report on all of them. The function
  // can return early, without examining the entire buffer, if it gets to a
  // point where no further matches are possible.
  void lg_starts_with(LG_HCONTEXT hCtx,
                      const char* bufStart,
                      const char* bufEnd,
                      uint64_t startOffset,
                      void* userData,
                      LG_HITCALLBACK_FN callbackFn);

  // Reset the context to its initial state.
  // Call this before searching a new file.
  void lg_reset_context(LG_HCONTEXT hCtx);

  // Search a buffer. It assumes it's picking up where it left off, so you can
  // call this in a loop. When a hit is identified, the callback function will
  // be called, on the same stackframe, giving you the starting byte offset of
  // the hit, the end offset, and the keyword index of the associated keyword.
  // The context does not store or otherwise remember the buffer data you pass
  // it after this function returns, so do whatever you'd like with your
  // buffers after lg_search() returns. Return value is the least offset for
  // which a hit could still be returned by further searching.
  //
  // Search hits will be generated in increasing byte offset order BY KEYWORD
  // INDEX. Search hits pertaining to different keywords may be out of order.
  // In particular, it may not be possible to determine the full length of a
  // hit until the entire byte stream has been searched...
  uint64_t lg_search(LG_HCONTEXT hCtx,
                         const char* bufStart,
                         const char* bufEnd,   // pointer past the end of the buffer, i.e. bufEnd - bufStart == length of buffer
                         const uint64_t startOffset,   // Increment this with each call, by the length of the previous buffer. i.e., startOffset += bufEnd - bufStart;
                         void* userData,       // pass in what you like, it will be passed through to the callback function
                         LG_HITCALLBACK_FN callbackFn);

  // ...which is why it's important you call lg_closeout_search() when finished
  // searching a byte stream. This will flush out any remaining search hits.
  void lg_closeout_search(LG_HCONTEXT hCtx,
                          void* userData,
                          LG_HITCALLBACK_FN callbackFn);

  // Return value is the least offset for which a hit could still be returned
  // by further searching.
  uint64_t lg_search_resolve(LG_HCONTEXT hCtx,
                         const char* bufStart,
                         const char* bufEnd,
                         const uint64_t startOffset,
                         void* userData,
                         LG_HITCALLBACK_FN callbackFn);

#ifdef __cplusplus
}
#endif

#endif /* LIGHTGREP_C_API_H_ */
