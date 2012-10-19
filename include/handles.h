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
#include "fwd_pointers.h"
#include "parser.h"
#include "vm_interface.h"

struct Handle {
  Handle() {
    // Reserving space makes it more likely that we can return
    // an error message on std::bad_alloc.
    Error.reserve(256);
  }

  virtual ~Handle() {}

  virtual bool ok() const = 0;
  virtual void destroy() = 0;
  const char* error() const { return Error.c_str(); }

  std::string Error;
};

template <typename T> struct HandleBase: public Handle {
  virtual bool ok() const { return static_cast<bool>(Impl); }
  virtual void destroy() { Impl.reset(); }

  std::unique_ptr<T> Impl;
};

struct ParserHandle: public HandleBase<Parser> {};

struct ProgramHandleImpl {
  ProgramHandleImpl();

  ProgramPtr Prog;
};

struct ProgramHandle: public HandleBase<ProgramHandleImpl> {};

struct ContextHandleImpl {
  ContextHandleImpl(): Vm(VmInterface::create()) {}

  std::shared_ptr<VmInterface> Vm;
};

struct ContextHandle: public HandleBase<ContextHandleImpl> {};
