#ifndef VECTOR_H
#define VECTOR_H

#include "../iterator/iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../iterator/list_iterator.hpp"
#include "../utility.hpp"
#include <cmath>
#include <memory>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <limits>

namespace ft {
/**
    * ------------------------------------------------------------- *
    * ------------------------ FT::VECTOR ------------------------- *
    *
    * - Coplien form:
    * (constructor):        Construct vector ++++++++++++++++
    * (destructor):         Destruct vector ++++++++++++++++
    * operator=:            Assign vector ++++++++++++++++
    *
    * - Iterators:
    * begin:                Return iterator to beginning ++++++++++++++++
    * end:                  Return iterator to end ++++++++++++++++
    * rbegin:               Return reverse iterator to reverse beginning ++++++++++++++++
    * rend:                 Return reverse iterator to reverse end ++++++++++++++++
    *
    * - Capacity:
    * size:                 Return size ++++++++++++++++
    * max_size:             Return maximum size ++++++++++++++++
    * resize:               Change size +++++++1+++++++++
    * capacity:             Return size of allocated storage capacity ++++++++++++++++
    * empty:                Test whether vector is empty ++++++++++++++++
    * reserve:              Request a change in capacity ++++++++++++++++
    *
    * - Element access:
    * operator[]:           Access element  ++++++++++++++++
    * at:                   Access element ++++++++++++++++
    * front:                Access first element ++++++++++++++++
    * back:                 Access last element ++++++++++++++++
    *
    * - Modifiers:
    * assign:               Assign vector content  ++++++++++++++++
    * push_back:            Add element at the end ++++++++++++++++
    * pop_back:             Delete last element ++++++++++++++++
    * insert:               Insert elements  ++++++++++++++++
    * erase:                Erase elements  ++++++++++++++++
    * swap:                 Swap content  ++++++++++++++++
    * clear:                Clear content  ++++++++++++++++
    *
    * - Non-member function overloads:
    * relational operators: Relational operators for vector  ++++++++++++++++
    * swap:                 Exchange contents of two vectors  ++++++++++++++++
    * ------------------------------------------------------------- *
    */
template < class T, class Alloc = std::allocator<T> > 
class vector
{
public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename ft::iterator<std::random_access_iterator_tag, T, false>      iterator;
    typedef typename ft::iterator<std::random_access_iterator_tag, T, true>       const_iterator;
    typedef typename ft::reverse_iterator<std::random_access_iterator_tag, T, false>  reverse_iterator;
    typedef typename ft::reverse_iterator<std::random_access_iterator_tag, T, true>   const_reverse_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    // constructors
    explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0)  {
        _vector = _alloc.allocate(_capacity);
    }
    
    explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc),_size(n), _capacity(n)  {
        _vector = _alloc.allocate(_capacity);
        for (size_type i = 0; i < _size; i++)
            _alloc.construct(&_vector[i], val);        
    }

    template <class InputIterator>
    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value , int>::type* = 0) :  _alloc(alloc) , _size(0)
    {
        InputIterator tmp(first);
        while (tmp++ != last)
            _size++;
        
        _capacity = _size;
        _vector = _alloc.allocate(_capacity);

        for (size_type i = 0; first != last; ++first, ++i)
            _alloc.construct(&_vector[i], *first);
    }

    vector(const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
    {
        _vector = _alloc.allocate(_capacity);
        size_type i = 0;
        for (const_iterator it = x.begin(); it != x.end(); ++it)
        {
            _alloc.construct(&_vector[i++], *it);
        }
    }

    //destructor
    ~vector() {
        for (iterator it = begin(); it != end(); ++it)
            _alloc.destroy(&(*it));
        _alloc.deallocate(_vector, _capacity);
    }

    //assign operator
    vector& operator= (const vector& x) {
        if (x._size > _capacity) {
            _capacity = x._size;
            _vector = _alloc.allocate(_capacity);
        }
        size_type i = 0;
        for (const_iterator it = x.begin(); it != x.end(); ++it)
        {
            if (i < _size)
                _alloc.destroy(&_vector[i]);
            _alloc.construct(&_vector[i++], *it);
        }
        _size = x._size;
        return (*this);
    }

    const_iterator  begin() const   { return const_iterator(_vector); }
    iterator        begin()         { return iterator(_vector); }
    const_iterator  end() const     { return const_iterator(_vector + _size); }        
    iterator        end()           { return iterator(_vector + _size); }
    const_reverse_iterator rbegin() const   { return const_reverse_iterator(_vector + _size - 1); }
    reverse_iterator rbegin()               { return reverse_iterator(_vector + _size - 1); }
    const_reverse_iterator rend() const     { return const_reverse_iterator(_vector - 1); }
    reverse_iterator rend()                 { return reverse_iterator(_vector - 1); }

    allocator_type get_allocator() const { return _alloc; }

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value , int>::type* = 0)
    {
        size_type tmp = _capacity;
        clear();
        _capacity = tmp;
        tmp = 0;
        InputIterator itmp(first);
        while (itmp++ != last)
            tmp++;
        if (tmp > _capacity)
        {
            _alloc.deallocate(_vector, _capacity);
            _vector = _alloc.allocate(tmp);
            _capacity = tmp;
        }
        
        size_type i = 0;
        for (; first != last; ++i, ++first)
            _alloc.construct(&_vector[i], *first);
        _size = i;
        
    }

    void assign (size_type n, const value_type& val)
    {
        size_type tmp = _capacity;
        clear();
        _capacity = tmp;
        if (n > _capacity)
        {
            _alloc.deallocate(_vector, _capacity);
            _vector = _alloc.allocate(n);
            _capacity = n;
        }
        
        for (size_type i = 0; i < n; ++i)
            _alloc.construct(&_vector[i], val);
        _size = n;
        
    }


    

    void push_back (const value_type& val) {
        if (_size >= _capacity)
            reallocVector(!_capacity ? 1 : _capacity * 2);
        _alloc.construct(&_vector[_size++], val);
    }

    void pop_back() {
        if (_size)
            _alloc.destroy(&_vector[_size-- - 1]);
    }

    iterator insert (iterator position, const value_type& val) {
        difference_type index = position - begin();
        insert(position, 1, val);
        return (&_vector[index]);
    }

    void insert (iterator position, size_type n, const value_type& val) {
        difference_type index = position - begin();
        if (_size + n > _capacity)
            reallocVector((2 * _capacity >= _size + n) ? 2 * _capacity : _size + n);
        
        iterator newPosition(&_vector[index]);
        if (newPosition != end())
            moveElementsToTheRight(newPosition, n);
        for (size_type i = 0; i < n; i++)
            _alloc.construct(&(*newPosition++), val);
        _size += n;
    }

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last,  typename ft::enable_if<!ft::is_integral<InputIterator>::value , int>::type* = 0) {
        difference_type index = position - begin();
        size_type len = 0;
        InputIterator tmp(first);
        while (tmp++ != last)
            len++;
        if (_size + len > _capacity)
            reallocVector((2 * _capacity >= _size + len) ? 2 * _capacity : _size + len);

        iterator newPosition(&_vector[index]);
        if (newPosition != end())
            moveElementsToTheRight(newPosition, len);
        for (size_type i = 0; i < len; i++)
            _alloc.construct(&(*newPosition++), *(first++));
        _size += len;
    }

    iterator erase (iterator position) {
        if (position != end())
            moveElementsToTheLeft(position, 1);
        _size--;
        return (position);
    }
    iterator erase (iterator first, iterator last) {
        size_type len = 0;
        iterator tmp(first);
        while (tmp++ != last)
            len++;
        if (first != end())
            moveElementsToTheLeft(first, len);
        _size -= len;
        return (first);
    }
    

    
    void clear() {
        for (iterator it = begin(); it != end(); ++it)
            _alloc.destroy(&*it);
        _size = 0;
    }

    void swap (vector& x) {
        swap(_alloc, x._alloc);
        swap(_vector, x._vector);
        swap(_size, x._size);
        swap(_capacity, x._capacity);
    }

     

    size_type size() const { return _size; }

    size_type max_size() const
    {
        return std::numeric_limits<size_t>::max() / sizeof(value_type);
    }

    void resize (size_type n, value_type val = value_type())
    {
        if (n > _capacity)
            reserve((2 * _capacity >= n) ? 2 * _capacity : n);
        while (_size < n)
            push_back(val);
        while (_size > n)
            pop_back();
    }
    
    size_type capacity() const { return _capacity; }

    bool empty() const { return !_size; }

    void reserve(size_type n)
    {
        if (n > max_size())
            throw std::length_error("vector");
        else if (n > _capacity)
            reallocVector(n);
    }

    reference operator[] (size_type n) { return _vector[n]; }

    const_reference operator[] (size_type n) const { return _vector[n]; }

    reference at (size_type n) {
        if (n >= _size)
            throw std::out_of_range("vector");
        return _vector[n];
    }

    const_reference at (size_type n) const {
        if (n >= _size)
            throw std::out_of_range("vector");
        return _vector[n];
    }

    reference front() { return _vector[0]; }

    const_reference front() const { return _vector[0]; }

    reference back() { return _vector[_size - 1]; }

    const_reference back() const { return _vector[_size - 1]; }

    friend void swap (vector& x, vector& y)                         { x.swap(y); }

    friend bool operator== (const vector& lhs, const vector& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        for (const_iterator ita = lhs.begin(), itb = rhs.begin(); ita != lhs.end(); ita++, itb++) {
            if (*ita != *itb)
                return false;
        }
        return true;
    }
    	
    
    friend bool operator!= (const vector& lhs, const vector& rhs) { return (!(lhs == rhs)); }
    	
    
    friend bool operator<  (const vector& lhs, const vector& rhs) {
        for (const_iterator ita = lhs.begin(), itb = rhs.begin(); ita != lhs.end() && itb != rhs.end(); ita++, itb++) {
            if (*ita < *itb)
                return true;
            if (*itb < *ita)
                return false;
        }
        return lhs.size() < rhs.size();
    }
    	
    
    friend bool operator<= (const vector& lhs, const vector& rhs) { return (!(rhs < lhs)); }
    	
    
    friend bool operator>  (const vector& lhs, const vector& rhs) { return (rhs < lhs); }
    	
    
    friend bool operator>= (const vector& lhs, const vector& rhs) { return (!(lhs < rhs)); }

private:
    pointer _vector;
    allocator_type _alloc;
    size_type _size;
    size_type _capacity;

    void reallocVector(size_type newCapacity) {
        pointer tmp = _alloc.allocate(newCapacity);
        for (size_type i = 0; i < _size; ++i)
            _alloc.construct(&tmp[i], _vector[i]);
        this->~vector();
        _capacity = newCapacity;
        _vector = tmp;
    }

	void moveElementsToTheLeft(iterator pos, size_type n) {
        for (iterator it = pos; it != end() - n; it++) {
            _alloc.destroy(&(*it));
            _alloc.construct(&*it, *(it + n));
        }
    }
    void moveElementsToTheRight(iterator pos, size_type n) {
        for (iterator it = end() - 1; it != pos - 1; --it) {
            _alloc.construct(&(*(it + n)), *it);
            _alloc.destroy(&(*it));
        }
    }

    template <typename U>
    void swap(U& a, U&b)
    {
        U tmp = a;
        a = b;
        b = tmp;
    }
};
}

#endif
