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

#pragma once

#include "caching_encoder.h"
#include "encoderbase.h"

#include <string>

#include <unicode/ucnv.h>

class ICUEncoder: public EncoderBase {
public:
  ICUEncoder(const char* const name);
  ICUEncoder(const std::string& name);
  virtual ~ICUEncoder();

  virtual uint32 maxByteLength() const;

  virtual std::string name() const;

  virtual uint32 write(int cp, byte buf[]) const;
  using EncoderBase::write;

private:
  void init(const char* const name);

  std::string enc_name;
  UConverter* src_conv;
  UConverter* dst_conv;
  UChar* pivot;
  uint32 max_bytes;
};

class CachingICUEncoder: public CachingEncoder<ICUEncoder> {
public:
  CachingICUEncoder(const char* const name):
    CachingEncoder<ICUEncoder>({}, name) {}

  CachingICUEncoder(const std::string& name):
    CachingEncoder<ICUEncoder>({}, name) {}
};
