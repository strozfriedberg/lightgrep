/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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

#include "icuutil.h"
#include "icuconverter.h"

#include <unicode/uset.h>

ICUConverter::ICUConverter(const char* name):
  Name(name),
  bytes_conv{nullptr, nullptr},
  cp_conv{nullptr, nullptr}
{
  init();
}

ICUConverter::ICUConverter(const std::string& name):
  Name(name),
  bytes_conv{nullptr, nullptr},
  cp_conv{nullptr, nullptr}
{
  init();
}

ICUConverter::ICUConverter(const ICUConverter& other):
  Name(other.Name),
  bytes_conv{nullptr, nullptr},
  cp_conv{nullptr, nullptr}
{
  init();
}

ICUConverter& ICUConverter::operator=(const ICUConverter& other) {
  Name = other.Name;
  init();
  return *this;
}

std::unique_ptr<UConverter,void(*)(UConverter*)> make_conv(const char* name) {
  UErrorCode err = U_ZERO_ERROR;

  std::unique_ptr<UConverter,void(*)(UConverter*)> conv(
    ucnv_open(name, &err),
    ucnv_close
  );

  if (U_FAILURE(err)) {
    if (err == U_FILE_ACCESS_ERROR) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(
        "Unrecognized encoding '" << name << "'"
      );
    }
    else {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(
        "Unrecognized encoding '" << name << "': " << u_errorName(err)
      );
    }
  }
  return conv;
}

void ICUConverter::init() {
  // The converter used to translate from the encoding to UTF-16.
  bytes_conv = make_conv(Name.c_str());

  // ICU pivots through UTF-16 when transcoding; this converter is used
  // to translate between our code points (single characters in UTF-32)
  // and UTF-16. We use the "PlatformEndian" version of UTF-32 so we
  // don't have to bother worrrying about endianness ourselves.
  cp_conv = make_conv("UTF32_PlatformEndian");

  // The pivot buffers used by ICU.
  bytes_pivot = std::unique_ptr<UChar[]>(
    new UChar[ucnv_getMaxCharSize(bytes_conv.get())]
  );

  cp_pivot = std::unique_ptr<UChar[]>(
    new UChar[ucnv_getMaxCharSize(cp_conv.get())]
  );

  UErrorCode err = U_ZERO_ERROR;

  // Tell ICU to halt on code points unrepresentable in the byte encoding.
  ucnv_setFromUCallBack(
    bytes_conv.get(),
    UCNV_FROM_U_CALLBACK_STOP,
    nullptr,
    nullptr,
    nullptr,
    &err
  );

  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Could not set from callback. WAT? " << u_errorName(err)
    );
  }

  ucnv_setToUCallBack(
    bytes_conv.get(),
    UCNV_TO_U_CALLBACK_STOP,
    nullptr,
    nullptr,
    nullptr,
    &err
  );

  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Could not set to callback. WAT? " << u_errorName(err)
    );
  }

  max_bytes =
    UCNV_GET_MAX_BYTES_FOR_STRING(1, ucnv_getMaxCharSize(bytes_conv.get()));
}

UnicodeSet ICUConverter::validCodePoints() const {
  UErrorCode err = U_ZERO_ERROR;

  // get the set of valid code points
  std::unique_ptr<USet, void(*)(USet*)> us(uset_openEmpty(), uset_close);
  ucnv_getUnicodeSet(bytes_conv.get(), us.get(), UCNV_ROUNDTRIP_SET, &err);

  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Could not get set of valid code points. WAT? " << u_errorName(err)
    );
  }

  UnicodeSet valid;
  convUnicodeSet(valid, us.get());
  return valid;
}

size_t ICUConverter::bytes_to_cp(const byte* beg, const byte* end, int32_t& cp) const {
  if (beg == end) {
    return 0;
  }

  const char* src = reinterpret_cast<const char*>(beg);

  ucnv_resetToUnicode(bytes_conv.get());

  UErrorCode err = U_ZERO_ERROR;

  cp = ucnv_getNextUChar(
    bytes_conv.get(),
    &src,
    reinterpret_cast<const char*>(end),
    &err
  );

  if (U_FAILURE(err)) {
    return 0;
  }

  if (cp < 0xD800 || 0xE000 <= cp) {
    return src - reinterpret_cast<const char*>(beg);
  }
  else {
    // this is a UTF-16 surrogate, which is invalid
    return 0;
  }
}

size_t ICUConverter::cp_to_bytes(int32_t cp, byte buf[]) const {
  char* dst = reinterpret_cast<char*>(buf);
  const char* src = reinterpret_cast<const char*>(&cp);

  UChar* psrc = cp_pivot.get();
  UChar* pdst = psrc;

  UErrorCode err = U_ZERO_ERROR;

  ucnv_convertEx(
    bytes_conv.get(),
    cp_conv.get(),
    &dst,
    dst + max_bytes,
    &src,
    src + sizeof(cp),
    psrc,
    &psrc,
    &pdst,
    cp_pivot.get() + sizeof(cp_pivot.get()),
    true,
    false,
    &err
  );

  return U_FAILURE(err) ? 0 : dst - reinterpret_cast<char*>(buf);
}
