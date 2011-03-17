#include "basic.h"

#include "lightgrep_c_api.h"

#include "graph.h"
#include "parser.h"
#include "compiler.h"
#include "utility.h"
#include "vm_interface.h"

#include <iostream>

struct ParseContext {
  SyntaxTree  Tree;
  Parser      P;
  Compiler    Comp;
  GraphPtr    Fsm;
};

class HitHandler: public HitCallback {
public:
  HitHandler(LG_HITCALLBACK_FN fn, void* userData): Fn(fn), UserData(userData) {}

  virtual void collect(const SearchHit& hit) {
    Hit.Start = hit.Offset;
    Hit.End = hit.Offset + hit.Length;
    Hit.KeywordIndex = hit.Label;
    (*Fn)(UserData, &Hit);
  }

private:
  LG_HITCALLBACK_FN Fn;
  void* UserData;
  LG_SearchHit Hit;
};

LG_HPARSER lg_create_parser(unsigned int) {
  return new ParseContext;
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
  ParseContext* pc = reinterpret_cast<ParseContext*>(hParser);
  pc->P.reset();
  pc->Tree.reset();
  pc->P.setCurLabel(keyIndex);
  pc->P.setCaseSensitive(options->CaseInsensitive == 0);
  std::string k(keyword);
  SyntaxTree tree;
  try {
    if (parse(k, options->FixedString != 0, pc->Tree, pc->P) && pc->P.good()) {
      if (pc->Fsm) {
        pc->Comp.mergeIntoFSM(*pc->Fsm, *pc->P.getFsm());
      }
      else {
        pc->Fsm = pc->P.getFsm();
        pc->P.resetFsm();
      }
      return 1;
    }
    else {
      *error = "Could not parse keyword";
    }
  }
  catch (std::exception& e) {
    *error = e.what();
  }
  catch (...) {
    *error = "Unspecified exception";
  }
  return 0;
}

LG_HPROGRAM lg_create_program(LG_HPARSER hParser,
                                LG_ProgramOptions* option)
{
  ParseContext* pc = reinterpret_cast<ParseContext*>(hParser);
  pc->Comp.labelGuardStates(*pc->Fsm);
  
  ProgramPtr *prog = new ProgramPtr;
  *prog = createProgram(*pc->Fsm);
  (*prog)->First = firstBytes(*pc->Fsm);
//  std::cerr << "program size is " << (*prog)->size() << std::endl;
//  std::cerr << **prog;
  return prog;
}

void lg_destroy_program(LG_HPROGRAM hProg) {
  ProgramPtr *prog = reinterpret_cast<ProgramPtr*>(hProg);
  delete prog;
}

LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg) {
  boost::shared_ptr<VmInterface> *ctx = new boost::shared_ptr<VmInterface>;
  *ctx = VmInterface::create();
  (*ctx)->init(*reinterpret_cast<ProgramPtr*>(hProg));
  return ctx;
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
