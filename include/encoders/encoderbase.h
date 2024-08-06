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


#pragma once

#include "encoders/encoder.h"

class EncoderBase: public Encoder {
public:
  virtual const UnicodeSet& validCodePoints() const { return Valid; };

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& v) const;

  using Encoder::write;

protected:
  EncoderBase(): Valid() {}

  EncoderBase(UnicodeSet&& valid): Valid(std::forward<UnicodeSet>(valid)) {}

  EncoderBase(const EncoderBase&) = default;

  EncoderBase(EncoderBase&&) = default;

  EncoderBase& operator=(const EncoderBase&) = default;

  EncoderBase& operator=(EncoderBase&&) = default;

  virtual void collectRanges(const UnicodeSet& user, std::vector<std::vector<ByteSet>>& v) const;

  UnicodeSet Valid;
};
