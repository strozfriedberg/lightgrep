// Copyright 2011, Lightbox Technologies, Inc. All Rights Reserved.

#ifndef __ENCODINGS_H_
#define __ENCODINGS_H_

#ifdef __cplusplus
extern "C" {
#endif

// FIXME: why not an enum?
static const int LG_ENC_ASCII    = 0;
static const int LG_ENC_UTF_8    = 1;
static const int LG_ENC_UTF_16LE = 2;
static const int LG_ENC_UTF_16BE = 3;
static const int LG_ENC_UTF_32LE = 4;
static const int LG_ENC_UTF_32BE = 5;

static const char* LG_SUPPORTED_ENCODINGS[] = {
// The encoding specified in LG_KeyOptions MUST be one of these ASCII strings:
  "ASCII",    // 0
  "UTF-8",    // 1
  "UTF-16LE", // 2
  "UTF-16BE", // 3
  "UTF-32LE", // 4
  "UTF-32BE"  // 5
};

#ifdef __cplusplus
}
#endif

#endif /* __ENCODINGS_H_ */
