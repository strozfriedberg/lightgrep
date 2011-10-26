#include "basic.h"

#include "lightgrep_c_api.h"

#include "graph.h"
#include "compiler.h"
#include "encodings.h"
#include "handles.h"
#include "nfabuilder.h"
#include "parsetree.h"
#include "utility.h"
#include "vm_interface.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

const char OH_SHIT[] = "Unspecified exception";

void paranoid_copy_error_string(std::string& err, const char* msg) {
  try {
    try {
      err = msg;
    }
    catch (const std::bad_alloc&) {
      // We don't have enough memory to copy the error string,
      // so copy up to the the capacity we already have.
      err.assign(msg, err.capacity());
    }
  }
  catch (...) {
    // This should be impossible.
  }
}

template <typename T> bool exception_trap(T func, Handle* h) {
  try {
    func();
    return true;
  }
  catch (const std::exception& e) {
    paranoid_copy_error_string(h->Error, e.what());
  }
  catch (...) {
    paranoid_copy_error_string(h->Error, OH_SHIT);
  }
  
  return false;
}

bool destroy_handle(Handle* h) {
  if (exception_trap(boost::bind(&Handle::destroy, h), h)) {
    try {
      delete h;
    }
    catch (...) {
    }

    return true;
  }
  else {
    return false;
  }
}

template <typename T> T* create_handle() {
  try {
    return new T;
  }
  catch (...) {
    return 0;
  }
}

int lg_ok(void* vp) {
  try {
    return vp && static_cast<Handle*>(vp)->ok();
  }
  catch (...) {
    return 0;
  }
}

const char* lg_error(void* vp) {
  try {
    return vp ? static_cast<Handle*>(vp)->error() : 0;
  }
  catch (...) {
    return 0;
  }
}

void create_parser_impl(LG_HPARSER hParser, unsigned int sizeHint) {
  hParser->Impl.reset(new ParserHandleImpl(sizeHint));
}

// TODO:
// 1. Should API functions return 0 or < 0 on failure? 0
// 2. Should all API functions return an error code?
// 3. How should we indicate that (outer) handle deletion failed?
// 4. ok() doesn't work, due to not resetting Impl on failure.
// 5. Could we use boost::thread_specific_ptr for returning error strings?
// 6. Use boost::thread_specific_ptr, get rid of inner handles.
// 7. Add doxygen docs for C API.

LG_HPARSER lg_create_parser(unsigned int sizeHint) {
  LG_HPARSER hParser = create_handle<ParserHandle>();
  if (!hParser) {
    return 0;
  }

  exception_trap(boost::bind(&create_parser_impl, hParser, sizeHint), hParser);
  return hParser;
}

int lg_destroy_parser(LG_HPARSER hParser) {
  return destroy_handle(hParser);
}

int lg_add_keyword(LG_HPARSER hParser,
                   const char* keyword,
                   unsigned int keyIndex,
                   const LG_KeyOptions* options)
{
  return exception_trap(boost::bind(&addPattern, boost::ref(hParser->Impl->Nfab), boost::ref(hParser->Impl->Tree), boost::ref(hParser->Impl->Comp), boost::ref(*hParser->Impl->Fsm), keyword, keyIndex, options->CaseInsensitive == 0, options->FixedString != 0, options->Encoding), hParser);
}

void create_program(LG_HPARSER hParser, LG_HPROGRAM hProg, bool determinize)
{
  GraphPtr& g(hParser->Impl->Fsm);

  if (g->numVertices() < 2) {
    throw std::runtime_error("No valid patterns were parsed");
  }

  Compiler& comp(hParser->Impl->Comp);

  if (determinize) {
    GraphPtr dfa(new Graph(1));
    comp.subsetDFA(*dfa, *g);
    g = dfa;
  }

  comp.labelGuardStates(*g);

  hProg->Impl.reset(new ProgramHandleImpl);
  ProgramPtr& prog(hProg->Impl->Prog);

  prog = createProgram(*g);
  prog->First = firstBytes(*g);
}

LG_HPROGRAM lg_create_program(LG_HPARSER hParser,
                              const LG_ProgramOptions* options)
{
  LG_HPROGRAM hProg = create_handle<ProgramHandle>();
  if (!hProg) {
    return 0;
  }

  exception_trap(boost::bind(&create_program, hParser, hProg, options->Determinize), hProg);

  return hProg;
}

int lg_destroy_program(LG_HPROGRAM hProg) {
  return destroy_handle(hProg);
}

void create_context(LG_HPROGRAM hProg, LG_HCONTEXT hCtx) {
  hCtx->Impl.reset(new ContextHandleImpl);
  hCtx->Impl->Vm->init(hProg->Impl->Prog);
}

LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg) {
  LG_HCONTEXT hCtx = create_handle<ContextHandle>();
  if (!hCtx) {
    return 0;
  }

  exception_trap(boost::bind(&create_context, hProg, hCtx), hCtx);

  return hCtx;
}

int lg_destroy_context(LG_HCONTEXT hCtx) {
  return destroy_handle(hCtx);
}

void lg_reset_context(LG_HCONTEXT hCtx) {
  exception_trap(boost::bind(&VmInterface::reset, hCtx->Impl->Vm), hCtx);
}

void lg_starts_with(LG_HCONTEXT hCtx,
                   const char* bufStart,
                   const char* bufEnd,
                   uint64 startOffset,
                   void* userData,
                   LG_HITCALLBACK_FN callbackFn)
{
  exception_trap(boost::bind(&VmInterface::startsWith, hCtx->Impl->Vm, (const byte*) bufStart, (const byte*) bufEnd, startOffset, *callbackFn, userData), hCtx);
}

unsigned int lg_search(LG_HCONTEXT hCtx,
                       const char* bufStart,
                       const char* bufEnd,
                       const uint64 startOffset,
                       void* userData,
                       LG_HITCALLBACK_FN callbackFn)
{
// FIXME: return Active[0]->Start

  exception_trap(boost::bind(&VmInterface::search, hCtx->Impl->Vm, (const byte*) bufStart, (const byte*) bufEnd, startOffset, *callbackFn, userData), hCtx);

  return 0;
}

void lg_closeout_search(LG_HCONTEXT hCtx,
                        void* userData,
                        LG_HITCALLBACK_FN callbackFn)
{
  exception_trap(boost::bind(&VmInterface::closeOut, hCtx->Impl->Vm, *callbackFn, userData), hCtx);

}
