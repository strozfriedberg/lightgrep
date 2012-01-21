#pragma once

#include <algorithm>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

template <class T, size_t SmallSize>
class SmallVector
{
public:

  typedef T value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* pointer;
  typedef const T* const_pointer;
//  typedef std::reverse_iterator<iterator> reverse_iterator;
//  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  class iterator;
  class const_iterator;

  class iterator : public boost::iterator_facade<iterator, T, std::random_access_iterator_tag>
  {
  public:
    iterator(): Ptr(0) {} 

    explicit iterator(pointer ptr): Ptr(ptr) {}

    explicit iterator(typename std::vector<value_type>::iterator i): Ptr(0), Iter(i) {}

    iterator(const iterator& other): Ptr(other.Ptr), Iter(other.Iter) {}

  private:
    friend class const_iterator;
    friend class boost::iterator_core_access;

    reference dereference() const {
      return Ptr ? *Ptr : *Iter; 
    }

    bool equal(const iterator& other) const {
      return Ptr == other.Ptr && (Ptr || Iter == other.Iter);
    }

    bool equal(const const_iterator& other) const {
      return Ptr == other.Ptr && (Ptr || Iter == other.Iter);
    }

    void increment() {
      if (Ptr) {
        ++Ptr;
      }
      else {
        ++Iter;
      }
    }

    void decrement() {
      if (Ptr) {
        --Ptr;
      }
      else {
        --Iter;
      }
    }

    void advance(difference_type n) {
      if (Ptr) {
        Ptr += n;
      }
      else {
        Iter += n;
      }
    }  

    difference_type distance_to(const iterator& other) const {
      return Ptr ? other.Ptr - Ptr : other.Iter - Iter;
    }

    difference_type distance_to(const const_iterator& other) const {
      return Ptr ? other.Ptr - Ptr : other.Iter - Iter;
    }

    pointer Ptr;
    typename std::vector<value_type>::iterator Iter;
  };

  class const_iterator : public boost::iterator_facade<const_iterator, T const, std::random_access_iterator_tag>
  {
  public:
    const_iterator(): Ptr(0) {}

    explicit const_iterator(T* ptr): Ptr(ptr) {}

    explicit const_iterator(T const* ptr): Ptr(ptr) {}

    explicit const_iterator(typename std::vector<value_type>::iterator i): Ptr(0), Iter(i) {}

    explicit const_iterator(typename std::vector<value_type>::const_iterator i): Ptr(0), Iter(i) {}

    const_iterator(const iterator& other): Ptr(other.Ptr), Iter(other.Iter) {}

    const_iterator(const const_iterator& other): Ptr(other.Ptr), Iter(other.Iter) {}

  private:
    friend class iterator;
    friend class boost::iterator_core_access;

    const T& dereference() const {
      return Ptr ? *Ptr : *Iter; 
    }

    bool equal(const iterator& other) const {
      return Ptr == other.Ptr && (Ptr || Iter == other.Iter);
    }

    bool equal(const const_iterator& other) const {
      return Ptr == other.Ptr && (Ptr || Iter == other.Iter);
    }

    void increment() {
      if (Ptr) {
        ++Ptr;
      }
      else {
        ++Iter;
      }
    }

    void decrement() {
      if (Ptr) {
        --Ptr;
      }
      else {
        --Iter;
      }
    }

    void advance(difference_type n) {
      if (Ptr) {
        Ptr += n;
      }
      else {
        Iter += n;
      }
    }  

    difference_type distance_to(const iterator& other) const {
      return Ptr ? other.Ptr - Ptr : other.Iter - Iter;
    }

