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

#include <memory>

#include "lightgrep/api.h"
#include "lightgrep/util.h"

#include "basic.h"
#include "fsmthingy.h"
#include "fwd_pointers.h"
#include "parser.h"
#include "parsetree.h"
#include "pattern_map.h"
#include "vm_interface.h"
#include "pattern.h"
#include "decoders/decoderfactory.h"

struct PatternHandle {
  Pattern   Pat;
  ParseTree Tree;
  Parser    TheParser;
};

struct PatternMapHandle {
  std::unique_ptr<PatternMap> Impl;
};

struct FSMHandle {
  std::unique_ptr<FSMThingy> Impl;
  std::shared_ptr<PatternMap> PMap;
};

struct ProgramHandle {
  ProgramPtr Prog;
  std::shared_ptr<PatternMap> PMap;
};

struct ContextHandle {
  std::shared_ptr<VmInterface> Impl;
};

struct DecoderHandle {
  DecoderFactory Factory;
};
