// Copyright 2011, Lightbox Technologies, Inc. All Rights Reserved.

#ifndef __ENCODINGS_H_
#define __ENCODINGS_H_

#ifdef __cplusplus
extern "C" {
#endif

static const int LG_ENC_ASCII = 0;
static const int LG_ENC_LATIN_1 = 1;
static const int LG_ENC_UTF_8 = 2;
static const int LG_ENC_UTF_16 = 3;

static const char* LG_SUPPORTED_ENCODINGS[] = {

// The Encoding specified in LG_KeyOptions MUST match one of the below strings (in ASCII)

  "US-ASCII",           // 0    aka ANSI_X3.4-1968, ASCII (as a special case, you can use any of the three)
  "ISO_8859-1:1987",    // 1    8859-1, aka Latin-1
  "UTF-8",              // 2
  "UTF-16"              // 3

};

#ifdef __cplusplus
}
#endif

#endif /* __ENCODINGS_H_ */
