#pragma once

#include <cassert>
#include <limits>
#include <cstring>

#include "instructions.h"

enum OpCodesNG {
  BYTE_OP_NG = 0,
  BRANCH_BYTE,
  JUMP_OP_NG,
  SET_START,
  SET_END,
  MATCH_OP_NG,
  MEMCHR_OP
};

#pragma pack(push, 1)

struct InstructionNG {
  Operand Op;

  byte OpCode; // low byte

  void set(const uint32_t val) {
    *reinterpret_cast<uint32_t*>(this) = val;
  }

  explicit operator uint32_t() const {
    return *reinterpret_cast<const uint32_t*>(this);
  }
};


struct CurEnd {
  uint32_t cur;
  uint32_t end;
};

struct MatchInfo {
  uint64_t Start,
           End;
  uint32_t Label; // pattern index number

  MatchInfo():
    Start(std::numeric_limits<uint64_t>::max()),
    End(std::numeric_limits<uint64_t>::max()),
    Label(std::numeric_limits<uint32_t>::max()) {}

  MatchInfo(uint64_t s, uint64_t e, uint32_t l):
    Start(s), End(e), Label(l) {}

  bool operator==(const MatchInfo& x) const {
    return Start == x.Start && End == x.End && Label == x.Label;
  }
};


#pragma pack(pop)

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

int dispatch(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm);

#include "lightgrep/search_hit.h"

#include <iterator>

struct ThreadNG {
  uint32_t PC;

  LG_SearchHit Hit;
};

class Threadlist {
/*
  The point of this data structure is to provide for fast O(1) insertion and deletion
  in a list while avoiding the deleterious heap allocations and pointer-chasing of
  a conventional linked list (e.g., std::list). The below is not a full-fledged 
  implementation of the std::list<> API, but is intended to be a compatible subset
  and further rounding out of std::list<> API is fine.

  The basic idea is to use a std::vector as a backing store for the nodes in the list.
  Rather than use 2 64-bit pointers in the nodes, 2 32-bit indices are used. Two sentinel
  nodes are reserved first in the vector, for a zeroth node pointing to the first node
  in the list and for an end node beyond the last. By using two sentinel nodes, 
  several conditionals are avoided in insert() and erase().

  The vector expands as the list grows. However, nodes in the list may be erased, leaving
  holes. This would have two negative consequences: first, more memory than necessary
  would be used over the time as new nodes in the list were created at the end of the
  vector (instead of reusing these 'holes'); second, memory locality would decrease,
  leading to cache misses. To keep this from happening, a second list is maintained--a
  free list (stack), of all the nodes that have been deleted and are now free. When a node is
  erased from the list, it is added onto the free list. When a new node is created,
  the space for it comes from the free list. Only when the free list is empty will the
  backing vector grow its size. The free list is maintained by reusing the Next index
  in the Node struct. The free list is effectively singly-linked so Prev is not
  manipulated. The only overhead cost of maintaining this second free list is the
  single uint32_t for knowing the index of the first element in the free list.
*/
public:
  class TLIterator {
  public:
    friend class Threadlist;

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = ThreadNG;
    using pointer           = value_type*;
    using reference         = value_type&;

    // constructors
    // constructible, copy-constructible, copy-assignable, destructible, swappable

    // operators
    reference operator*() const { return TL->Vec[Index].T; }
    pointer operator->() { return &TL->Vec[Index].T; }

    TLIterator& operator++() {
      if (Index != TL->Last) {
        Index = TL->Vec[Index].Next;
      }
      return *this;
    }

    TLIterator operator++(int) {
      TLIterator ret(*this);
      if (Index != TL->Last) {
        Index = TL->Vec[Index].Next;
      }
      return ret;
    }

    uint32_t index() const { return Index; }

    friend bool operator==(const TLIterator& a, const TLIterator& b) { return a.TL == b.TL && a.Index == b.Index; }
    friend bool operator!=(const TLIterator& a, const TLIterator& b) { return a.TL != b.TL || a.Index != b.Index; }

  private:
    TLIterator(Threadlist* tl, uint32_t i): TL(tl), Index(i) {}

    Threadlist* TL; // look, pointers still work, it'll be okay

    uint32_t Index;
  };

  friend class TLIterator;

  struct ThreadNode {
    ThreadNG T;

