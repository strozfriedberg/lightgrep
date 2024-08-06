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

#include "encoders/icuencoder.h"

ICUEncoder::ICUEncoder(const std::string& name):
  EncoderBase(),
  Conv(name)
{
  Valid = Conv.validCodePoints();
}

uint32_t ICUEncoder::write(int32_t cp, byte buf[]) const {
  return Conv.cp_to_bytes(cp, buf);
}

uint32_t ICUEncoder::write(const byte [], int32_t&) const {
// TODO: fill this in
  return 0;
}
