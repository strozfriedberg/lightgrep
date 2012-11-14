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
#include "nfaoptimizer.h"
#include "handles.h"
#include "nfabuilder.h"
#include "parsetree.h"
#include "utility.h"
#include "vm_interface.h"
#include "compiler.h"
#include "program.h"

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
bool destroy_handle(H* h) {
  try {
    delete h;
    return true;
  }
  catch (...) {
    return false;
  }
}

template <class H>
H* create_handle() {
  try {
    return new H;
  }
  catch (...) {
    return 0;
  }
}

void create_parser_impl(LG_HPARSER hParser, unsigned int sizeHint) {
  hParser->Impl.reset(new Parser(sizeHint));
}

// TODO:
// * Review uses of exception_trap. We're likely using it in places where
// it's not necessary.

LG_HPARSER lg_create_parser(unsigned int sizeHint) {
  LG_HPARSER hParser = create_handle<ParserHandle>();
  if (!hParser) {
    return 0;
  }

  exception_trap(std::bind(&create_parser_impl, hParser, sizeHint));
  return hParser;
}

int lg_destroy_parser(LG_HPARSER hParser) {
  return destroy_handle(hParser);
}

int lg_add_keyword(LG_HPARSER hParser,
                   const char* keyword,
                   unsigned int keyIndex,
                   const LG_KeyOptions* options,
                   const char* encoding,
                   LG_Error** err)
{
  return lg_add_keyword_ex(hParser, keyword, keyIndex, options, &encoding, 1, err);
}

int lg_add_keyword_ex(LG_HPARSER hParser,
                   const char* keyword,
                   unsigned int keyIndex,
                   const LG_KeyOptions* options,
                   const char** encodings,
                   unsigned int encnum,
                   LG_Error** err)
{
// TODO: Adjust Pattern to take a list of encodings
// TODO: Adjust Parser::addPattern to constuct an encoder chain

  Pattern p(
    keyword,
    options->FixedString,
    options->CaseInsensitive,
    keyIndex,
    std::vector<std::string>(encodings, encodings+encnum)
  );
  return exception_trap(std::bind(&Parser::addPattern, hParser->Impl.get(), std::cref(p), keyIndex), err);
}

void create_program(LG_HPARSER hParser, LG_HPROGRAM hProg, bool determinize)
{
  NFAPtr& g(hParser->Impl->Fsm);

  if (g->verticesSize() < 2) {
    throw std::runtime_error("No valid patterns were parsed");
  }

  NFAOptimizer& comp(hParser->Impl->Comp);

  if (determinize && !g->Deterministic) {
    NFAPtr dfa(new NFA(1, 2 * g->verticesSize(), g->edgesSize()));
    dfa->TransFac = g->TransFac;
    comp.subsetDFA(*dfa, *g);
    g = dfa;
  }

  comp.labelGuardStates(*g);

  ProgramPtr& prog(hProg->Impl);

  prog = Compiler::createProgram(*g);
}

LG_HPROGRAM lg_create_program(LG_HPARSER hParser,
                              const LG_ProgramOptions* options)
{
  LG_HPROGRAM hProg = create_handle<ProgramHandle>();
  if (!hProg) {
    return 0;
  }
  exception_trap(std::bind(&create_program, hParser, hProg, options->Determinize));

  return hProg;
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
    return 0;
  }
  exception_trap(std::bind(&read_program, hProg, buffer, size));
  return hProg;
}

void lg_write_program(LG_HPROGRAM hProg, void* buffer) {
  exception_trap(std::bind(write_program, hProg, buffer));
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
    return 0;
  }

  const uint64
    begin = options ? options->TraceBegin : std::numeric_limits<uint64>::max(),
    end = options ? options->TraceEnd : std::numeric_limits<uint64>::max();

  exception_trap(std::bind(&create_context, hProg, hCtx, begin, end));
  return hCtx;
}

int lg_destroy_context(LG_HCONTEXT hCtx) {
  return destroy_handle(hCtx);
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
