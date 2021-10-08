#ifndef MAP_ITERATOR_H
#define MAP_ITERATOR_H

#include <cstddef>
#include "../utility.hpp"

namespace ft {

template <class Key, class T, class Compare, typename Node, bool B>
struct map_iterator {
    typedef Key                                             key_type;
    typedef Compare                                         key_compare;
    typedef T                                               mapped_type;
    
    typedef ft::pair<const key_type, mapped_type>           value_type;
    typedef long int                                        difference_type;
    typedef size_t                                          size_type;
    
    typedef std::bidirectional_iterator_tag                                     iterator_category;
    typedef typename chooseConst<B, value_type&, const value_type&>::type       reference;
    typedef typename chooseConst<B, value_type*, const value_type*>::type       pointer;
    typedef Node*                                                               nodePtr;

    map_iterator(nodePtr node = 0, nodePtr lastElem = 0, const key_compare& comp = key_compare()) : _node(node), _lastElem(lastElem), _comp(comp) {}
    
    map_iterator(const map_iterator<Key, T, Compare, Node, false>& src) : _node(src.getNode()) {}

    ~map_iterator() {}

    map_iterator& operator=(const map_iterator & src) {
      
        _node = src.getNode();
        _lastElem = src.getLast();
        _comp = src.getComp();
      
      return (*this);
    }

    nodePtr getNode() const { return _node; }
    nodePtr getLast() const { return _lastElem; }
    key_compare getComp() const { return _comp; }



    reference operator*() const { return _node->content; }
    pointer operator->() const { return &(_node->content); }

      map_iterator& operator++()         { _node = _node->next; return (*this); }
    map_iterator operator++(int)       { map_iterator res = *this; ++(*this); return (res); };
    map_iterator& operator--()         { _node = _node->prev; return (*this); }
    map_iterator operator--(int)       { map_iterator res = *this; --(*this); return (res); };

    bool operator==(const map_iterator& rhs) const {return (_node == rhs.getNode());}
    bool operator!=(const map_iterator& rhs) const {return (_node != rhs.getNode());}
    
    private:
        nodePtr _node;
        nodePtr _lastElem;
        key_compare _comp;
  };
}

#endif
