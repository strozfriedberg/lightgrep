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

#include "lightgrep_c_api.h"

#include "automata.h"
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

void lg_free_error(LG_Error* err) {
  if (err) {
    delete err->Message;
  }
  delete err;
}

template <typename F>
bool exception_trap(F func) {
  try {
    func();
    return true;
  }
  catch (...) {
    return false;
  }
}

void fill_error(LG_Error** err, const char* msg) {
  if (err) {
    try {
     *err = new LG_Error;
     (*err)->Message = new char[std::strlen(msg)];
      std::strcpy((*err)->Message, msg);
    }
    catch (const std::bad_alloc&) {
      // Not enough memory to copy the error message. Everything is hosed.
    }
    catch (...) {
      // Should be impossible.
    }
  }
}

template <typename R, typename F>
R trap(F func, R succ, R fail, LG_Error** err) {
  try {
    func();
    return succ;
  }
  catch (const std::exception& e) {
    fill_error(err, e.what());
  }
  catch (...) {
    fill_error(err, "Unspecified exception");
  }

  return fail;
}

template <typename F>
bool exception_trap(F func, LG_Error** err) {
  try {
    func();
    return true;
  }
  catch (const std::exception& e) {
    fill_error(err, e.what());
  }
  catch (...) {
    fill_error(err, "Unspecified exception");
  }

  return false;
}

template <class H>
H* create_handle() {
  try {
    return new H;
  }
  catch (...) {
    return nullptr;
  }
}

// TODO:
// * Review uses of exception_trap. We're likely using it in places where
// it's not necessary.

LG_HPATTERN lg_parse_pattern(LG_HPATTERN hPattern,
                             const char* pattern,
                             const LG_KeyOptions* options,
                             LG_Error** err)
{
  // create a pattern handle if we're not given one
  if (!hPattern) {
    try {
      hPattern = new PatternHandle();
    }
    catch (...) {
      return nullptr;
    }
  }

  // set up the pattern handle
  hPattern->Expression = pattern;
  hPattern->FixedString = options->FixedString;
  hPattern->CaseInsensitive = options->CaseInsensitive;

  return trap(
    [hPattern](){
      parse_and_reduce(
        hPattern->Expression,
        hPattern->FixedString,
        hPattern->CaseInsensitive,
        hPattern->Tree
      );
    },
    hPattern,
    hPattern,
    err
  );
}

void lg_destroy_pattern(LG_HPATTERN hPattern) {
  delete hPattern;
}

LG_HPATTERNMAP lg_create_pattern_map(unsigned int numTotalPatternsSizeHint) {
// TODO: use the size hint
  try {
    return new PatternMapHandle();
  }
  catch (...) {
    return nullptr;
  }
}

void lg_destroy_pattern_map(LG_HPATTERNMAP hPatternMap) {
  delete hPatternMap;
}

LG_HFSM lg_create_fsm(unsigned int numFsmStateSizeHint) {
  try {
    return new FSMHandle{std::unique_ptr<FSMThingy>(new FSMThingy(numFsmStateSizeHint))};
  }
  catch (...) {
    return nullptr;
  }
}

void lg_destroy_fsm(LG_HFSM hFsm) {
  delete hFsm;
}

int lg_add_pattern(LG_HFSM hFsm,
                   LG_HPATTERNMAP hMap,
                   LG_HPATTERN hPattern,
                   const LG_EncodingChain* chain,
                   LG_Error** err)
{
  const uint32 index = hMap->Table.size();

  hMap->Patterns.push_back({
    hPattern->Expression.c_str(),
    chain,
    nullptr
  });
  hMap->Table.push_back(index);

  return trap(
    [hFsm,hPattern,chain,index](){
      hFsm->Impl->addPattern(hPattern->Tree, chain->CharByteEncoder, index);
    },
    (int) index,
    -1,
    err
  );
}

const LG_PatternInfo* lg_pattern_info(LG_HPATTERNMAP hMap,
                                      unsigned int patternIndex)
{
// TODO: exception trap
  return &hMap->Patterns[patternIndex];
}

