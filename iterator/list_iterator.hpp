#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include <cstddef>
#include "../utility.hpp"

namespace ft {

template<typename T, typename Node, bool B>
struct list_iterator {
    typedef T                                                   value_type;
    typedef long int                                            difference_type;
    typedef typename ft::chooseConst<B, T&, const T&>::type     reference;
    typedef typename ft::chooseConst<B, T*, const T*>::type     pointer;
    typedef std::bidirectional_iterator_tag                     iterator_category;
    typedef Node*                                               nodePtr;

    list_iterator(nodePtr node = 0) : _node(node) {}
    
    list_iterator(const list_iterator<T, Node, false>& src) : _node(src.getNode()) {}

    ~list_iterator() {}

    list_iterator& operator=(const list_iterator & src) {
      if (this != &src)
        _node = src._node;
      return (*this);
    }

    nodePtr getNode() const { return _node; }



    reference operator*() const { return _node->content; }
    pointer operator->() const { return &(_node->content); }

   list_iterator& operator++()         { _node = _node->next; return (*this); }
    list_iterator operator++(int)       { list_iterator res(*this); ++(*this); return (res); };
    list_iterator& operator--()         { _node = _node->prev; return (*this); }
    list_iterator operator--(int)       { list_iterator res(*this); --(*this); return (res); };

    bool operator==(const list_iterator& rhs) const {return _node == rhs.getNode();}
    bool operator!=(const list_iterator& rhs) const {return _node != rhs.getNode();}

    private:
        nodePtr _node;
  };
}

#endif
