#pragma once

#include <utility>

#include "basic.h"
// #include "lightgrep/search_hit.h"

struct ThreadNG {
  uint64_t  Start,        // starting offset of the hit
            End;          // one past the hit, i.e., End - Start = Length
  uint32_t  KeywordIndex; // index of keyword that hit
  uint32_t PC;
};

template<class TypeT>
class Fastlist {
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
private:
  enum {
    LAST = 0, // It may be a hair faster to have LAST == 0
    FIRST = 1,
    SENTINEL = 0xFFFFFFFF
  };

public:
  struct ThreadNode;

  class TLIterator {
  public:
    friend class Fastlist;

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = TypeT;
    using pointer           = value_type*;
    using reference         = value_type&;

    // constructors
    // constructible, copy-constructible, copy-assignable, destructible, swappable

    // operators
    reference operator*() const { return (*Vec)[Index].T; }
    pointer operator->() { return &(*Vec)[Index].T; }

    TLIterator& operator++() {
      Index = (*Vec)[Index].Next;
      return *this;
    }

    TLIterator operator++(int) {
      TLIterator ret(*this);
      Index = (*Vec)[Index].Next;
      // if (LIKELY(Index != LAST)) {
      //   Index = TL->Vec[Index].Next;
      // }
      return ret;
    }

    uint32_t index() const { return Index; }

    friend bool operator==(const TLIterator& a, const TLIterator& b) { return a.Vec == b.Vec && a.Index == b.Index; }
    friend bool operator!=(const TLIterator& a, const TLIterator& b) { return a.Vec != b.Vec || a.Index != b.Index; }

  private:
    TLIterator(Fastlist* tl, uint32_t i): Vec(&(tl->Vec)), Index(i) {}

    std::vector<ThreadNode>* Vec;

    uint32_t Index;
  };

  friend class TLIterator;

  using iterator = TLIterator;
  using const_iterator = const TLIterator;

  struct ThreadNode {
    TypeT T;

    uint32_t Prev;
    uint32_t Next;

    ThreadNode(): T(), Prev(SENTINEL), Next(SENTINEL) {}
    ThreadNode(const TypeT& t, uint32_t prev = SENTINEL, uint32_t next = SENTINEL): T(t), Prev(prev), Next(next) {}
  };


  Fastlist():
    Size(0), Free(SENTINEL)
  {
    Vec.reserve(20);
    Vec.emplace_back(TypeT(), FIRST, LAST);
    Vec.emplace_back(TypeT(), FIRST, LAST);
    // Vec.emplace_back(TypeT(), SENTINEL, LAST);
    // Vec.emplace_back(TypeT(), FIRST, SENTINEL);
  }

  bool empty() const { return Size == 0; }

  size_t size() const { return Size; }
  size_t capacity() const { return Vec.capacity(); }
  size_t vector_size() const { return Vec.size(); }

  void reserve(size_t capacity) { Vec.reserve(capacity + 2); }

  TLIterator begin() { return TLIterator(this, Vec[FIRST].Next); }
  TLIterator end() { return TLIterator(this, LAST); }

  TypeT& front() { return Vec[Vec[FIRST].Next].T; }
  TypeT& back() { return Vec[Vec[LAST].Prev].T; }

  TLIterator insert(TLIterator pos, const TypeT& t) {
    uint32_t i = alloc_node(t);

    auto& posRef(Vec[pos.Index]);
    auto& newRef(Vec[i]);
    newRef.Prev = posRef.Prev;
    newRef.Next = pos.Index;

    Vec[posRef.Prev].Next = i;
    posRef.Prev = i;

    return TLIterator(this, i);
  }

  void push_back(const TypeT& t) {
    uint32_t i = alloc_node(t);

    auto& lastRef(Vec[LAST]);
    auto& newRef(Vec[i]);
    newRef.Prev = lastRef.Prev;
    newRef.Next = LAST;

    Vec[newRef.Prev].Next = i;
    lastRef.Prev = i;
  }

  TLIterator erase(TLIterator pos) {
    // it should not be possible to get an itr where pos.Index == First
    if (UNLIKELY(pos.Index == LAST || pos.Index == SENTINEL)) {
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

  void swap(Fastlist& x) {
    Vec.swap(x.Vec);
    std::swap(Size, x.Size);
    std::swap(Free, x.Free);
  }

  void clear() {
    Vec[FIRST].Next = LAST;
    Vec[LAST].Prev = FIRST;
    Free = SENTINEL;
    Size = 0;
  }

private:
  uint32_t alloc_node(const TypeT& t) {
    uint32_t ret;
    ++Size;
    if (LIKELY(Free == SENTINEL)) {
      ret = Vec.size();
      Vec.push_back(t);
    }
    else {
      ret = Free;
      Vec[ret] = t;
      Free = Vec[Free].Next;
    }
    return ret;
  }

  std::vector<ThreadNode> Vec;

  size_t Size;

  uint32_t Free;
};
