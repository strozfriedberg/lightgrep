#include "icuencoder.h"
#include "icuutil.h"

#include <unicode/uset.h>

// FIXME: Maybe we should set endianness with a compile-time flag? This
// would let us do the fast thing (casting & assignment) for conversions
// from code points to UTF-16 and UTF-32, instead of assigning each byte
// individually, in the case where our architecture and the encoding are
// same-endian.
bool is_little_endian() {
  const uint16_t twobytes = 1;
  return reinterpret_cast<const byte*>(&twobytes)[0];
}

ICUEncoder::ICUEncoder(const char* const name): enc_name(name) {
  UErrorCode err = U_ZERO_ERROR;

  // ICU pivots through UTF-16 when transcoding; this converter is used
  // to turn our code points (single characters in UTF-32) into UTF-16.
  src_conv = ucnv_open(is_little_endian() ? "UTF-32LE" : "UTF-32BE", &err);
  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Your ICU is missing UTF-32. WAT? " << u_errorName(err)
    );
  }

  // The pivot buffer used by ICU.
  pivot = new UChar[ucnv_getMaxCharSize(src_conv)];

  // The converter used to translate UTF-16 into our desired encoding.
  dst_conv = ucnv_open(name, &err);
  if (U_FAILURE(err)) {
    if (err == U_FILE_ACCESS_ERROR) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Unrecognized encoding '" << name << "'");
    }
    else {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(
        "Unrecognized encoding '" << name << "': " << u_errorName(err)
      );
    }
  }

  // Tell ICU to halt conversion on code points unrepresentable in the
  // target encoding.
  ucnv_setFromUCallBack(
    dst_conv,
    UCNV_FROM_U_CALLBACK_STOP,
    nullptr,
    nullptr,
    nullptr,
    &err
  );

  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Could not set callback. WAT? " << u_errorName(err)
    );
  }

  max_bytes = UCNV_GET_MAX_BYTES_FOR_STRING(1, ucnv_getMaxCharSize(dst_conv));

  // get the set of valid code points
  std::unique_ptr<USet, void(*)(USet*)> us(uset_openEmpty(), uset_close);
  ucnv_getUnicodeSet(dst_conv, us.get(), UCNV_ROUNDTRIP_SET, &err);
  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Could not get set of valid code points. WAT? " << u_errorName(err)
    );
  }

  convUnicodeSet(const_cast<UnicodeSet&>(Valid), us.get());
}

ICUEncoder::ICUEncoder(const std::string& name): ICUEncoder(name.c_str()) {}

ICUEncoder::~ICUEncoder() {
  ucnv_close(src_conv);
  ucnv_close(dst_conv);
  delete[] pivot;
}

uint32 ICUEncoder::maxByteLength() const { return max_bytes; }

std::string ICUEncoder::name() const { return enc_name; }

uint32 ICUEncoder::write(int cp, byte buf[]) const {
  char* dst = reinterpret_cast<char*>(buf);
  const char* src = reinterpret_cast<const char*>(&cp);

  UChar* psrc = pivot;
  UChar* pdst = pivot;

  UErrorCode err = U_ZERO_ERROR;

  ucnv_convertEx(
    dst_conv,
    src_conv,
    &dst,
    dst + max_bytes,
    &src,
    src + sizeof(cp),
    pivot,
    &psrc,
    &pdst,
    pivot + sizeof(pivot),
    true,
    false,
    &err
  );

  return U_FAILURE(err) ? 0 : dst - reinterpret_cast<char*>(buf);
}
