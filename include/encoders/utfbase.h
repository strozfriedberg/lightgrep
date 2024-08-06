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

#include "encoders/encoderbase.h"

class UTFBase: public EncoderBase {
public:
  using EncoderBase::write;

protected:
  UTFBase(): EncoderBase(UnicodeSet{{0, 0xD800}, {0xE000, 0x110000}}) {}

  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32_t& l, uint32_t h, uint32_t len, uint32_t blimit) const = 0;

  virtual void writeRange(std::vector<std::vector<ByteSet>>& va, UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32_t& l, uint32_t& h, byte* cur, uint32_t len, uint32_t blimit) const;

  virtual void skipRange(UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32_t& l, uint32_t& h, uint32_t ubound) const;
};
