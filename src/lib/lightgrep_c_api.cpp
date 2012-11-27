/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "basic.h"

#include "lightgrep/api.h"

#include "automata.h"
#include "c_api_util.h"
#include "compiler.h"
#include "handles.h"
#include "nfabuilder.h"
#include "nfaoptimizer.h"
#include "parser.h"
#include "parsetree.h"
#include "program.h"
#include "utility.h"
#include "vm_interface.h"

#include <cstring>
#include <functional>
#include <iostream>
#include <vector>

namespace {
  template <typename F>
  bool exceptionTrap(F func) {
    try {
      func();
      return true;
    }
    catch (...) {
      return false;
    }
  }

  template <class H>
  H* createHandle() {
    try {
      return new H;
    }
    catch (...) {
      return nullptr;
    }
  }
}

void lg_free_error(LG_Error* err) {
  if (err) {
    delete err->Message;
  }
  delete err;
}

LG_HPATTERN lg_create_pattern() {
  return createHandle<PatternHandle>();
}

void lg_destroy_pattern(LG_HPATTERN hPattern) {
  delete hPattern;
}

// TODO:
// * Review uses of exceptionTrap. We're likely using it in places where
// it's not necessary.

int lg_parse_pattern(LG_HPATTERN hPattern,
                     const char* pattern,
                     const LG_KeyOptions* options,
                     LG_Error** err)
{
  // set up the pattern handle
  hPattern->Pat = {pattern, options->FixedString, options->CaseInsensitive};

  return trap_with_vals([hPattern](){ parseAndReduce(hPattern->Pat, hPattern->Tree); },
                        1,
                        0,
                        err);
}

LG_HPATTERNMAP lg_create_pattern_map(unsigned int numTotalPatternsSizeHint) {
  try {
    return new PatternMapHandle(numTotalPatternsSizeHint);
  }
  catch (...) {
    return nullptr;
  }
}

void lg_destroy_pattern_map(LG_HPATTERNMAP hPatternMap) {
  delete hPatternMap;
}

int lg_pattern_map_size(const LG_HPATTERNMAP hPatternMap) {
  return hPatternMap->Patterns.size();
}

LG_HFSM create_fsm(unsigned int numFsmStateSizeHint) {
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> hFsm(
    new FSMHandle,
    lg_destroy_fsm
  );

  hFsm->Impl.reset(new FSMThingy(numFsmStateSizeHint));
  return hFsm.release();
}

LG_HFSM lg_create_fsm(unsigned int numFsmStateSizeHint) {
  return trap_with_retval(
    [numFsmStateSizeHint](){ return create_fsm(numFsmStateSizeHint); },
    nullptr
  );
}

void lg_destroy_fsm(LG_HFSM hFsm) {
  delete hFsm;
}

int add_pattern(LG_HFSM hFsm, LG_HPATTERNMAP hMap, LG_HPATTERN hPattern, const char* encoding) {
  const uint32_t label = hMap->Patterns.size();
  hMap->addPattern(hPattern->Pat.Expression.c_str(), encoding);
  hFsm->Impl->addPattern(hPattern->Tree, encoding, label);
  return (int) label;
}

int lg_add_pattern(LG_HFSM hFsm,
                   LG_HPATTERNMAP hMap,
                   LG_HPATTERN hPattern,
                   const char* encoding,
                   LG_Error** err)
{
  return trap_with_retval(
    [hFsm,hMap,hPattern,encoding]() {
      return add_pattern(hFsm, hMap, hPattern, encoding);
    },
    -1,
    err
  );
}

LG_PatternInfo* lg_pattern_info(LG_HPATTERNMAP hMap,
                                unsigned int patternIndex)
{
  return &hMap->Patterns[patternIndex];
}

