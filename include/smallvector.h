#pragma once

#include <algorithm>
#include <iterator>
//#include <limits>
//#include <memory>
//#include <stdexcept>
#include <vector>

template <class T, size_t N>
class SmallVector
{
public:

  //
  // typedefs
  //

  typedef T value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* pointer;
  typedef const T* const_pointer;

  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  //
  // ctors & dtor
  //

  SmallVector(std::vector< std::vector<T> >& store): ArrayEnd(0), VecStore(store) {}

/*
  explicit SmallVector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()): ArrayEnd(0), Alloc(alloc) {
    assign(count, value);
  }

  template <class InputIterator> SmallVector(InputIterator first, InputIterator last, const Allocator& alloc = Allocator()): ArrayEnd(0), Alloc(alloc) {
    assign(first, last);
  }
*/

  SmallVector(const SmallVector& other): VecStore(other.VecStore) {
    if (other.large()) {
      VecStore.push_back(other.vector());
      ArrayEnd = N + VecStore.size();
    }
    else {
      ArrayEnd = other.ArrayEnd;
      std::copy(other.Array, other.Array + other.ArrayEnd, Array);
    }
  }

/*
  ~SmallVector() {

  }
*/

  //
  // assignment
  //

  SmallVector& operator=(const SmallVector& other) {
    VecStore = other.VecStore;

    if (other.large()) {
      VecStore.push_back(other.vector());
      ArrayEnd = N + VecStore.size();
    }
    else {
      ArrayEnd = other.ArrayEnd;
      std::copy(other.Array, other.Array + other.ArrayEnd, Array);
    }

    return *this;
  }

/*
  void assign(size_type count, const T& value) {
    if (count > N) {
      VecStore.push_back(std::vector<T>(count, value));
      ArrayEnd = VecStore.size() - 1 + N;
    }
    else {
      std::fill(Array, Array + count, value);
      ArrayEnd = count;
    }
  }

  template <class InputIterator> void assign(InputIterator first, InputIterator last) {
    if (last - first > N) {
      VecStore.push_back(std::vector<T>(first, last));
      ArrayEnd = VecStore.size() - 1 + N;
    }
    else {
      std::copy(first, last, Array);
      ArrayEnd = last - first;
    }
  }

  allocator_type get_allocator() const {
    return Alloc;
  }
*/

  //
  // element access
  //

/*
  reference at(size_type pos) {
    if (pos >= size()) {
      throw std::out_of_range(boost::lexical_cast<std::string>(pos));
    }

    return *this[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size()) {
      throw std::out_of_range(boost::lexical_cast<std::string>(pos));
    }

    return *this[pos];
  }
*/

  reference operator[](size_type pos) {
    return large() ? vector()[pos] : Array[pos];
  }

  const_reference operator[](size_type pos) const {
    return large() ? vector()[pos] : Array[pos];
  }

/*
  reference front() {
    return large() ? vector().front() : Array[0];
  }

  const_reference front() const {
    return large() ? vector().front() : Array[0];
  }

  reference back() {
    return large() ? vector().back() : Array[ArrayEnd-1];
  }

  const_reference back() const {
    return large() ? vector().back() : Array[ArrayEnd-1];
  }
*/

  //
  // iterators
  //

  iterator begin() {
    return large() ? &*vector().begin() : Array;
  }

  const_iterator begin() const {
    return large() ? &*vector().begin() : Array;
  }

  iterator end() {
    return large() ? &*vector().end() : Array + ArrayEnd;
  }

  const_iterator end() const {
    return large() ? &*vector().end() : Array + ArrayEnd;
  }

/*
  reverse_iterator rbegin() {
  }

  const_reverse_iterator rbegin() const {
  }

  reverse_iterator rend() {
  }

  const_reverse_iterator rend() const {
  }
*/

  //
  // capacity
  //

/*
  bool empty() const {
    return size() == 0;
  }
*/

