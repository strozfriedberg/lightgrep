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

int lg_destroy_handle(Handle* h) {
  if (exception_trap(boost::bind(&Handle::destroy, h), h)) {
    try {
      delete h;
    }
    catch (...) {
    }

    return 1;
  }
  else {
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

LG_HPARSER lg_create_parser(unsigned int sizeHint) {
  LG_HPARSER hParser = 0;
  try {
    hParser = new ParserHandle;
  }
  catch (...) {
    return 0;
  }

  exception_trap(boost::bind(create_parser_impl, hParser, sizeHint), hParser);
  return hParser;
}

int lg_destroy_parser(LG_HPARSER hParser) {
  return lg_destroy_handle(hParser);
}

int lg_add_keyword(LG_HPARSER hParser,
                   const char* keyword,
                   unsigned int keyIndex,
                   const LG_KeyOptions* options)
{
  try {
    try {
      addPattern(
        hParser->Impl->Nfab,
        hParser->Impl->Tree,
        hParser->Impl->Comp,
        *hParser->Impl->Fsm,
        keyword,
        keyIndex,
        options->CaseInsensitive == 0,
        options->FixedString != 0,
        options->Encoding
      );

      return 1;
    }
    catch (std::exception& e) {
// FIXME: should distinguish exceptions which apply only to one keyword
// from those which leave parser in an unusable state

      hParser->Error = e.what();
    }
    catch (...) {
      hParser->Error = "Unspecified exception";
    }
  }
  catch (...) {
    // This is the unlikely case in which std::string::operator= threw.
    // We can't even set an error string here, just stop the exception
    // from propagating.
  }

  return 0;
}

LG_HPROGRAM lg_create_program(LG_HPARSER hParser,
                              const LG_ProgramOptions* options)
{
  LG_HPROGRAM hProg = 0;
  try {
    hProg = new ProgramHandle;
  }
  catch (...) {
    return 0;
  }

  try {
    try {
      GraphPtr& g(hParser->Impl->Fsm);
      Compiler& comp(hParser->Impl->Comp);

      if (g->numVertices() < 2) {
        throw std::runtime_error("Parser has no patterns");
      }

      if (options->Determinize) {
        GraphPtr dfa(new Graph(1));
        comp.subsetDFA(*dfa, *g);
        g = dfa;
      }

      comp.labelGuardStates(*g);

      hProg->Impl->Prog = createProgram(*g);
      hProg->Impl->Prog->First = firstBytes(*g);
    }
    catch (std::exception& e) {
      hProg->Error = e.what();
      hProg->Impl->Prog.reset();
    }
    catch (...) {
      hProg->Error = "Unspecified exception";
      hProg->Impl->Prog.reset();
    }

    return hProg;
  }
  catch (...) {
    try {
      delete hProg;
    }
    catch (...) {
    }

    return 0;
  }
}

int lg_destroy_program(LG_HPROGRAM hProg) {
  return lg_destroy_handle(hProg);
}

LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg) {
  LG_HCONTEXT hCtx = 0;
  try {
    hCtx = new ContextHandle;
  }
  catch (...) {
    return 0;
  }

  try {
    try {
      hCtx->Impl->Vm->init(hProg->Impl->Prog);
    }
    catch (std::exception& e) {
      hCtx->Error = e.what();
      hCtx->Impl->Vm.reset();
    }
    catch (...) {
      hCtx->Error = "Unspecified exception";
      hCtx->Impl->Vm.reset();
    }

    return hCtx;
  }
  catch (...) {
    try {
      delete hCtx;
    }
    catch (...) {
    }

    return 0;
  }
}

int lg_destroy_context(LG_HCONTEXT hCtx) {
  return lg_destroy_handle(hCtx);
}

void lg_reset_context(LG_HCONTEXT hCtx) {
  try {
    try {
      hCtx->Impl->Vm->reset();
    }
    catch (std::exception& e) {
      hCtx->Error = e.what();
    }
    catch (...) {
      hCtx->Error = "Unspecified exception";
    }
  }
  catch (...) {
  }
}

void lg_starts_with(LG_HCONTEXT hCtx,
                   const char* bufStart,
                   const char* bufEnd,
                   uint64 startOffset,
                   void* userData,
                   LG_HITCALLBACK_FN callbackFn)
{
  try {
    try {
      hCtx->Impl->Vm->startsWith(
        (const byte*) bufStart,
        (const byte*) bufEnd,
        startOffset,
        *callbackFn,
        userData
      );
    }
    catch (std::exception& e) {
      hCtx->Error = e.what();
    }
    catch (...) {
      hCtx->Error = "Unspecified exception";
    }
  }
  catch (...) {
  }
}

unsigned int lg_search(LG_HCONTEXT hCtx,
                       const char* bufStart,
                       const char* bufEnd,
                       const uint64 startOffset,
                       void* userData,
                       LG_HITCALLBACK_FN callbackFn)
{
  try {
    try {
      return hCtx->Impl->Vm->search(
        (const byte*) bufStart,
        (const byte*) bufEnd,
        startOffset,
        *callbackFn,
        userData
      );
    }
    catch (std::exception& e) {
      hCtx->Error = e.what();
    }
    catch(...) {
      hCtx->Error = "Unspecified exception";
    }
  }
  catch (...) {
  }

  return 0;
}

void lg_closeout_search(LG_HCONTEXT hCtx,
                        void* userData,
                        LG_HITCALLBACK_FN callbackFn)
{
  try {
    try {
      hCtx->Impl->Vm->closeOut(*callbackFn, userData);
    }
    catch (std::exception& e) {
      hCtx->Error = e.what();
    }
    catch (...) {
      hCtx->Error = "Unspecified exception";
    }
  }
  catch(...) {
  }
}