    difference_type distance_to(const const_iterator& other) const {
      return Ptr ? other.Ptr - Ptr : other.Iter - Iter;
    }

//    pointer Ptr;
    T const* Ptr;
    typename std::vector<T>::const_iterator Iter;
  };

/*
  template <class Value>
  class base_iter : public boost::iterator_facade<base_iter<Value>, Value, std::random_access_iterator_tag>
  {
  private:
    struct enabler {};

  public:
    base_iter(): Ptr(0) {} 

    explicit base_iter(pointer ptr): Ptr(ptr) {}

    explicit base_iter(typename std::vector<value_type>::iterator i): Ptr(0), Iter(i) {}

    explicit base_iter(typename std::vector<value_type>::const_iterator i): Ptr(0), Iter(i) {}

    template <class OtherValue>
    base_iter(const base_iter<OtherValue>& other,
              typename boost::enable_if<
                boost::is_convertible<OtherValue*,pointer>,
                enabler
              >::type = enabler()): Ptr(other.Ptr), Iter(other.Iter) {}

  private:
    friend class boost::iterator_core_access;

    reference dereference() const {
      return Ptr ? *Ptr : *Iter; 
    }

    template <class OtherValue>
    bool equal(const base_iter<OtherValue>& other) const {
      return Ptr == other.Ptr && (Ptr || Iter == other.Iter);
    }

    void increment() {
      if (Ptr) {
        ++Ptr;
      }
      else {
        ++Iter;
      }
    }

    void decrement() {
      if (Ptr) {
        --Ptr;
      }
      else {
        --Iter;
      }
    }

    void advance(difference_type n) {
      if (Ptr) {
        Ptr += n;
      }
      else {
        Iter += n;
      }
    }  

    template <class OtherValue>
    difference_type distance_to(const base_iter<OtherValue>& other) const {
      return Ptr ? other.Ptr - Ptr : other.Iter - Iter;
    }

    pointer Ptr;
    typename std::vector<value_type>::iterator Iter;
  };

  typedef base_iter<T> iterator;
  typedef base_iter<T const> const_iterator;
*/

/*
  template <class Value>
  class base_iter : public boost::iterator_facade<base_iter<Value>, Value, boost::random_access_iterator_tag>
  {
  pubilc:
    virtual ~base_iter() {}

  protected:
    friend class boost::iterator_core_access;

    virtual reference dereference() const = 0;

    template <class OtherValue>
    virtual bool equal(const base_iter<OtherValue>& other) const = 0;

    virtual void increment() = 0;

    virtual void decrement() = 0;

    virtual void advance(difference_type n) = 0;

    template <class OtherValue>
    virtual difference_type distance_to(const base_iter<OtherValue>& other) const = 0;
  };

  typedef base_iter<T> iterator;
  typedef base_iter<T const> const_iterator;

  template <class Value>
  class array_iter : public base_iter<Value>
  {
  pubilc:
    array_iter(): ptr(0) {}
  
    explicit array_iter(pointer p): ptr(p) {}

    template <class OtherValue>
    array_iter(const array_iter<OtherValue>& other): ptr(other.ptr) {}

  private:
    virtual reference dereference() const {
      return *ptr;
    }

    template <class OtherValue>
    virtual bool equal(const base_iter<OtherValue>& other) const {
      array_iter<OtherValue>* op = dynamic_cast<array_iter<OtherValue>*>(&other);
      return op && ptr == op->ptr;
    }

    virtual void increment() {
      ++ptr;
    }

    virtual void decrement() {
      --ptr;
    }

    virtual void advance(difference_type n) {
      ptr += n;
    }

    template <class OtherValue>
    virtual difference_type distance_to(const base_iter<OtherValue>& other) const { 
      array_iter<OtherValue>* op = dynamic_cast<array_iter<OtherValue>*>(&other);
      return op ? op.ptr - ptr : 0;
    }

    pointer ptr;
  };

  template <class Value>
  class vec_iter : public base_iter<Value>
  {
  pubilc:
    vec_iter() {}
  
    explicit vec_iter(std::vector<Value>::iterator i): iter(i) {}

    template <class OtherValue>
    vec_iter(const vec_iter<OtherValue>& other): iter(other.iter) {}

  private:
    virtual reference dereference() const {
      return *iter;
    }

    template <class OtherValue>
    virtual bool equal(const base_iter<OtherValue>& other) const {
      vec_iter<OtherValue>* op = dynamic_cast<vec_iter<OtherValue>*>(&other);
      return op && iter == op.iter;
    }

    virtual void increment() {
      ++iter;
    }

    virtual void decrement() {
      --iter;
    }

    virtual void advance(difference_type n) {
      iter += n;
    }

    template <class OtherValue>
    virtual difference_type distance_to(const base_iter<OtherValue>& other) const { 
      vec_iter<OtherValue>* op = dynamic_cast<vec_iter<OtherValue>*>(&other);
      return op ? other.iter - iter : 0;
    }

    std::vector<Value>::iterator iter;
  };
*/

