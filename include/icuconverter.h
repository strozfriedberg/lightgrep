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

#pragma once

#include "basic.h"
#include "rangeset.h"

#include <string>
#include <memory>

#include <unicode/ucnv.h>

class ICUConverter {
public:
  ICUConverter(const char* encname);

  ICUConverter(const std::string& encname);

  ICUConverter(const ICUConverter& other);

  ICUConverter& operator=(const ICUConverter& other);

  ICUConverter(ICUConverter&&) = default;

  ICUConverter& operator=(ICUConverter&&) = default;

  size_t maxByteLength() const { return max_bytes; }

  std::string name() const { return Name; }

  UnicodeSet validCodePoints() const;

  size_t bytes_to_cp(const byte* beg, const byte* end, int32_t& cp) const;

  size_t cp_to_bytes(int32_t cp, byte buf[]) const;

private:
  void init();

  std::string Name;

  size_t max_bytes;
  
  std::unique_ptr<UConverter,void(*)(UConverter*)> bytes_conv, cp_conv;
  std::unique_ptr<UChar[]> bytes_pivot, cp_pivot;
};
