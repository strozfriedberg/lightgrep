#pragma once

#include "lightgrep/search_hit.h"

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
