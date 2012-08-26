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
