// Copyright 2011, Lightbox Technologies, Inc. All Rights Reserved.

#ifndef __LIGHTGREP_C_API_H_
#define __LIGHTGREP_C_API_H_

// for size_t
#ifdef __cplusplus
#include <cstring>
#else
#include <string.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef uint64
  typedef unsigned long long uint64;
#endif
#ifndef uint32
  typedef unsigned int uint32;
#endif

  struct ParserHandle;
  struct ProgramHandle;
  struct ContextHandle;

  typedef struct ParserHandle*  LG_HPARSER;
  typedef struct ProgramHandle* LG_HPROGRAM;
  typedef struct ContextHandle* LG_HCONTEXT;

  typedef struct {
    char FixedString;     // 0 => grep, non-zero => fixed-string
    char CaseInsensitive; // 0 => case sensitive, non-zero => case-insensitive
  } LG_KeyOptions;

  typedef struct {
    char Determinize;     // 0 => build NFA, non-zero => build (pseudo)DFA
  } LG_ProgramOptions;

  typedef struct {
    uint64 TraceBegin,    // starting offset of trace output
           TraceEnd;      // ending offset of trace output
  } LG_ContextOptions;

  typedef struct {
    uint64  Start,        // starting offset of the hit
            End;          // one past the hit, i.e., End - Start = Length
    uint32  KeywordIndex; // index of keyword that hit
  } LG_SearchHit;

  // function you specify to handle the search hit, e.g.,
  // void gotASearchHit(void* userData, const LG_SearchHit const* hit) {
  //   print("hit at %d, ending %d, on keyword %d",
  //         hit->Start, hit->End, hit->KeywordIndex);
  // }
  typedef void (*LG_HITCALLBACK_FN)(void* userData, const LG_SearchHit* const hit);

  int lg_ok(void* handle);

  const char* lg_error(void* handle);

  // Returns a handle to a parser for assembling all the keywords you'd like
  // to search for. The parameter lets you pass a hint as to the size of the
  // finite state machine that will be created from the keywords. This is
  // important if there will be a lot of keywords, as it helps minimize heap
  // allocation and fragmentation. A good rule of thumb is to pass the total
  // number of characters in all of the keywords. Everything will work fine
  // with 0, though.
  LG_HPARSER lg_create_parser(unsigned int numFsmStateSizeHint);

  // Frees all RAM associated with parsing the keywords.
  // Can, and should, be called after creating an LG_HPROGRAM.
  int lg_destroy_parser(LG_HPARSER hParser);

  // Parse a keyword and add it to the set of keywords associated with the
  // parser. Returns 1 on success, 0 if there was a parsing error.
  int lg_add_keyword(
    LG_HPARSER hParser,
    const char* keyword,           // the expression to search for, in UTF-8
    size_t length,                 // the length of the keyword, in bytes
    unsigned int keyIndex,         // unique for this keyword
    const LG_KeyOptions* options,  // parsing options
    const char* Encoding           // Encoding of keyword to search for, using
    // IANA names c.f. http://www.iana.org/assignments/character-sets
    // encodings.h has the list of supported encodings
  );

  // Create a "Program" from a parser, which efficiently encodes the logic for
  // recognizing all the specified keywords. Once a program has been created,
  // the parser can be discarded.
  LG_HPROGRAM lg_create_program(LG_HPARSER hParser,
                                const LG_ProgramOptions* options);

  // The size, in bytes, of the search program. Used for serialization.
  int lg_program_size(LG_HPROGRAM hProg);

  // Serialize the program, in binary format, to a buffer. The buffer must be
  // at least as large as lg_program_size() in bytes.
  void lg_write_program(void* buffer);

  // Read in a serialized program, given the binary buffer and size. No
  // versioning check is done so don't keep these around too long.
  LG_HPROGRAM lg_read_program(void* buffer, int size);

  // A Program must live as long as any associated contexts,
  // so only call this at the end.
  int lg_destroy_program(LG_HPROGRAM hProg);

  // Create a "search context" from a program. Many search contexts can be
  // associated with a single program. A context lets you search a byte stream
  // and keeps track of the necessary state so that you can treat buffers as
  // contiguous. Uses a fixed amount of RAM.
  LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg,
                                const LG_ContextOptions* options);
  int lg_destroy_context(LG_HCONTEXT hCtx);

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
                      uint64 startOffset,
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
  // buffers after lg_search() returns. Search hits will be generated in
  // increasing byte offset order BY KEYWORD INDEX. Search hits pertaining to
  // different keywords may be out of order. In particular, it may not be
  // possible to determine the full length of a hit until the entire byte
  // stream has been searched...
  unsigned int lg_search(LG_HCONTEXT hCtx,
                         const char* bufStart,
                         const char* bufEnd,   // pointer past the end of the buffer, i.e. bufEnd - bufStart == length of buffer
                         const uint64 startOffset,   // Increment this with each call, by the length of the previous buffer. i.e., startOffset += bufEnd - bufStart;
                         void* userData,       // pass in what you like, it will be passed through to the callback function
                         LG_HITCALLBACK_FN callbackFn);

  // ...which is why it's important you call lg_closeout_search() when finished
  // searching a byte stream. This will flush out any remaining search hits.
  void lg_closeout_search(LG_HCONTEXT hCtx,
                          void* userData,
                          LG_HITCALLBACK_FN callbackFn);

#ifdef __cplusplus
}
#endif

#endif /* __LIGHTGREP_C_API_H_ */