void create_program(LG_HFSM hFsm, LG_HPROGRAM hProg, bool determinize)
{
  hFsm->Impl->finalizeGraph(determinize);
  hProg->Impl = Compiler::createProgram(*hFsm->Impl->Fsm);
}

LG_HPROGRAM lg_create_program(LG_HFSM hFsm,
                              const LG_ProgramOptions* options)
{
  LG_HPROGRAM hProg = create_handle<ProgramHandle>();
  if (!hProg) {
    return nullptr;
  }

// TODO: fix exception trap
  if (exception_trap(std::bind(&create_program, hFsm, hProg, options->Determinize))) {
    return hProg;
  }
  else {
    lg_destroy_program(hProg);
    return nullptr;
  }
}

void write_program(LG_HPROGRAM hProg, void* buffer) {
  std::string buf = hProg->Impl->marshall();
  std::memcpy(buffer, buf.data(), buf.size());
}

void read_program(LG_HPROGRAM hProg, void* buffer, int size) {
  std::string s((char*)buffer, size);
  hProg->Impl = Program::unmarshall(s);
}

int lg_program_size(LG_HPROGRAM hProg) {
  return hProg->Impl->bufSize();
}

LG_HPROGRAM lg_read_program(void* buffer, int size) {
  LG_HPROGRAM hProg = create_handle<ProgramHandle>();
  if (!hProg) {
    return nullptr;
  }
  exception_trap(std::bind(&read_program, hProg, buffer, size));
  return hProg;
}

void lg_write_program(LG_HPROGRAM hProg, void* buffer) {
  exception_trap(std::bind(write_program, hProg, buffer));
}

void lg_destroy_program(LG_HPROGRAM hProg) {
  delete hProg;
}

void create_context(LG_HPROGRAM hProg, LG_HCONTEXT hCtx,
  #ifdef LBT_TRACE_ENABLED
                    uint64 beginTrace, uint64 endTrace
  #else
                    uint64, uint64
  #endif
  )
{
  hCtx->Impl = VmInterface::create();
  #ifdef LBT_TRACE_ENABLED
  hCtx->Impl->setDebugRange(beginTrace, endTrace);
  #endif
  hCtx->Impl->init(hProg->Impl);
}

LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg,
                              const LG_ContextOptions* options)
{
  LG_HCONTEXT hCtx = create_handle<ContextHandle>();
  if (!hCtx) {
    return nullptr;
  }

  const uint64
    begin = options ? options->TraceBegin : std::numeric_limits<uint64>::max(),
    end = options ? options->TraceEnd : std::numeric_limits<uint64>::max();

  exception_trap(std::bind(&create_context, hProg, hCtx, begin, end));
  return hCtx;
}

void lg_destroy_context(LG_HCONTEXT hCtx) {
  delete hCtx;
}

void lg_reset_context(LG_HCONTEXT hCtx) {
  exception_trap(std::bind(&VmInterface::reset, hCtx->Impl));
}

void lg_starts_with(LG_HCONTEXT hCtx,
                   const char* bufStart,
                   const char* bufEnd,
                   uint64 startOffset,
                   void* userData,
                   LG_HITCALLBACK_FN callbackFn)
{
  exception_trap(std::bind(&VmInterface::startsWith, hCtx->Impl, (const byte*) bufStart, (const byte*) bufEnd, startOffset, callbackFn, userData));
}

unsigned int lg_search(LG_HCONTEXT hCtx,
                       const char* bufStart,
                       const char* bufEnd,
                       const uint64 startOffset,
                       void* userData,
                       LG_HITCALLBACK_FN callbackFn)
{
// FIXME: return Active[0]->Start

  exception_trap(std::bind(&VmInterface::search, hCtx->Impl, (const byte*) bufStart, (const byte*) bufEnd, startOffset, callbackFn, userData));

  return 0;
}

void lg_closeout_search(LG_HCONTEXT hCtx,
                        void* userData,
                        LG_HITCALLBACK_FN callbackFn)
{
  exception_trap(std::bind(&VmInterface::closeOut, hCtx->Impl, callbackFn, userData));
}