  //
  // ctors & dtor
  //

  explicit SmallVector(std::vector< std::vector<T> >& store): ArrayEnd(0), VecStore(store) {}

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
      ArrayEnd = SmallSize + VecStore.size();
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
  // 
  //

  SmallVector& operator=(const SmallVector& other) {
    VecStore = other.VecStore;

    if (other.large()) {
      VecStore.push_back(other.vector());
      ArrayEnd = SmallSize + VecStore.size();
    }
    else {
      ArrayEnd = other.ArrayEnd;
      std::copy(other.Array, other.Array + other.ArrayEnd, Array);
    }

    return *this;
  }

/*
  void assign(size_type count, const T& value) {
    if (count > SmallSize) {
      VecStore.push_back(std::vector<T>(count, value));
      ArrayEnd = VecStore.size() - 1 + SmallSize;
    }
    else {
      std::fill(Array, Array + count, value);
      ArrayEnd = count; 
    }
  }

  template <class InputIterator> void assign(InputIterator first, InputIterator last) {
    if (last - first > SmallSize) {
      VecStore.push_back(std::vector<T>(first, last));
      ArrayEnd = VecStore.size() - 1 + SmallSize;
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
    return large() ? iterator(vector().begin()) : iterator(Array); 
  }  

  const_iterator begin() const {
    return large() ? const_iterator(vector().begin()) : const_iterator(Array); 
  }

  iterator end() {
    return large() ? iterator(vector().end()) : iterator(Array + ArrayEnd); 
  }

  const_iterator end() const {
    return large() ? const_iterator(vector().end()) : const_iterator(Array + ArrayEnd); 
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
    if (size > SmallSize) {
       
    }
  }

  size_type capacity() const {
    return large() ? vector().capacity() : SmallSize;
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
    const typename iterator::difference_type pos = i - begin();

    if (large()) {
      return iterator(vector().insert(vector().begin() + pos, value));
    }
    else {
      if (ArrayEnd < SmallSize) {
        std::copy(Array + pos, Array + ArrayEnd, Array + pos + 1);
        Array[pos] = value;
        ++ArrayEnd;
        return ++i;
      }
      else { /* ArrayEnd == SmallSize */
        VecStore.push_back(std::vector<T>(Array, Array + pos));
        ArrayEnd += VecStore.size();

        vector().push_back(value);
        vector().insert(vector().end(), Array + pos, Array + SmallSize);

        return iterator(vector().begin() + pos); 
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
    ptrdiff_t pos = i - begin();

    if (large()) {
      return iterator(vector().erase(vector().begin() + pos));
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
    if (ArrayEnd < SmallSize) {
      Array[ArrayEnd++] = value;
    }
    else {
      if (ArrayEnd == SmallSize) {
        VecStore.push_back(std::vector<T>(Array, Array + ArrayEnd));
        ArrayEnd += VecStore.size();
      }

      vector().push_back(value);
    }
  }

/*
  void pop_back() {
    if (ArrayEnd > SmallSize) {
      vector().pop_back();
    }
    else {
      --ArrayEnd;
    }
  }

  void resize(size_type count, T value = T()) {
    if (count > SmallSize) {

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
    return ArrayEnd > SmallSize;
  }

  std::vector<T>& vector() {
    return VecStore[ArrayEnd - SmallSize - 1];
  }

  const std::vector<T>& vector() const {
    return VecStore[ArrayEnd - SmallSize - 1];
  }

  void overflow() { 
    VecStore.push_back(std::vector<T>(Array, Array + ArrayEnd));
    ArrayEnd += VecStore.size();
  }

  T Array[SmallSize];
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

template <class T, unsigned int SmallSize, class Alloc>
void std::swap(SmallVector<T,SmallSize,Alloc> &lhs, SmallVector<T,SmallSize,Alloc> &rhs) {
  lhs.swap(rhs);
} 
*/
