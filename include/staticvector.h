/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
 
 #pragma once

#include "basic.h"

#include <memory>

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

  T& front() { return *Begin; }
  const T& front() const { return *Begin; }

  T& back() { return *(End - 1); }
  const T& back() const { return *(End - 1); }

  unsigned int size() const { return End - Begin; }
  bool empty() const { return Begin == End; }
  bool full() const { return size() == Capacity; }

  void push_back(const T& x) { *(End++) = x; }
  void clear() { End = Begin; }

  T& addBack() { return *(End++); }

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
  std::unique_ptr<T[]> Array;
  unsigned int Capacity;
  T *Begin,
    *End;
};
