#pragma once

#include <string>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "basic.h"
#include "compiler.h"
#include "graph.h"
#include "nfabuilder.h"
#include "parsetree.h"
#include "vm_interface.h"

struct Handle {
  Handle() {
    // Reserving space makes it more likely that we can return
    // an error message on std::bad_alloc.
    Error.reserve(256);
  }

  virtual bool ok() const = 0;
  virtual void destroy() = 0;
  const char* error() const { return Error.c_str(); }

  std::string Error;
};

template <typename T> struct HandleBase: public Handle {
  virtual bool ok() const { return Impl; }
  virtual void destroy() { Impl.reset(); }

  boost::scoped_ptr<T> Impl;
};

struct ParserHandleImpl {
  ParserHandleImpl(uint32 sizeHint): Fsm(new Graph(1, sizeHint)) {}

  ParseTree   Tree;
  NFABuilder  Nfab;
  Compiler    Comp;
  GraphPtr    Fsm;
};

struct ParserHandle: public HandleBase<ParserHandleImpl> {};

struct ProgramHandleImpl {
  ProgramHandleImpl(): Prog(new Program) {};

  ProgramPtr Prog;
};

struct ProgramHandle: public HandleBase<ProgramHandleImpl> {};

struct ContextHandleImpl {
  ContextHandleImpl(): Vm(VmInterface::create()) {}

  boost::shared_ptr<VmInterface> Vm;
};

struct ContextHandle: public HandleBase<ContextHandleImpl> {};

