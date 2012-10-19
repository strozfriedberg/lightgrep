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

#include "patterninfo.h"
#include "lightgrep_search_hit.h"

#include <iosfwd>
#include <string>
#include <vector>

struct HitCounterInfo {
  HitCounterInfo(): NumHits(0) {}

  virtual ~HitCounterInfo() {}

  uint64 NumHits;

  virtual void setPath(const std::string&) {}
};

void nullWriter(void* userData, const LG_SearchHit* const);

struct HitWriterInfo: public HitCounterInfo, PatternInfo {
  HitWriterInfo(std::ostream& outStream, const PatternInfo& pinfo):
                PatternInfo(pinfo), Out(outStream) {}

  std::ostream& Out;
};

void hitWriter(void* userData, const LG_SearchHit* const hit);

struct PathWriterInfo: public HitWriterInfo {
  PathWriterInfo(std::ostream& outStream,
                 const PatternInfo& pinfo):
                 HitWriterInfo(outStream, pinfo) {}

  std::string Path;

  virtual void setPath(const std::string& path) { Path = path; }
};

void pathWriter(void* userData, const LG_SearchHit* const hit);

