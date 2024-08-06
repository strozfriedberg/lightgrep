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
#include "icuconverter.h"

#include <memory>
#include <string>

class ICUEncoder: public EncoderBase {
public:
  ICUEncoder(const std::string& name);

  ICUEncoder(const ICUEncoder&) = default;

  ICUEncoder& operator=(const ICUEncoder&) = default;

  ICUEncoder(ICUEncoder&&) = default;

  ICUEncoder& operator=(ICUEncoder&&) = default;

  virtual ICUEncoder* clone() const { return new ICUEncoder(*this); }

  virtual uint32_t maxByteLength() const { return Conv.maxByteLength(); }

  virtual std::string name() const { return Conv.name(); }

  virtual uint32_t write(int32_t cp, byte buf[]) const;

  using EncoderBase::write;

  virtual uint32_t write(const byte buf[], int32_t& cp) const;

private:
  ICUConverter Conv;
};
