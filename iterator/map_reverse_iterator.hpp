#ifndef MAP_REVERSE_ITERATOR_H
#define MAP_REVERSE_ITERATOR_H

#include <cstddef>
#include "../utility.hpp"

namespace ft {

template <class Key, class T, class Compare, typename Node, bool B>
struct reverse_map_iterator {
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


    

    reverse_map_iterator(nodePtr node = 0, nodePtr lastElem = 0, const key_compare& comp = key_compare()) : _node(node), _lastElem(lastElem), _comp(comp) {}
    
    reverse_map_iterator(const reverse_map_iterator<Key, T, Compare, Node, false>& src) : _node(src.getNode()) {}
    reverse_map_iterator(const reverse_map_iterator<Key, T, Compare, Node, true>& src) : _node(src.getNode()) {}
    reverse_map_iterator(const map_iterator<Key, T, Compare, Node, false>& src, nodePtr lastElem = 0, const key_compare& comp = key_compare()) : _node(src.getNode()->prev), _lastElem(lastElem), _comp(comp) {}
    reverse_map_iterator(const map_iterator<Key, T, Compare, Node, true>& src, nodePtr lastElem = 0, const key_compare& comp = key_compare()) : _node(src.getNode()->prev), _lastElem(lastElem), _comp(comp) {}

    ~reverse_map_iterator() {}

    reverse_map_iterator& operator=(const reverse_map_iterator & src) {
        _node = src.getNode();
        _lastElem = src.getLast();
        _comp = src.getComp();
        return (*this);
    }

    map_iterator<Key, T, Compare, Node, B> base() const {
      reverse_map_iterator tmp(*this);
      tmp--;
      map_iterator<Key, T, Compare, Node, B> it(tmp.getNode(), _lastElem, _comp);
      return it;
    }

    nodePtr getNode() const { return _node; }
    nodePtr getLast() const { return _lastElem; }
    key_compare getComp() const { return _comp; }



    reference operator*() const { return _node->content; }
    pointer operator->() const { return &(_node->content); }

      reverse_map_iterator& operator++()         { _node = _node->prev; return (*this); }
    reverse_map_iterator operator++(int)       { reverse_map_iterator res(*this); ++(*this); return (res); };
    reverse_map_iterator& operator--()         { _node = _node->next; return (*this); }
    reverse_map_iterator operator--(int)       { reverse_map_iterator res(*this); --(*this); return (res); };

    bool operator==(const reverse_map_iterator& rhs) const {return _node == rhs._node;}
    bool operator!=(const reverse_map_iterator& rhs) const {return _node != rhs._node;}

    private:
        nodePtr _node;
        nodePtr _lastElem;
        key_compare _comp;
  };
}

#endif
