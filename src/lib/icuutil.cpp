#include "icuutil.h"

#include <memory>

void convUnicodeSet(UnicodeSet& dst, const USet* src) {
  UErrorCode err = U_ZERO_ERROR;

  // get the size of the data array
  const int32 len_dat = uset_serialize(src, nullptr, 0, &err);
  if (err != U_BUFFER_OVERFLOW_ERROR) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "uset_serialize failed: " << u_errorName(err)
    );
  }

  // allocate and fill the data array
  err = U_ZERO_ERROR;
  std::unique_ptr<uint16[]> dat(new uint16[len_dat]);
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
  dst.reset();
  int32 beg, end;
  const int32 rc = uset_getSerializedRangeCount(&uss);
  for (int32 i = 0; i < rc; ++i) {
    if (!uset_getSerializedRange(&uss, i, &beg, &end)) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Bad range index " << i << ", WTF?");
    }

    dst.insert(beg, end+1);
  }
}

void convUnicodeSet(USet* dst, const UnicodeSet& src) {
  uset_clear(dst);
  for (const UnicodeSet::range& r : src) {
    uset_addRange(dst, r.first, r.second-1);
  }
}
