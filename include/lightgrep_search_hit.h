// Copyright 2012, Lightbox Technologies, Inc. All Rights Reserved.

#ifndef LIGHTGREP_C_SEARCH_HIT_H_
#define LIGHTGREP_C_SEARCH_HIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef uint64
  typedef unsigned long long uint64;
#endif
#ifndef uint32
  typedef unsigned int uint32;
#endif


// Basic Search Hit struct

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


#ifdef __cplusplus
}
#endif

#endif /* LIGHTGREP_C_SEARCH_HIT_H_ */
