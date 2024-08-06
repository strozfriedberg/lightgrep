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

#include "icuutil.h"

#include <unicode/uset.h>

void addUnicodeSet(UnicodeSet& dst, const USet* src) {
  UErrorCode err = U_ZERO_ERROR;

  // get the size of the data array
  const int32_t len_dat = uset_serialize(src, nullptr, 0, &err);
  if (err != U_BUFFER_OVERFLOW_ERROR) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "uset_serialize failed: " << u_errorName(err)
    );
  }

  // allocate and fill the data array
  err = U_ZERO_ERROR;
  std::unique_ptr<uint16_t[]> dat(new uint16_t[len_dat]);
  uset_serialize(src, dat.get(), len_dat, &err);
  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "uset_serialize failed: " << u_errorName(err)
    );
  }

  // fill the USerializedSet with the data array
  USerializedSet uss;
  if (!uset_getSerializedSet(&uss, dat.get(), len_dat)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("Bad serialized array, WTF?");
  }

  // insert the ranges from the USerializedSet into the UnicodeSet
  int32_t beg, end;
  const int32_t rc = uset_getSerializedRangeCount(&uss);
  for (int32_t i = 0; i < rc; ++i) {
    if (!uset_getSerializedRange(&uss, i, &beg, &end)) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Bad range index " << i << ", WTF?");
    }

    dst.insert(beg, end+1);
  }
}

void convUnicodeSet(UnicodeSet& dst, const USet* src) {
  dst.reset();
  addUnicodeSet(dst, src);
}

void convUnicodeSet(USet* dst, const UnicodeSet& src) {
  uset_clear(dst);
  for (const UnicodeSet::range r : src) {
    uset_addRange(dst, r.first, r.second-1);
  }
}
