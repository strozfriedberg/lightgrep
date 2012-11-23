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

#include "encoderbase.h"

#include <memory>
#include <string>

#include <unicode/ucnv.h>

class ICUEncoder: public EncoderBase {
public:
  ICUEncoder(const char* const name):
    EncoderBase(),
    enc_name(name),
    src_conv{nullptr, nullptr},
    dst_conv{nullptr, nullptr}
  {
    init(name);
  }

  ICUEncoder(const std::string& name):
    EncoderBase(),
    enc_name(name),
    src_conv{nullptr, nullptr},
    dst_conv{nullptr, nullptr}
  {
    init(name.c_str());
  }

  ICUEncoder(const ICUEncoder& other): 
    EncoderBase(other),
    enc_name(other.enc_name),
    src_conv{nullptr, nullptr},
    dst_conv{nullptr, nullptr}
  {
    init(other.enc_name.c_str());
  }

  ICUEncoder& operator=(const ICUEncoder& other) {
    EncoderBase::operator=(other);
    enc_name = other.enc_name;
    init(other.enc_name.c_str());
    return *this;
  }

  ICUEncoder(ICUEncoder&&) = default;

  ICUEncoder& operator=(ICUEncoder&&) = default;

  virtual ICUEncoder* clone() const { return new ICUEncoder(*this); }

  virtual uint32_t maxByteLength() const;

  virtual std::string name() const;

  virtual uint32_t write(int cp, byte buf[]) const;

  using EncoderBase::write;

private:
  void init(const char* const name);

  std::string enc_name;
  std::unique_ptr<UConverter,void(*)(UConverter*)> src_conv;
  std::unique_ptr<UConverter,void(*)(UConverter*)> dst_conv;
  std::unique_ptr<UChar[]> pivot;

  uint32_t max_bytes;
};
