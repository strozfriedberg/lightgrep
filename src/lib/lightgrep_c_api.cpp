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

#include <boost/shared_ptr.hpp>

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

LG_HPARSER lg_create_parser(unsigned int sizeHint) {
  try {
    return new ParserHandle(sizeHint);
  }
  catch (...) {
    return 0;
  }
}

void lg_destroy_parser(LG_HPARSER hParser) {
  try {
    delete hParser;
  }
  catch (...) {
    // We can't even report this, as the pointer is now invalid. Ha!
  }
}

int lg_add_keyword(LG_HPARSER hParser,
                   const char* keyword,
                   unsigned int keyIndex,
                   const LG_KeyOptions* options)
{
  try {
    try {
      addPattern(
        hParser->Nfab,
        hParser->Tree,
        hParser->Comp,
        *hParser->Fsm,
        keyword,
        keyIndex,
        options->CaseInsensitive == 0,
        options->FixedString != 0,
        options->Encoding
      );

      return 1;
    }
    catch (std::exception& e) {
      hParser->Error = e.what();
    }
    catch (...) {
      hParser->Error = "Unspecified exception";
    }
  }
  catch (...) {
    // This is the vanishingly unlikely case in which either
    // std::exception::what() or std::string::operator= threw.
    // We can't even set an error string here, just stop the
    // exception from propagating.
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
      GraphPtr& g(hParser->Fsm);
      Compiler& comp(hParser->Comp);

  // FIXME: should check here that the graph has >= 2 nodes

      if (options->Determinize) {
        GraphPtr dfa(new Graph(1));
        comp.subsetDFA(*dfa, *g);
        g = dfa;
      }

      comp.labelGuardStates(*g);

      hProg->Prog = createProgram(*g);
      hProg->Prog->First = firstBytes(*g);
    }
    catch (std::exception& e) {
      hProg->Error = e.what();
      hProg->Prog.reset();
    }
    catch (...) {
      hProg->Error = "Unspecified exception";
      hProg->Prog.reset();
    }
  }
  catch (...) {
  }

  return hProg;
}

void lg_destroy_program(LG_HPROGRAM hProg) {
  try {
    delete hProg;
  }
  catch (...) {
    // We can't even report this, as the pointer is now invalid. Ha!
  }
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
      hCtx->Vm->init(hProg->Prog);
    }
    catch (std::exception& e) {
      hCtx->Error = e.what();
      hCtx->Vm.reset();
    }
    catch (...) {
      hCtx->Error = "Unspecified exception";
      hCtx->Vm.reset();
    }
  }
  catch (...) {
    try {
      delete hCtx;
    }
    catch (...) {
    }

    return 0;
  }

  return hCtx;
}

void lg_destroy_context(LG_HCONTEXT hCtx) {
  try {
    delete hCtx;
  }
  catch (...) {
    // We can't even report this, as the pointer is now invalid. Ha!
  }
}

void lg_reset_context(LG_HCONTEXT hCtx) {
  try {
    try {
      hCtx->Vm->reset();
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
      hCtx->Vm->startsWith(
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
      return hCtx->Vm->search(
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
}

void lg_closeout_search(LG_HCONTEXT hCtx,
                        void* userData,
                        LG_HITCALLBACK_FN callbackFn)
{
  try {
    try {
      hCtx->Vm->closeOut(*callbackFn, userData);
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
