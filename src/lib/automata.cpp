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

#include "automata.h"

#include <limits>

const uint32_t Glushkov::NOLABEL = std::numeric_limits<uint32_t>::max();

std::string Glushkov::label() const {
  std::ostringstream buf;
  if (Trans) {
    buf << Trans->label();
    if (Label != NOLABEL) {
      buf << "/" << Label;
    }
  }
  return buf.str();
}
