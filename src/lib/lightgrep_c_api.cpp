#include "basic.h"

#include "lightgrep_c_api.h"

#include "graph.h"
#include "compiler.h"
#include "nfabuilder.h"
#include "parser.h"
#include "parsetree.h"
#include "rewriter.h"
#include "utility.h"
#include "vm_interface.h"

#include <cstring>
#include <iostream>

char Error[1024];

struct ParseContext {
  ParseTree   Tree;
  NFABuilder  Nfab;
  Compiler    Comp;
  GraphPtr    Fsm;

  ParseContext(unsigned int sizeHint): Fsm(new Graph(1, sizeHint)) {}
};

class HitHandler: public HitCallback {
public:
  HitHandler(LG_HITCALLBACK_FN fn, void* userData): Fn(fn), UserData(userData) {}

  virtual void collect(const SearchHit& hit) {
    (*Fn)(UserData, &hit);
  }

private:
  LG_HITCALLBACK_FN Fn;
  void* UserData;
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
                   LG_KeyOptions* options,
                   const char** error)
{
  try {
    ParseContext* pc = reinterpret_cast<ParseContext*>(hParser);

    NFABuilder& nfab(pc->Nfab);
    ParseTree& tree(pc->Tree);
    Compiler& comp(pc->Comp);
    GraphPtr& g(pc->Fsm);

    // prepare the NFA builder
    nfab.reset();
    nfab.setCurLabel(keyIndex);
    nfab.setCaseSensitive(options->CaseInsensitive == 0);

    // parse the keyword
    std::string kw(keyword);
    if (parse(kw, options->FixedString != 0, tree)) {
      // rewrite the parse tree, if necessary
      bool rewritten = false;
      if (kw.find('?',1) != std::string::npos) {
        rewritten |= reduce_trailing_nongreedy_then_empty(tree.Root);
      }

      if (rewritten || kw.find('{',1) != std::string::npos) {
        reduce_empty_subtrees(tree.Root);
        reduce_useless_repetitions(tree.Root);
      }

      // build the NFA for this keyword
      if (nfab.build(tree)) {
        // and merge it into the greater NFA
        comp.pruneBranches(*nfab.getFsm());
        comp.mergeIntoFSM(*g, *nfab.getFsm());
        return 1;
      }
    }
    else {
      strcpy(Error, "Could not parse");
    }
  }
  catch (std::exception& e) {
    strcpy(Error, "Exception: ");
    strcat(Error, e.what());
  }
  catch (...) {
    strcpy(Error, "Unspecified exception");
  }

  *error = Error;
  return 0;
}

LG_HPROGRAM lg_create_program(LG_HPARSER hParser,
                              LG_ProgramOptions* options)
{
  LG_HPROGRAM prog = 0;
  try {
    ParseContext* pc = reinterpret_cast<ParseContext*>(hParser);

    GraphPtr g(pc->Fsm);
    Compiler& comp(pc->Comp);

    if (options->Determinize) {
      GraphPtr dfa(new Graph(1));
      comp.subsetDFA(*dfa, *g);
      g = dfa;
    }

    comp.labelGuardStates(*g);

    ProgramPtr* pp = new ProgramPtr;
    try {
      *pp = createProgram(*pc->Fsm);
      (*pp)->First = firstBytes(*pc->Fsm);
      prog = pp;
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
  HitHandler cb(callbackFn, userData);
  (*reinterpret_cast<boost::shared_ptr<VmInterface>*>(hCtx))->startsWith((const byte*)bufStart, (const byte*)bufEnd, startOffset, cb);
}

unsigned int lg_search(LG_HCONTEXT hCtx,
                         const char* bufStart,
                         const char* bufEnd,
                         uint64 startOffset,
                         void* userData,
                         LG_HITCALLBACK_FN callbackFn)
{
  HitHandler cb(callbackFn, userData);
  return (*reinterpret_cast<boost::shared_ptr<VmInterface>*>(hCtx))->search((const byte*)bufStart, (const byte*)bufEnd, startOffset, cb);
}

void lg_closeout_search(LG_HCONTEXT hCtx,
                        void* userData,
                        LG_HITCALLBACK_FN callbackFn)
{
  HitHandler cb(callbackFn, userData);
  (*reinterpret_cast<boost::shared_ptr<VmInterface>*>(hCtx))->closeOut(cb);
}
