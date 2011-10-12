#include "basic.h"

#include "lightgrep_c_api.h"

#include "graph.h"
#include "compiler.h"
#include "encodings.h"
#include "nfabuilder.h"
#include "parsetree.h"
#include "utility.h"
#include "vm_interface.h"

#include <cstring>
#include <iostream>
#include <sstream>

#include <boost/shared_ptr.hpp>

char Error[1024];

struct ParseContext {
  ParseTree   Tree;
  NFABuilder  Nfab;
  Compiler    Comp;
  GraphPtr    Fsm;

  ParseContext(unsigned int sizeHint): Fsm(new Graph(1, sizeHint)) {}
};

LG_HPARSER lg_create_parser(unsigned int sizeHint) {
  LG_HPARSER ret = 0;
  try {
    ret = new ParseContext(sizeHint);
  }
  catch (...) {
  }
  return ret;
}

void lg_destroy_parser(LG_HPARSER hParser) {
  delete reinterpret_cast<ParseContext*>(hParser);
}

int lg_add_keyword(LG_HPARSER hParser,
                   const char* keyword,
                   unsigned int keyIndex,
                   const LG_KeyOptions* options,
                   const char** error)
{
  try {
    ParseContext* pc = reinterpret_cast<ParseContext*>(hParser);

    addPattern(
      pc->Nfab,
      pc->Tree,
      pc->Comp,
      *pc->Fsm,
      keyword,
      keyIndex,
      options->CaseInsensitive == 0,
      options->FixedString != 0,
      options->Encoding
    );

    return 1;
  }
  catch (std::exception& e) {
    strcpy(Error, e.what());
  }
  catch (...) {
    strcpy(Error, "Unspecified exception");
  }

  *error = &Error[0];
  return 0;
}

LG_HPROGRAM lg_create_program(LG_HPARSER hParser,
                              const LG_ProgramOptions* options)
{
  LG_HPROGRAM prog = 0;
  try {
    ParseContext* pc = reinterpret_cast<ParseContext*>(hParser);

    GraphPtr& g(pc->Fsm);
    Compiler& comp(pc->Comp);

    std::cerr << g->numVertices() << " vertices" << std::endl;

    if (options->Determinize) {
      GraphPtr dfa(new Graph(1));
      comp.subsetDFA(*dfa, *g);
      g = dfa;

      std::cerr << g->numVertices() << " vertices" << std::endl;
    }

    comp.labelGuardStates(*g);

    std::cerr << g->numVertices() << " vertices" << std::endl;

    ProgramPtr* pp = new ProgramPtr;
    try {
      *pp = createProgram(*g);
      (*pp)->First = firstBytes(*g);
      prog = pp;

      std::cerr << (*pp)->size() << " instructions" << std::endl;
    }
    catch (...) {
      delete pp;
    }
  }
  catch (...) {}

  return prog;
}

void lg_destroy_program(LG_HPROGRAM hProg) {
  delete reinterpret_cast<ProgramPtr*>(hProg);
}

LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg) {
  LG_HCONTEXT ret = 0;
  try {
    boost::shared_ptr<VmInterface>* ctx = new boost::shared_ptr<VmInterface>;
    try {
      *ctx = VmInterface::create();
      (*ctx)->init(*reinterpret_cast<ProgramPtr*>(hProg));
      ret = ctx;
    }
    catch (...) {
      delete ctx;
    }
  }
  catch (...) {}

  return ret;
}

void lg_destroy_context(LG_HCONTEXT hCtx) {
  delete reinterpret_cast<boost::shared_ptr<VmInterface>*>(hCtx);
}

void lg_reset_context(LG_HCONTEXT hCtx) {
  (*reinterpret_cast<boost::shared_ptr<VmInterface>*>(hCtx))->reset();
}

void lg_starts_with(LG_HCONTEXT hCtx,
                   const char* bufStart,
                   const char* bufEnd,
                   uint64 startOffset,
                   void* userData,
                   LG_HITCALLBACK_FN callbackFn)
{
  (*reinterpret_cast<boost::shared_ptr<VmInterface>*>(hCtx))->startsWith((const byte*)bufStart, (const byte*)bufEnd, startOffset, *callbackFn, userData);
}

unsigned int lg_search(LG_HCONTEXT hCtx,
                         const char* bufStart,
                         const char* bufEnd,
                         const uint64 startOffset,
                         void* userData,
                         LG_HITCALLBACK_FN callbackFn)
{
  return (*reinterpret_cast<boost::shared_ptr<VmInterface>*>(hCtx))->search((const byte*)bufStart, (const byte*)bufEnd, startOffset, *callbackFn, userData);
}

void lg_closeout_search(LG_HCONTEXT hCtx,
                        void* userData,
                        LG_HITCALLBACK_FN callbackFn)
{
  (*reinterpret_cast<boost::shared_ptr<VmInterface>*>(hCtx))->closeOut(*callbackFn, userData);
}
