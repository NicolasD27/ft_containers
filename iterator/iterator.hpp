#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>
#include "../utility.hpp"

namespace ft {

template<typename Category, typename T, bool B>
struct iterator {
    typedef T         value_type;
    typedef long int  difference_type;
    typedef typename ft::chooseConst<B, T&, const T&>::type     reference;
    typedef typename ft::chooseConst<B, T*, const T*>::type     pointer;
    typedef Category  iterator_category;

    iterator() : m_ptr(NULL) {}
    iterator(pointer ptr) : m_ptr(ptr) {}
    
    iterator(const iterator<Category, T, false>& src) : m_ptr(src.getPtr()) {}

    ~iterator() {}

    iterator& operator=(const iterator & src) {
      if (*this != src)
        m_ptr = src.m_ptr;
      return (*this);
    }

    pointer getPtr() const { return m_ptr; }



    reference operator*() const { return *m_ptr; }
    pointer operator->() const { return m_ptr; }

    // Prefix increment
    iterator& operator++() { m_ptr++; return *this; }  
    iterator& operator--() { m_ptr--; return *this; }  

    // Postfix increment
    iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
    iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }


    friend bool operator==(const iterator& lhs, const iterator& rhs) {return lhs.getPtr() == rhs.getPtr();}
    friend bool operator!=(const iterator& lhs, const iterator& rhs) {return lhs.getPtr() != rhs.getPtr();}
    friend bool operator<=(const iterator& lhs, const iterator& rhs) {return lhs.getPtr() <= rhs.getPtr();}
    friend bool operator>=(const iterator& lhs, const iterator& rhs) {return lhs.getPtr() >= rhs.getPtr();}
    friend bool operator>(const iterator& lhs, const iterator& rhs) {return lhs.getPtr() > rhs.getPtr();}
    friend bool operator<(const iterator& lhs, const iterator& rhs) {return lhs.getPtr() < rhs.getPtr();}

    iterator operator+=(int n) {
      m_ptr += n;
      return (*this);
    }

    iterator operator+(int n) const {
      iterator it(*this);
      it.m_ptr += n;
      return (it);
    }

    iterator operator-=(int n) {
      m_ptr -= n;
      return (*this);
    }

    iterator operator-(int n) const {
      iterator it(*this);
      it.m_ptr -= n;
      return (it);
    }

    reference operator[](int n) const {
      pointer ptr(m_ptr);
      ptr += n;
      return (*ptr);
    }

    difference_type operator-(iterator it) const {
      return (m_ptr - it.getPtr());
    }
    

    friend iterator operator+(int n, const iterator & it) {
      iterator newIt(it);
      return (newIt += n);
    }

    friend iterator operator-(int n, const iterator & it) {
      iterator newIt(it);
      return (newIt -= n);
    }


    private:
        pointer m_ptr;
  };
}

#endif
