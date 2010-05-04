#pragma once

#include "basic.h"

// this ONLY works for POD types, especially clear()
template<class T>
class StaticVector {
public:
  typedef T* iterator;
  typedef const T* const_iterator;
  
  // StaticVector(): Array(0), Capacity(0), Begin(0), End(0) {}
  StaticVector(unsigned int capacity = 10): Array(new T[capacity]), Capacity(capacity), Begin(&Array[0]), End(&Array[0]) {}

  StaticVector(const StaticVector<T>& x): Array(new T[x.Capacity]), Capacity(x.Capacity), Begin(&Array[0]), End(&Array[x.size()]) {
    unsigned int num = size();
    for (unsigned int i = 0; i < num; ++i) {
      Array[i] = x.Array[i];
    }
  }

  StaticVector<T>& operator=(const StaticVector<T>& rhs) const {
    Array.reset(new T[rhs.Capacity]);
    Capacity = rhs.Capacity;
    Begin = &Array[0];
    unsigned int num = rhs.size();
    End = &Array[num];
    for (unsigned int i = 0; i < num; ++i) {
      Array[i] = rhs.Array[i];
    }
    return *this;
  }

  T& operator[](unsigned int i) { return Array[i]; }
  const T& operator[](unsigned int i) const { return Array[i]; }

  iterator begin() { return Begin; }
  const_iterator begin() const { return Begin; }

  iterator end() { return End; }
  const_iterator end() const { return End; }

  unsigned int size() const { return End - Begin; }
  bool empty() const { return Begin == End; }
  
  void push_back(const T& x) { *(End++) = x; }
  void clear() { End = Begin; }

  void swap(StaticVector<T>& x) {
    Array.swap(x.Array);
    unsigned int tempI = Capacity;
    Capacity = x.Capacity;
    x.Capacity = tempI;
    T* tempP = Begin;
    Begin = x.Begin;
    x.Begin = tempP;
    tempP = End;
    End = x.End;
    x.End = tempP;
  }

  void resize(unsigned int capacity) { // does not retain old objects; again, unsafe
    Array.reset(new T[capacity]);
    Capacity = capacity;
    Begin = &Array[0];
    End = &Array[0];
  }

private:
  boost::scoped_array<T> Array;
  unsigned int Capacity;
  T *Begin,
    *End;
};
