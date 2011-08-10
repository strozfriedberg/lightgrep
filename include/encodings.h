// Copyright 2011, Lightbox Technologies, Inc. All Rights Reserved.

#ifndef ENCODINGS_H
#define ENCODINGS_H

#ifdef __cplusplus
extern "C" {
#endif

static const int LG_ENC_LATIN_1 = 0;
static const int LG_ENC_ASCII = 1;
static const int LG_UTF_8 = 2;
static const int LG_UTF_16 = 3;

const char* LG_SUPPORTED_ENCODINGS[] = {

// The Encoding specified in LG_KeyOptions MUST match one of the below strings (in ASCII)

  "ISO_8859-1:1987",    // 0    8859-1, aka Latin-1
  "ANSI_X3.4-1968",     // 1    aka good ol' ASCII, ANSI; yes, this is the formal IANA name
  "UTF-8",              // 2
  "UTF-16"              // 3

};

#ifdef __cplusplus
}
#endif

#endif
