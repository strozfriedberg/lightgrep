#pragma once

#include <string>

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
  virtual const char* error() const { return Error.c_str(); }

  std::string Error;
};

struct ParserHandle: public Handle {
  ParserHandle(uint32 sizeHint): Fsm(new Graph(1, sizeHint)) {}

  virtual bool ok() const { return Fsm; }

  ParseTree   Tree;
  NFABuilder  Nfab;
  Compiler    Comp;
  GraphPtr    Fsm;
};

struct ProgramHandle: public Handle {
  virtual bool ok() const {
    return Prog;
  }

  ProgramPtr Prog;
};

struct ContextHandle: public Handle {
  ContextHandle(): Vm(VmInterface::create()) {}

  virtual bool ok() const {
    return Vm;
  }

  boost::shared_ptr<VmInterface> Vm;
};
