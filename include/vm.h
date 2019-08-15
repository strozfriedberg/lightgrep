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

#pragma once

#include <bitset>
#include <set>
#include <vector>

#include "basic.h"
#include "sparseset.h"
#include "vm_interface.h"
#include "thread.h"

class Vm: public VmInterface {
public:

  typedef std::vector<Thread> ThreadList;

  Vm(ProgramPtr prog);

  virtual void startsWith(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData);
  virtual uint64_t search(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData);
  virtual uint64_t searchResolve(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData);
  virtual void closeOut(HitCallback hitFn, void* userData);
  virtual void reset();

  #ifdef LBT_TRACE_ENABLED
  void setDebugRange(uint64_t beg, uint64_t end) {
    BeginDebug = beg;
    EndDebug = end;
  }
  #endif

  bool execute(Thread* t, const byte* const cur);
  bool execute(ThreadList::iterator t, const byte* const cur);

  bool executeEpsilon(Thread* t, uint64_t offset);
  bool executeEpsilon(ThreadList::iterator t, uint64_t offset);

  void executeFrame(const byte* const cur, uint64_t offset, HitCallback hitFn, void* userData);
  void cleanup();

  const ThreadList& first() const { return First; }
  const ThreadList& active() const { return Active; }
  const ThreadList& next() const { return Next; }

  Thread& add(const Thread& t) {
    Active.push_back(t);
    return Active.back();
  }

  uint32_t numActive() const { return Active.size(); }
  uint32_t numNext() const { return Next.size(); }

private:
  void _markLive(const uint32_t label);
  bool _liveCheck(const uint64_t start, const uint32_t label) const;

  bool _execute(const Instruction* const base, ThreadList::iterator t, const byte* const cur) const;

  template <uint32_t X>
  bool _executeEpsilon(const Instruction* const base, ThreadList::iterator t, const uint64_t offset);

  template <uint32_t X>
  bool _executeEpSequence(const Instruction* const base, ThreadList::iterator t, const uint64_t offset);

  void _executeThread(const Instruction* const base, ThreadList::iterator t, const byte* const cur, const uint64_t offset);

  void _executeNewThreads(const Instruction* const base, ThreadList::iterator t, const byte* const cur, const uint64_t offset);

  void _executeFrame(const std::bitset<256*256>& filter, ThreadList::iterator t, const Instruction* const base, const byte* const cur, const uint64_t offset);
  void _executeFrame(ThreadList::iterator t, const Instruction* const base, const byte* const cur, const uint64_t offset);

  void _cleanup();

  uint64_t _startOfLeftmostLiveThread(const uint64_t offset) const;

  #ifdef LBT_TRACE_ENABLED
  void open_init_epsilon_json(std::ostream& out);
  void close_init_epsilon_json(std::ostream& out) const;
  void open_frame_json(std::ostream& out, uint64_t offset, const byte* const cur);
  void close_frame_json(std::ostream& out, uint64_t offset) const;
  void pre_run_thread_json(std::ostream& out, uint64_t offset, const Thread& t,
                           const Instruction* const base);
  void post_run_thread_json(std::ostream& out, uint64_t offset, const Thread& t,
                            const Instruction* const base);
  void thread_json(std::ostream& out, const Thread& t,
                   const Instruction* const base, byte state);

  bool first_thread_json;
  std::set<uint64_t> new_thread_json;

  uint64_t BeginDebug, EndDebug;
  uint64_t NextId;
  #endif

  std::vector<uint64_t> ThreadCountHist;

  const ProgramPtr Prog;
  const Instruction* const ProgEnd;

  ThreadList First,
             Active,
             Next;

  SparseSet CheckLabels;

  bool LiveNoLabel;
  SparseSet Live;

  std::vector<uint64_t> MatchEnds;
  uint64_t MatchEndsMax;

  HitCallback CurHitFn;
  void* UserData;
};
