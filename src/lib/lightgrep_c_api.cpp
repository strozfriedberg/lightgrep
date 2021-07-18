/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

namespace {
  template <typename F>
  bool exceptionTrap(F&& func) {
    try {
      func();
      return true;
    }
    catch (...) {
      return false;
    }
  }
}

void lg_free_error(LG_Error* err) {
  while (err) {
    LG_Error* next = err->Next;
    delete[] err->Pattern;
    delete[] err->EncodingChain;
    delete[] err->Message;
    delete[] err->Source;
    delete err;
    err = next;
  }
}

LG_HPATTERN lg_create_pattern() {
  return new (std::nothrow) PatternHandle;
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
  hPattern->Pat = {
    pattern,
    static_cast<bool>(options->FixedString),
    static_cast<bool>(options->CaseInsensitive),
    static_cast<bool>(options->UnicodeMode)
  };

  return trapWithVals(
    [hPattern](){ parseAndReduce(hPattern->Pat, hPattern->Tree); },
    1, 0, err
  );
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
  return trapWithRetval(
    [numFsmStateSizeHint](){ return create_fsm(numFsmStateSizeHint); },
    nullptr
  );
}

void lg_destroy_fsm(LG_HFSM hFsm) {
  delete hFsm;
}

namespace {
  int addPattern(LG_HFSM hFsm, LG_HPROGRAM hProg, LG_HPATTERN hPattern, const char* encoding, uint64_t userIndex) {
    const uint32_t label = hProg->PMap->Patterns.size();
    hFsm->Impl->addPattern(hPattern->Tree, encoding, label);
    hProg->PMap->addPattern(hPattern->Pat.Expression.c_str(), encoding, userIndex);
    return (int) label;
  }
}

int lg_add_pattern(LG_HFSM hFsm,
                   LG_HPROGRAM hProg,
                   LG_HPATTERN hPattern,
                   const char* encoding,
                   uint64_t userIndex,
                   LG_Error** err)
{
  return trapWithRetval(
    [hFsm, hProg, hPattern, encoding, userIndex]() {
      return addPattern(hFsm, hProg, hPattern, encoding, userIndex);
    },
    -1,
    err
  );
}

namespace {
  template <class E>
  void addPattern(LG_HFSM hFsm,
                  LG_HPROGRAM hProg,
                  LG_HPATTERN hPat,
                  const std::string& pat,
                  LG_KeyOptions* keyOpts,
                  const E& encodings,
                  int lnum,
                  LG_Error**& err)
  {
    lg_parse_pattern(hPat, pat.c_str(), keyOpts, err);
    if (*err) {
      (*err)->Index = lnum;
      err = &((*err)->Next);
      return;
    }

    for (const std::string& enc : encodings) {
      lg_add_pattern(hFsm, hProg, hPat, enc.c_str(), lnum, err);
      if (*err) {
        (*err)->Index = lnum;
        err = &((*err)->Next);
        continue;
      }
    }
  }