  size_type size() const {
    return large() ? vector().size() : ArrayEnd;
  }

/*
  size_type max_size() const {
    return std::numeric_limits<std::vector<T>::size_type>::max();
  }

  void reserve(size_type size) {
    if (size > N) {

    }
  }

  size_type capacity() const {
    return large() ? vector().capacity() : N;
  }
*/

  //
  // modifiers
  //

  void clear() {
    if (large()) {
      vector().clear();
    }
    else {
      ArrayEnd = 0;
    }
  }

  iterator insert(iterator i, const T& value) {
    const difference_type pos = i - begin();

    if (large()) {
      return &*vector().insert(vector().begin() + pos, value);
    }
    else {
      if (ArrayEnd < N) {
        std::copy(Array + pos, Array + ArrayEnd, Array + pos + 1);
        Array[pos] = value;
        ++ArrayEnd;
        return ++i;
      }
      else { /* ArrayEnd == N */
        VecStore.push_back(std::vector<T>(Array, Array + pos));
        ArrayEnd += VecStore.size();

        vector().push_back(value);
        vector().insert(vector().end(), Array + pos, Array + N);

        return &*(vector().begin() + pos);
      }
    }
  }

/*
  void insert(iterator pos, size_type count, const T& value) {
  }

  template <class InputIterator> void insert(iterator pos, InputIterator first, InputIterator last) {
  }
*/

  iterator erase(iterator i) {
    const difference_type pos = i - begin();

    if (large()) {
      return &*vector().erase(vector().begin() + pos);
    }
    else {
      std::copy(Array + pos + 1, Array + ArrayEnd, Array + pos);
      --ArrayEnd;
      return i;
    }
  }

/*
  iterator erase(iterator first, iterator last) {
  }
*/

  void push_back(const T& value) {
    if (ArrayEnd < N) {
      Array[ArrayEnd++] = value;
    }
    else {
      if (ArrayEnd == N) {
        VecStore.push_back(std::vector<T>(Array, Array + ArrayEnd));
        ArrayEnd += VecStore.size();
      }

      vector().push_back(value);
    }
  }

/*
  void pop_back() {
    if (ArrayEnd > N) {
      vector().pop_back();
    }
    else {
      --ArrayEnd;
    }
  }

  void resize(size_type count, T value = T()) {
    if (count > N) {

    }
    else {
      std::fill(Array + ArrayEnd, Array + count, value);
      ArrayEnd = count;
    }
  }

  void swap(SmallVector& other) {
  }
*/

private:
  bool large() const {
    return ArrayEnd > N;
  }

  std::vector<T>& vector() {
    return VecStore[ArrayEnd - N - 1];
  }

  const std::vector<T>& vector() const {
    return VecStore[ArrayEnd - N - 1];
  }

  void overflow() {
    VecStore.push_back(std::vector<T>(Array, Array + ArrayEnd));
    ArrayEnd += VecStore.size();
  }

  T Array[N];
  unsigned int ArrayEnd;

  std::vector< std::vector<T> >& VecStore;
};

/*
template <class T, class Alloc>
void operator==(SmallVector<T,Alloc> &lhs, SmallVector<T,Alloc> &rhs) {
}

template <class T, class Alloc>
void operator!=(SmallVector<T,Alloc> &lhs, SmallVector<T,Alloc> &rhs) {
}

template <class T, class Alloc>
void operator<(SmallVector<T,Alloc> &lhs, SmallVector<T,Alloc> &rhs) {
}

template <class T, class Alloc>
void operator<=(SmallVector<T,Alloc> &lhs, SmallVector<T,Alloc> &rhs) {
}

template <class T, class Alloc>
void operator>(SmallVector<T,Alloc> &lhs, SmallVector<T,Alloc> &rhs) {
}

template <class T, class Alloc>
void operator>=(SmallVector<T,Alloc> &lhs, SmallVector<T,Alloc> &rhs) {
}

template <class T, unsigned int N, class Alloc>
void std::swap(SmallVector<T,N,Alloc> &lhs, SmallVector<T,N,Alloc> &rhs) {
  lhs.swap(rhs);
}
*/
