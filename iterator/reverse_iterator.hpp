#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include <cstddef>
#include "../utility.hpp"
#include "iterator.hpp"

namespace ft {

template<typename Category, typename T, bool B>
struct reverse_iterator {
    typedef T         value_type;
    typedef long int  difference_type;
    typedef typename ft::chooseConst<B, T&, const T&>::type     reference;
    typedef typename ft::chooseConst<B, T*, const T*>::type     pointer;
    typedef Category  iterator_category;

    reverse_iterator() : m_ptr(NULL) {}
    reverse_iterator(pointer ptr) : m_ptr(ptr) {}

    reverse_iterator(const reverse_iterator<Category, T, false>& src) : m_ptr(src.getPtr()) {}
    reverse_iterator(const iterator<Category, T, false>& src) : m_ptr(src.getPtr() - 1) {}
    reverse_iterator(const iterator<Category, T, true>& src) : m_ptr(src.getPtr() - 1) {}

    ~reverse_iterator() {}
    reverse_iterator& operator=(const reverse_iterator & src) {
      if (*this != src)
        m_ptr = src.m_ptr;
      return (*this);
    }

    pointer getPtr() const { return m_ptr; }

    iterator<Category, T, B> base() const {
      reverse_iterator tmp(*this);
      tmp--;
      iterator<Category, T, B> it(tmp.getPtr());
      return it;
    }

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    // Prefix increment
    reverse_iterator& operator++() { m_ptr--; return *this; }  
    reverse_iterator& operator--() { m_ptr++; return *this; }  

    // Postfix increment
    reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
    reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return tmp; }

    friend bool operator==(const reverse_iterator& lhs, const reverse_iterator& rhs) {return lhs.getPtr() == rhs.getPtr();}
    friend bool operator!=(const reverse_iterator& lhs, const reverse_iterator& rhs) {return lhs.getPtr() != rhs.getPtr();}
    friend bool operator<=(const reverse_iterator& lhs, const reverse_iterator& rhs) {return lhs.getPtr() >= rhs.getPtr();}
    friend bool operator>=(const reverse_iterator& lhs, const reverse_iterator& rhs) {return lhs.getPtr() <= rhs.getPtr();}
    friend bool operator>(const reverse_iterator& lhs, const reverse_iterator& rhs) {return lhs.getPtr() < rhs.getPtr();}
    friend bool operator<(const reverse_iterator& lhs, const reverse_iterator& rhs) {return lhs.getPtr() > rhs.getPtr();}

    reverse_iterator operator+=(int n) {
      m_ptr -= n;
      return (*this);
    }

    reverse_iterator operator+(int n) const {
      reverse_iterator it(*this);
      it.m_ptr -= n;
      return (it);
    }

    reverse_iterator operator-=(int n) {
      m_ptr += n;
      return (*this);
    }

    reverse_iterator operator-(int n) const {
      reverse_iterator it(*this);
      it.m_ptr += n;
      return (it);
    }

    reference operator[](int n) const {
      pointer ptr(m_ptr);
      ptr -= n;
      return (*ptr);
    }

    difference_type operator-(reverse_iterator it) const {
      return (it.getPtr() - m_ptr);
    }

    difference_type operator+(reverse_iterator it) const {
      return (it.getPtr() + m_ptr);
    }

    friend reverse_iterator operator+(int n, const reverse_iterator & it) {
      reverse_iterator newIt(it);
      return (newIt += n);
    }

    friend reverse_iterator operator-(int n, const reverse_iterator & it) {
      reverse_iterator newIt(it);
      return (newIt -= n);
    }


    private:
        pointer m_ptr;
  };
}

#endif
