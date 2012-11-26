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

#include "icuutil.h"
#include "encoders/icuencoder.h"

#include <unicode/uset.h>

ICUEncoder::ICUEncoder(const char* const name):
  EncoderBase(),
  enc_name(name),
  src_conv{nullptr, nullptr},
  dst_conv{nullptr, nullptr}
{
  init(name);
}

ICUEncoder::ICUEncoder(const std::string& name):
  EncoderBase(),
  enc_name(name),
  src_conv{nullptr, nullptr},
  dst_conv{nullptr, nullptr}
{
  init(name.c_str());
}

ICUEncoder::ICUEncoder(const ICUEncoder& other): 
  EncoderBase(other),
  enc_name(other.enc_name),
  src_conv{nullptr, nullptr},
  dst_conv{nullptr, nullptr}
{
  init(other.enc_name.c_str());
}

ICUEncoder& ICUEncoder::operator=(const ICUEncoder& other) {
  EncoderBase::operator=(other);
  enc_name = other.enc_name;
  init(other.enc_name.c_str());
  return *this;
}

void ICUEncoder::init(const char* const name) {
  UErrorCode err = U_ZERO_ERROR;

  // ICU pivots through UTF-16 when transcoding; this converter is used
  // to turn our code points (single characters in UTF-32) into UTF-16.
  // We use the "PlatformEndian" version of UTF-32 so we don't have to
  // bother worrrying about endianness ourselves.
  src_conv = std::unique_ptr<UConverter,void(*)(UConverter*)>(
    ucnv_open("UTF32_PlatformEndian", &err),
    ucnv_close
  );
  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Your ICU is missing UTF32_PlatformEndian. WAT? " << u_errorName(err)
    );
  }

  // The pivot buffer used by ICU.
  pivot = std::unique_ptr<UChar[]>(
    new UChar[ucnv_getMaxCharSize(src_conv.get())]
  );

  // The converter used to translate UTF-16 into our desired encoding.
  dst_conv = std::unique_ptr<UConverter,void(*)(UConverter*)>(
    ucnv_open(name, &err),
    ucnv_close
  );
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
    dst_conv.get(),
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

  max_bytes =
    UCNV_GET_MAX_BYTES_FOR_STRING(1, ucnv_getMaxCharSize(dst_conv.get()));

  // get the set of valid code points
  std::unique_ptr<USet, void(*)(USet*)> us(uset_openEmpty(), uset_close);
  ucnv_getUnicodeSet(dst_conv.get(), us.get(), UCNV_ROUNDTRIP_SET, &err);
  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Could not get set of valid code points. WAT? " << u_errorName(err)
    );
  }

  convUnicodeSet(const_cast<UnicodeSet&>(Valid), us.get());
}

uint32_t ICUEncoder::maxByteLength() const { return max_bytes; }

std::string ICUEncoder::name() const { return enc_name; }

uint32_t ICUEncoder::write(int cp, byte buf[]) const {
  char* dst = reinterpret_cast<char*>(buf);
  const char* src = reinterpret_cast<const char*>(&cp);

  UChar* psrc = pivot.get();
  UChar* pdst = pivot.get();

  UErrorCode err = U_ZERO_ERROR;

  ucnv_convertEx(
    dst_conv.get(),
    src_conv.get(),
    &dst,
    dst + max_bytes,
    &src,
    src + sizeof(cp),
    pivot.get(),
    &psrc,
    &pdst,
    pivot.get() + sizeof(pivot.get()),
    true,
    false,
    &err
  );

  return U_FAILURE(err) ? 0 : dst - reinterpret_cast<char*>(buf);
}