  int addPatternList(LG_HFSM hFsm,
                     LG_HPROGRAM hProg,
                     const char* patterns,
                     const char* source,
                     const char** defaultEncodings,
                     size_t defaultEncodingsNum,
                     const LG_KeyOptions* defaultOptions,
                     LG_Error** err)
  {
    std::unique_ptr<PatternHandle,void(*)(PatternHandle*)> ph(
      lg_create_pattern(),
      lg_destroy_pattern
    );

    const std::vector<std::string> defEncs(
      defaultEncodings, defaultEncodings + defaultEncodingsNum
    );

    typedef boost::char_separator<char> char_separator;
    typedef boost::tokenizer<char_separator, const char*> cstr_tokenizer;
    typedef boost::tokenizer<char_separator> tokenizer;

    // read each pattern line
    const cstr_tokenizer ltok(
      patterns, patterns + std::strlen(patterns), char_separator("\n")
    );

    cstr_tokenizer::const_iterator lcur(ltok.begin());
    const cstr_tokenizer::const_iterator lend(ltok.end());
    for (int lnum = 0; lcur != lend; ++lcur, ++lnum) {
      // split each pattern line into columns
      const tokenizer ctok(*lcur, char_separator("\t"));
      tokenizer::const_iterator ccur(ctok.begin());
      const tokenizer::const_iterator cend(ctok.end());

      if (ccur == cend) { // FIXME: is this possible?
        if (err) {
          *err = makeError("no pattern", nullptr, nullptr, source, lnum);
          err = &((*err)->Next);
        }
        continue;
      }

      // read the pattern
      const std::string pat(*ccur);

      LG_KeyOptions opts(*defaultOptions);

      if (++ccur != cend) {
        // read the encoding list
        const std::string el(*ccur);
        const tokenizer etok(el, char_separator(","));

        if (etok.begin() == etok.end()) {
          if (err) {
            *err = makeError(
              "no encoding list",
              pat.c_str(), nullptr, source, lnum
            );
            err = &((*err)->Next);
          }
          continue;
        }

        // read the options
        if (++ccur != cend) {
          opts.FixedString = boost::lexical_cast<bool>(*ccur);
          if (++ccur != cend) {
            opts.CaseInsensitive = boost::lexical_cast<bool>(*ccur);
            if (++ccur != cend) {
              opts.UnicodeMode = boost::lexical_cast<bool>(*ccur);
            }
          }
        }

        addPattern(hFsm, hProg, ph.get(), pat, &opts, etok, lnum, err);
      }
      else {
        // use default encodings and options
        addPattern(hFsm, hProg, ph.get(), pat, &opts, defEncs, lnum, err);
      }
    }

    return 0;
  }
}

int lg_add_pattern_list(LG_HFSM hFsm,
                        LG_HPROGRAM hProg,
                        const char* patterns,
                        const char* source,
                        const char** defaultEncodings,
                        unsigned int defaultEncodingsNum,
                        const LG_KeyOptions* defaultOptions,
                        LG_Error** err)
{
  LG_Error* in_err = nullptr;

  int ret = trapWithRetval(
    [hFsm, hProg, patterns, source, defaultEncodings, defaultEncodingsNum, defaultOptions, &in_err]() {
      return addPatternList(hFsm, hProg, patterns, source, defaultEncodings, defaultEncodingsNum, defaultOptions, &in_err);
    },
    -1,
    err
  );

  if (err) {
    if (in_err) {
      if (*err) {
        // append the error from addPatternList to the chain
        in_err->Next = *err;
      }
      *err = in_err;
    }
  }

  return ret;
}

unsigned int lg_pattern_count(const LG_HPROGRAM hProg) {
  return hProg->PMap->Patterns.size();
}

LG_PatternInfo* lg_pattern_info(LG_HPROGRAM hProg,
                                unsigned int patternIndex)
{
  return &hProg->PMap->Patterns[patternIndex];
}

namespace {
  LG_HPROGRAM create_program(unsigned int numTotalPatternsSizeHint) {
    std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> hProg(
      new ProgramHandle,
      lg_destroy_program
    );

    hProg->PMap.reset(new PatternMap(numTotalPatternsSizeHint));
    hProg->Prog = nullptr;

    return hProg.release();
  }
}

LG_HPROGRAM lg_create_program(unsigned int numTotalPatternsSizeHint) {
  return trapWithRetval(
    [numTotalPatternsSizeHint](){ return create_program(numTotalPatternsSizeHint); },
    nullptr
  );
}

namespace {
  int compile_program(LG_HFSM hFsm, LG_HPROGRAM hProg, const LG_ProgramOptions* opts) {
    hFsm->Impl->finalizeGraph(opts->DeterminizeDepth);
    hProg->Prog = Compiler::createProgram(*hFsm->Impl->Fsm);
    return hProg->Prog != nullptr;
  }
}

int lg_compile_program(LG_HFSM hFsm, LG_HPROGRAM hProg,
                       const LG_ProgramOptions* options)
{
  return trapWithRetval(
    [hFsm, hProg, options](){ return compile_program(hFsm, hProg, options); },
    0
  );
}