    uint32_t Prev;
    uint32_t Next;

    ThreadNode(): T(), Prev(SENTINEL), Next(SENTINEL) {}
    ThreadNode(const ThreadNG& t, uint32_t prev = SENTINEL, uint32_t next = SENTINEL): T(t), Prev(prev), Next(next) {}
  };


  Threadlist():
    First(0), Last(1), Free(SENTINEL), Size(0)
  {
    Vec.reserve(20);
    Vec.emplace_back(ThreadNG(), SENTINEL, 1u);
    Vec.emplace_back(ThreadNG(), 0u, SENTINEL);
  }

  bool empty() const { return Size == 0; }

  size_t size() const { return Size; }
  size_t capacity() const { return Vec.capacity(); }
  size_t vector_size() const { return Vec.size(); }

  void reserve(size_t capacity) { Vec.reserve(capacity + 2); }

  TLIterator insert(TLIterator pos, const ThreadNG& t) {
    uint32_t i = alloc_node(t);

    auto& posRef(Vec[pos.Index]);
    auto& newRef(Vec[i]);
    newRef.Prev = posRef.Prev;
    newRef.Next = pos.Index;

    Vec[posRef.Prev].Next = i;
    posRef.Prev = i;

    return TLIterator(this, i);
  }

  TLIterator begin() { return TLIterator(this, Vec[First].Next); }
  TLIterator end() { return TLIterator(this, Last); }

  ThreadNG& front() { return Vec[Vec[First].Next].T; }
  ThreadNG& back() { return Vec[Vec[Last].Prev].T; }

  TLIterator erase(TLIterator pos) {
    // it should not be possible to get an itr where pos.Index == First
    if (pos.Index == Last || pos.Index == SENTINEL) {
      return end();
    }
    auto& posRef(Vec[pos.Index]);
    Vec[posRef.Prev].Next = posRef.Next;
    Vec[posRef.Next].Prev = posRef.Prev;
    --Size;

    TLIterator ret(this, posRef.Next);

    // add to free list
    posRef.Next = Free;
    Free = pos.Index;

    return ret;
  }

  void clear() {
    Vec[First].Next = Last;
    Vec[Last].Prev = First;
    Size = 0;
  }

private:
  static const uint32_t SENTINEL = std::numeric_limits<uint32_t>::max();

  uint32_t alloc_node(const ThreadNG& t) {
    uint32_t ret;
    ++Size;
    if (Free == SENTINEL) {
      Vec.push_back(t);
      ret = Vec.size() - 1;
    }
    else {
      ret = Free;
      Free = Vec[Free].Next;
    }
    return ret;
  }

  std::vector<ThreadNode> Vec;

  uint32_t First,
           Last,
           Free;

  size_t Size;
};

class ProgramNG {
public:
  ProgramNG(): Code() {}
  ProgramNG(const std::vector<InstructionNG>& code): Code(code) {}

  void swapCode(std::vector<InstructionNG>& newCode) {
    Code.swap(newCode);
  }

  const InstructionNG* begin() const { return &Code[0]; }
  const InstructionNG* end() const { return &Code[Code.size()]; }

  uint32_t numInstructions() const { return static_cast<uint32_t>(Code.size()); }

private:
  std::vector<InstructionNG> Code;
};

class VmNG {
public:
  VmNG(): Prog(), Hits(), BufOffset(0) { Hits.reserve(100); }

  VmNG(const ProgramNG& prog): Prog(prog), Hits(), BufOffset(0) { Hits.reserve(100); }

  const std::vector<MatchInfo>& hits() const { return Hits; }

  uint64_t curBufOffset() const { return BufOffset; }

  void addHit(const MatchInfo& hit) { Hits.push_back(hit); }

  void search(const byte* buf, const byte* bufEnd) {
    BufOffset = 0;
    CurEnd curBuf = {0, static_cast<uint32_t>(bufEnd - buf)};
    CurEnd curProg = {0, Prog.numInstructions()};
    MatchInfo info;

    dispatch(buf, curBuf, Prog.begin(), curProg, info, this);
  }

  void reset() {
    Hits.clear();
    BufOffset = 0;
  }

private:
  ProgramNG Prog;

  std::vector<MatchInfo> Hits;

  uint64_t BufOffset;
};

