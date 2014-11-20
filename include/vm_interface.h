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

#pragma once

#include "basic.h"
#include "fwd_pointers.h"
#include "searchhit.h"

class VmInterface {
public:
  virtual ~VmInterface() {}

  virtual void startsWith(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData) = 0;
  virtual uint64_t search(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData) = 0;
  virtual uint64_t searchResolve(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData) = 0;
  virtual void closeOut(HitCallback hitFn, void* userData) = 0;
  virtual void reset() = 0;

  #ifdef LBT_TRACE_ENABLED
  virtual void setDebugRange(uint64_t beg, uint64_t end) = 0;
  #endif

  static std::shared_ptr<VmInterface> create(ProgramPtr prog);
};