unsigned int lg_program_size(const LG_HPROGRAM hProg) {
  return sizeof(uint64_t) + hProg->PMap->bufSize() +
         sizeof(uint64_t) + hProg->Prog->bufSize();
}

namespace {
  void write_program(const LG_HPROGRAM hProg, void* buffer) {
    char* dst = reinterpret_cast<char*>(buffer);

    const std::vector<char> pmap_buf = hProg->PMap->marshall();
    const uint64_t pmap_size = pmap_buf.size();
    *reinterpret_cast<uint64_t*>(dst) = pmap_size;
    dst += sizeof(pmap_size);
    std::memcpy(dst, pmap_buf.data(), pmap_size);
    dst += pmap_size;

    const std::vector<char> prog_buf = hProg->Prog->marshall();
    const uint64_t prog_size = prog_buf.size();
    *reinterpret_cast<uint64_t*>(dst) = prog_size;
    dst += sizeof(prog_size);
    std::memcpy(dst, prog_buf.data(), prog_size);
    dst += prog_size;
  }

  LG_HPROGRAM read_program(const void* buffer, size_t size) {
    std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> hProg(
      new ProgramHandle,
      lg_destroy_program
    );

    const char* src = reinterpret_cast<const char*>(buffer);

    const uint64_t pmap_size = *reinterpret_cast<const uint64_t*>(src);
    src += sizeof(pmap_size);
    hProg->PMap = PatternMap::unmarshall(src, pmap_size);
    src += pmap_size;

    const uint64_t prog_size = *reinterpret_cast<const uint64_t*>(src);
    src += sizeof(prog_size);
    hProg->Prog = Program::unmarshall(src, prog_size);
    src += prog_size;

// TODO: don't go beyond size?

    return hProg.release();
  }
}

LG_HPROGRAM lg_read_program(const void* buffer, int size) {
  return trapWithRetval(
    [buffer, size](){ return read_program(buffer, size); },
    nullptr
  );
}

void lg_write_program(const LG_HPROGRAM hProg, void* buffer) {
  exceptionTrap(std::bind(write_program, hProg, buffer));
}

void lg_destroy_program(LG_HPROGRAM hProg) {
  delete hProg;
}

namespace {
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

    hCtx->Impl = VmInterface::create(hProg->Prog);
#ifdef LBT_TRACE_ENABLED
    hCtx->Impl->setDebugRange(beginTrace, endTrace);
#endif

    return hCtx.release();
  }
}

LG_HCONTEXT lg_create_context(LG_HPROGRAM hProg,
                              const LG_ContextOptions* options)
{
  const uint64_t
    begin = options ? options->TraceBegin : std::numeric_limits<uint64_t>::max(),
    end = options ? options->TraceEnd : std::numeric_limits<uint64_t>::max();

  return trapWithRetval(
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

uint64_t lg_search(LG_HCONTEXT hCtx,
                       const char* bufStart,
                       const char* bufEnd,
                       const uint64_t startOffset,
                       void* userData,
                       LG_HITCALLBACK_FN callbackFn)
{
  return trapWithRetval(std::bind(&VmInterface::search, hCtx->Impl, (const byte*) bufStart, (const byte*) bufEnd, startOffset, callbackFn, userData), std::numeric_limits<uint64_t>::max());
}

void lg_closeout_search(LG_HCONTEXT hCtx,
                        void* userData,
                        LG_HITCALLBACK_FN callbackFn)
{
  exceptionTrap(std::bind(&VmInterface::closeOut, hCtx->Impl, callbackFn, userData));
}

uint64_t lg_search_resolve(LG_HCONTEXT hCtx,
                       const char* bufStart,
                       const char* bufEnd,
                       const uint64_t startOffset,
                       void* userData,
                       LG_HITCALLBACK_FN callbackFn)
{
  return trapWithRetval(std::bind(&VmInterface::searchResolve, hCtx->Impl, (const byte*) bufStart, (const byte*) bufEnd, startOffset, callbackFn, userData), std::numeric_limits<uint64_t>::max());
}