/*
  State:
    current instruction/offset into program (cur instruction)
    [begin, end) of program

    current offset into input buffer (cur byte)
    [begin, end) of input buffer

    start of match, pattern label

    pointer back to VM machinery (potential match reporting & resolution, thread lists, etc)

  CPS on Intel: six registers, 64 bits apiece
    - should they be out-parameters so state becomes visible to callee?
    - does making them out-parameters even work with __fastcall semantics???
    - it's okay for complex functions to manipulate lots of data, but calling functions could screw up all of CSP
*/



template<auto DispatcherFn>
int do_byte_op(const byte* buf,
               CurEnd& curBuf,
               const InstructionNG* prog,
               CurEnd& curProg,
               MatchInfo& info,
               void* vm)
{
  const InstructionNG inst = prog[curProg.cur];
  if (UNLIKELY(buf[curBuf.cur] == inst.Op.T1.Byte)) {
    ++curBuf.cur;
    ++curProg.cur;
    [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
  }
  else {
    return 0;
  }
}

template<auto DispatcherFn>
int do_branch_byte_op(const byte* buf,
                     CurEnd& curBuf,
                     const InstructionNG* prog,
                     CurEnd& curProg,
                     MatchInfo& info,
                     void* vm)
{
  if (UNLIKELY(curBuf.cur >= curBuf.end)) {
    return 0;
  }
  const InstructionNG inst = prog[curProg.cur];
  if (UNLIKELY(buf[curBuf.cur] == inst.Op.T1.Byte)) {
    curProg.cur += 2;
  }
  else {
    curProg.cur = uint32_t(prog[curProg.cur + 1]);
  }
  ++curBuf.cur;
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_set_start_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  VmNG& vmRef(*reinterpret_cast<VmNG*>(vm));

  assert(vmRef.curBufOffset() + curBuf.cur >= prog[curProg.cur].Op.Offset);
  info.Start = vmRef.curBufOffset() + curBuf.cur - prog[curProg.cur].Op.Offset;
  ++curProg.cur;
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_set_end_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  VmNG& vmRef(*reinterpret_cast<VmNG*>(vm));

  info.End = vmRef.curBufOffset() + curBuf.cur;
  ++curProg.cur;
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_match_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  VmNG& vmRef(*reinterpret_cast<VmNG*>(vm));

  vmRef.addHit(info);
  ++curProg.cur;
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_memchr_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  // std::cerr << "memchr'ing for '" << prog[curProg.cur].Op.T1.Byte << "' [" << curBuf.cur << ", " << curBuf.end << ") of " << buf << '\n';
  const byte* cur = &buf[curBuf.cur];
  const byte* end = &buf[curBuf.end];
  const byte* found(reinterpret_cast<const byte*>(std::memchr(cur, prog[curProg.cur].Op.T1.Byte, end - cur)));
  if (found) {
    ++curProg.cur;
    curBuf.cur = found - buf;
    ++curBuf.cur;
    // std::cerr << "Found at " << (curBuf.cur - 1) << ", curProg.cur at " << curProg.cur << '\n';
  }
  else {
    // std::cerr << "Not found\n";
    curBuf.cur = curBuf.end;
  }
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

template<auto DispatcherFn>
int do_jump_op(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  curProg.cur = uint32_t(prog[curProg.cur + 1]);
  [[clang::musttail]] return DispatcherFn(buf, curBuf, prog, curProg, info, vm);
}

int dispatch(const byte* buf,
             CurEnd& curBuf,
             const InstructionNG* prog,
             CurEnd& curProg,
             MatchInfo& info,
             void* vm)
{
  if (UNLIKELY(curBuf.cur == curBuf.end)) {
    return 0;
  }
  switch(prog[curProg.cur].OpCode) {
  case BYTE_OP_NG:
    [[clang::musttail]] return do_byte_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case BRANCH_BYTE:
    [[clang::musttail]] return do_branch_byte_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case JUMP_OP_NG:
    [[clang::musttail]] return do_jump_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case SET_START:
    [[clang::musttail]] return do_set_start_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case SET_END:
    [[clang::musttail]] return do_set_end_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  case MATCH_OP_NG:
    [[clang::musttail]] return do_match_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
   case MEMCHR_OP:
    [[clang::musttail]] return do_memchr_op<dispatch>(buf, curBuf, prog, curProg, info, vm);
  default:
    return 0;
  }
}