LG_HPROGRAM create_program(LG_HFSM hFsm, const LG_ProgramOptions* opts) {
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> hProg(
    new ProgramHandle,
    lg_destroy_program
  );

  hFsm->Impl->finalizeGraph(opts->Determinize);
  hProg->Impl = Compiler::createProgram(*hFsm->Impl->Fsm);

  return hProg.release();
}

LG_HPROGRAM lg_create_program(LG_HFSM hFsm,
                              const LG_ProgramOptions* options)
{
  return trap_with_retval(
    [hFsm,options](){ return create_program(hFsm, options); },
    nullptr
  );
}

void write_program(LG_HPROGRAM hProg, void* buffer) {
  std::string buf = hProg->Impl->marshall();
  std::memcpy(buffer, buf.data(), buf.size());
}

LG_HPROGRAM read_program(void* buffer, int size) {
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> hProg(
    new ProgramHandle,
    lg_destroy_program
  );

  std::string s(static_cast<char*>(buffer), size);
  hProg->Impl = Program::unmarshall(s);

  return hProg.release();
}

int lg_program_size(const LG_HPROGRAM hProg) {
  return hProg->Impl->bufSize();
}

LG_HPROGRAM lg_read_program(void* buffer, int size) {
  return trap_with_retval(
    [buffer,size](){ return read_program(buffer, size); },
    nullptr
  );
}

void lg_write_program(LG_HPROGRAM hProg, void* buffer) {
  exceptionTrap(std::bind(write_program, hProg, buffer));
}

void lg_destroy_program(LG_HPROGRAM hProg) {
  delete hProg;
}

LG_HCONTEXT create_context(LG_HPROGRAM hProg,
  #ifdef LBT_TRACE_ENABLED
                    uint64_t beginTrace, uint64_t endTrace
  #else
                    uint64_t, uint64_t
  #endif
  )
{
  std::unique_ptr<ContextHandle,void(*)(ContextHandle*)> hCtx(
    new ContextHandle,
    lg_destroy_context
  );

  hCtx->Impl = VmInterface::create();
  #ifdef LBT_TRACE_ENABLED
  hCtx->Impl->setDebugRange(beginTrace, endTrace);
  #endif
  hCtx->Impl->init(hProg->Impl);

  return hCtx.release();
}

LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg,
                              const LG_ContextOptions* options)
{
  const uint64_t
    begin = options ? options->TraceBegin : std::numeric_limits<uint64_t>::max(),
    end = options ? options->TraceEnd : std::numeric_limits<uint64_t>::max();

  return trap_with_retval(
    [hProg,begin,end](){ return create_context(hProg, begin, end); },
    nullptr
  );
}

void lg_destroy_context(LG_HCONTEXT hCtx) {
  delete hCtx;
}

void lg_reset_context(LG_HCONTEXT hCtx) {
  exceptionTrap(std::bind(&VmInterface::reset, hCtx->Impl));
}

void lg_starts_with(LG_HCONTEXT hCtx,
                   const char* bufStart,
                   const char* bufEnd,
                   uint64_t startOffset,
                   void* userData,
                   LG_HITCALLBACK_FN callbackFn)
{
  exceptionTrap(std::bind(&VmInterface::startsWith, hCtx->Impl, (const byte*) bufStart, (const byte*) bufEnd, startOffset, callbackFn, userData));
}

unsigned int lg_search(LG_HCONTEXT hCtx,
                       const char* bufStart,
                       const char* bufEnd,
                       const uint64_t startOffset,
                       void* userData,
                       LG_HITCALLBACK_FN callbackFn)
{
// FIXME: return Active[0]->Start

  exceptionTrap(std::bind(&VmInterface::search, hCtx->Impl, (const byte*) bufStart, (const byte*) bufEnd, startOffset, callbackFn, userData));

  return 0;
}

void lg_closeout_search(LG_HCONTEXT hCtx,
                        void* userData,
                        LG_HITCALLBACK_FN callbackFn)
{
  exceptionTrap(std::bind(&VmInterface::closeOut, hCtx->Impl, callbackFn, userData));
}
