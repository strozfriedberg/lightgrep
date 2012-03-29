#include "basic.h"

#include "lightgrep_c_api.h"

#include "automata.h"
#include "compiler.h"
#include "handles.h"
#include "nfabuilder.h"
#include "parsetree.h"
#include "utility.h"
#include "vm_interface.h"

#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

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
  if (exception_trap(std::bind(&Handle::destroy, h), h)) {
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
  hParser->Impl.reset(new Parser(sizeHint));
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

  exception_trap(std::bind(&create_parser_impl, hParser, sizeHint), hParser);
  return hParser;
}

int lg_destroy_parser(LG_HPARSER hParser) {
  return destroy_handle(hParser);
}

int lg_add_keyword(LG_HPARSER hParser,
                   const char* keyword,
                   size_t length,
                   unsigned int keyIndex,
                   const LG_KeyOptions* options,
                   const char* encoding)
{
  Pattern p(
    std::string(keyword, 0, length),
    options->FixedString,
    options->CaseInsensitive,
    keyIndex,
    encoding
  );
  return exception_trap(std::bind(&Parser::addPattern, hParser->Impl.get(), std::cref(p), keyIndex), hParser);
}

void create_program(LG_HPARSER hParser, LG_HPROGRAM hProg, bool determinize)
{
  NFAPtr& g(hParser->Impl->Fsm);

  if (g->verticesSize() < 2) {
    throw std::runtime_error("No valid patterns were parsed");
  }

  Compiler& comp(hParser->Impl->Comp);

  if (determinize && !g->Deterministic) {
    NFAPtr dfa(new NFA(1));
    dfa->TransFac = g->TransFac;
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

  exception_trap(std::bind(&create_program, hParser, hProg, options->Determinize), hProg);

  return hProg;
}

int lg_destroy_program(LG_HPROGRAM hProg) {
  return destroy_handle(hProg);
}

void create_context(LG_HPROGRAM hProg, LG_HCONTEXT hCtx,
  #ifdef LBT_TRACE_ENABLED
                    uint64 beginTrace, uint64 endTrace
  #else
                    uint64, uint64
  #endif
  )
{
  hCtx->Impl.reset(new ContextHandleImpl);
  #ifdef LBT_TRACE_ENABLED
  hCtx->Impl->Vm->setDebugRange(beginTrace, endTrace);
  #endif
  hCtx->Impl->Vm->init(hProg->Impl->Prog);
}

LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg,
                              const LG_ContextOptions* options)
{
  LG_HCONTEXT hCtx = create_handle<ContextHandle>();
  if (!hCtx) {
    return 0;
  }

  exception_trap(std::bind(&create_context, hProg, hCtx, options->TraceBegin, options->TraceEnd), hCtx);

  return hCtx;
}

int lg_destroy_context(LG_HCONTEXT hCtx) {
  return destroy_handle(hCtx);
}

void lg_reset_context(LG_HCONTEXT hCtx) {
  exception_trap(std::bind(&VmInterface::reset, hCtx->Impl->Vm), hCtx);
}

void lg_starts_with(LG_HCONTEXT hCtx,
                   const char* bufStart,
                   const char* bufEnd,
                   uint64 startOffset,
                   void* userData,
                   LG_HITCALLBACK_FN callbackFn)
{
  exception_trap(std::bind(&VmInterface::startsWith, hCtx->Impl->Vm, (const byte*) bufStart, (const byte*) bufEnd, startOffset, callbackFn, userData), hCtx);
}

unsigned int lg_search(LG_HCONTEXT hCtx,
                       const char* bufStart,
                       const char* bufEnd,
                       const uint64 startOffset,
                       void* userData,
                       LG_HITCALLBACK_FN callbackFn)
{
// FIXME: return Active[0]->Start

  exception_trap(std::bind(&VmInterface::search, hCtx->Impl->Vm, (const byte*) bufStart, (const byte*) bufEnd, startOffset, callbackFn, userData), hCtx);

  return 0;
}

void lg_closeout_search(LG_HCONTEXT hCtx,
                        void* userData,
                        LG_HITCALLBACK_FN callbackFn)
{
  exception_trap(std::bind(&VmInterface::closeOut, hCtx->Impl->Vm, callbackFn, userData), hCtx);

}
