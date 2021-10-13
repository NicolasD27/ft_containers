#ifndef MAP_H
#define MAP_H

#include "../iterator/iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../iterator/map_iterator.hpp"
#include "../iterator/map_reverse_iterator.hpp"
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
    * ------------------------- FT::MAP --------------------------- *
    *
    * - Coplien form:           
    * (constructor):    Construct map
    * (destructor):     Map destructor
    * operator=:        Assign map
    *
    * - Iterators:
    * begin:            Return iterator to beginning ++++++++++++++++++++++++++++++
    * end:              Return iterator to end ++++++++++++++++++++++++++++++
    * rbegin:           Return reverse iterator to reverse beginning ++++++++++++++++++++++++++++++
    * rend:             Return reverse iterator to reverse end ++++++++++++++++++++++++++++++
    *
    * - Capacity:
    * empty:            Test whether container is empty ++++++++++++++++++++++++++++++
    * size:             Return container size ++++++++++++++++++++++++++++++
    * max_size:         Return maximum size ++++++++++++++++++++++++++++++
    *
    * - Element access:
    * operator[]:       Access element ++++++++++++++++++++++++++++++
    *
    * - Modifiers:
    * insert:           Insert elements ++++++++++++++++++++++++++++++
    * erase:            Erase elements ++++++++++++++++++++++++++++++
    * swap:             Swap content
    * clear:            Clear content ++++++++++++++++++++++++++++++
    *
    * - Observers:
    * key_comp:         Return key comparison object ++++++++++++++++++++++++++++++
    * value_comp:       Return value comparison object ++++++++++++++++++++++++++++++
    *
    * - Operations:
    * find:             Get iterator to element ++++++++++++++++++++++++++++++
    * count:            Count elements with a specific key ++++++++++++++++++++++++++++++
    * lower_bound:      Return iterator to lower bound ++++++++++++++++++++++++++++++
    * upper_bound:      Return iterator to upper bound ++++++++++++++++++++++++++++++
    * equal_range       Get range of equal elements ++++++++++++++++++++++++++++++
    * ------------------------------------------------------------- *
    */

template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > > 
class map
{
    private:
        struct Node {    
            Node* parent;
            Node* left;
            Node* right; 
            pair<const Key, T> content;
            Node* prev;
            Node* next;
        };

       
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef pair<const Key, T> value_type;
    typedef Compare key_compare; 
    typedef Alloc allocator_type;
	typedef typename allocator_type::template rebind<Node>::other node_allocator_type; 
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename ft::map_iterator<key_type, T, key_compare, Node, false>      iterator;
    typedef typename ft::map_iterator<key_type, T, key_compare, Node, true>       const_iterator;
    typedef typename ft::reverse_map_iterator<key_type, T, key_compare, Node, false>  reverse_iterator;
    typedef typename ft::reverse_map_iterator<key_type, T, key_compare, Node, true>   const_reverse_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

private:
    Node* _root;
    Node* _lastElem;
    allocator_type _allocPair;
    node_allocator_type _allocNode;
    key_compare _comp;
    size_type _size;

    class value_compare  : std::binary_function <value_type, value_type, bool>
    {   
        friend class map;
        protected:
            Compare comp;
            value_compare (Compare c) : comp(c) {}
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
    };

public:

    explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _allocPair(alloc), _comp(comp) ,  _size(0) {
        _lastElem = createNode(value_type());        
        _root = _lastElem;
        _root->prev = _lastElem;
        _root->next = _lastElem;
        _lastElem->left = _lastElem;
        _lastElem->right = _lastElem;
        _lastElem->next = _root;
        _lastElem->prev = _root;
    }

    template <class InputIterator>
    map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type()) :   _allocPair(alloc), _comp(comp), _size(0)
    {
        _lastElem = createNode(value_type());
        _root = _lastElem;
        _lastElem->left = _lastElem;
        _lastElem->right = _lastElem;
        _lastElem->next = _root;
        _lastElem->prev = _root;
        insert(first, last);

    }

    map (const map& x) :  _root(NULL), _allocPair(x.get_allocator()), _comp(x.key_comp()), _size(0) {
        _lastElem = createNode(value_type());
        _root = _lastElem;
        _lastElem->left = _lastElem;
        _lastElem->right = _lastElem;
        _lastElem->next = _root;
        _lastElem->prev = _root;
        insertRangeInEmpty(x.begin(), x.end());
    }

    ~map() {
        clear();
        deallocateNode(_lastElem);
    }

    map& operator=(const map& x)
    {
        map tmp(x);
        this->swap(tmp);
        return (*this);
    }

    

    const_iterator  begin() const   { return iterator(_lastElem->next); }
    iterator        begin()         { return iterator(_lastElem->next); }
    const_iterator  end() const     { return const_iterator(_lastElem); }        
    iterator        end()           { return iterator(_lastElem); }
    const_reverse_iterator rbegin() const   { return const_reverse_iterator(_lastElem->prev); }
    reverse_iterator rbegin()               { return reverse_iterator(_lastElem->prev); }
    const_reverse_iterator rend() const     { return const_reverse_iterator(_lastElem); }
    reverse_iterator rend()                 { return reverse_iterator(_lastElem); }

    
    mapped_type& operator[] (const key_type& k)
    {
        return (*((insert(ft::make_pair<const Key, T>(k,mapped_type()))).first)).second;
    } 

    size_type count (const key_type& key) const {
        for (const_iterator it = begin(); it != end(); ++it)
            if (it->first == key)
                return 1;
        return 0;
    }

    iterator find (const key_type& key)
    {
        for (iterator it = begin(); it != end(); ++it)
            if (it->first == key)
                return it;
        return end();
    }
    const_iterator find (const key_type& key) const
    {
        for (const_iterator it = begin(); it != end(); ++it)
            if (it->first == key)
                return it;
        return end();
    }

    iterator lower_bound (const key_type& key)
    {
        Node* current = begin().getNode();
        while (current != _lastElem && _comp(current->content.first, key))
            current = current->next;
        return (iterator(current));
        
    }
    const_iterator lower_bound (const key_type& key) const
    {
        Node* current = begin().getNode();
        while (current != _lastElem && _comp(current->content.first, key))
            current = current->next;
        return (const_iterator(current));
    }

    iterator upper_bound (const key_type& key)
    {
        Node* current = begin().getNode();
        while (current != _lastElem && !_comp(key, current->content.first))
            current = current->next;
        return (iterator(current));
        
    }
    const_iterator upper_bound (const key_type& key) const
    {
        Node* current = begin().getNode();
        while (current != _lastElem && !_comp(key, current->content.first))
            current = current->next;
        return (const_iterator(current));
    }

    pair<const_iterator,const_iterator> equal_range (const key_type& key) const
    {
        return pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
    }
    pair<iterator,iterator>             equal_range (const key_type& key)
    {
        return pair<iterator, iterator>(lower_bound(key), upper_bound(key));
    }

    ft::pair<iterator,bool> insert (const value_type& pair) {
        Node* target = searchNode(_root, pair.first);

        if (target) 
            return (ft::pair<iterator, bool>(iterator(target, _lastElem, _comp), false));
        _size++;
        return ft::pair<iterator, bool>(iterator(insertNode(_root, pair), _lastElem, _comp), true);
    }

    iterator insert (const_iterator position, const value_type& pair)
    {
        iterator it = _root;
        Node* target = NULL;
        for (const_iterator it = position; it != end(); ++it)
            if (!_comp(it->first, pair.first) && !_comp(pair.first, it->first))
                target = it.getNode();
        if (!target)
            for (const_iterator it = begin(); it != position; ++it)
                if (!_comp(it->first, pair.first) && !_comp(pair.first, it->first))
                    target = it.getNode();

        if (target)
            return (iterator(target, _lastElem, _comp));
        _size++;
        return iterator(insertNode(_root, pair), _lastElem, _comp);
    }

    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        for (InputIterator it = first; it != last; ++it)
            insert(*it);
    }

    

    void erase (iterator position)
    {
        Node* N = position.getNode();        
        if ((N->left == _lastElem || N->left == NULL) && (N->right == _lastElem || N->right == NULL))
        {
            if (N->parent)
            {
                if (N == N->parent->right)
                    N->parent->right = N->right;
                else
                    N->parent->left = N->left;
            }
            else
                _root = _lastElem;
            N->next->prev = N->prev;
            N->prev->next = N->next;
            deallocateNode(N);
        }
        else if ((N->left == _lastElem || N->left == NULL))
        {
            if (N->parent)
            {
                if (N == (N->parent)->right)
                    N->parent->right = N->right;
                else
                    N->parent->left = N->right;
            }
            else {
                _root = N->right;
            }
            if (N->right && N->right != _lastElem)
                N->right->parent = N->parent;
            N->right->left = N->left;
            N->next->prev = N->prev;
            N->prev->next = N->next;
            deallocateNode(N);
        }
        else if (N->right == _lastElem || N->right == NULL)
        {
            if (N->parent)
            {
                if (N == (N->parent)->right)
                    N->parent->right = N->left;
                else
                    N->parent->left = N->left;
            }
            else
                _root = N->left;
            if (N->left && N->left != _lastElem)
                N->left->parent = N->parent;
            N->next->prev = N->prev;
            N->prev->next = N->next;
            deallocateNode(N);
        }
        else
        {
            Node* movingUp = N->prev;
            if (movingUp != _lastElem)
            {
                movingUp->next = N->next;
                N->next->prev = movingUp;
                if  (movingUp->parent != N)
                {
                    if (movingUp->left && movingUp->left != _lastElem)
                    {
                        movingUp->parent->right = movingUp->left;
                        movingUp->left->parent = movingUp->parent;
                    }
                }
                if (movingUp != N->right)
                {
                    movingUp->right = N->right;
                    N->right->parent = movingUp;
                }
                if (movingUp != N->left)
                {
                    movingUp->left = N->left;
                    N->left->parent = movingUp;
                }
            }
            else
            {
                movingUp = N->next;                
                movingUp->prev = N->prev;
                N->prev->next = movingUp;
                if  (movingUp->parent != N)
                {
                    if (movingUp->right && movingUp->right != _lastElem)
                    {
                        movingUp->parent->left = movingUp->right;
                        movingUp->right->parent = movingUp->parent;
                    }
                }
                if (movingUp != N->left)
                {
                    movingUp->left = N->left;
                    N->left->parent = movingUp;
                }
                if (movingUp != N->right)
                {
                    movingUp->right = N->right;
                    N->right->parent = movingUp;
                }
            }
            if (N->parent)
            {
                if (N == (N->parent)->right)
                    N->parent->right = movingUp;
                else
                    N->parent->left = movingUp;
            }
            movingUp->parent = N->parent;
            if (_root->content.first == N->content.first)
                _root = movingUp;
            deallocateNode(N);
        }
        _size--;
    }
    
    size_type erase (const key_type& k)
    {
        iterator position = find(k);
        if (position.getNode() != _lastElem)
        {
            erase(position);
            return 1;
        }
        return 0;
    }
    
    void erase (iterator first, iterator last)
    {
        iterator next = first;
        iterator it = next++;
        while (it != last) {
            erase(it);
            if (next != last)
                it = next++;
            else
                it = next;
        }
    }

    void swap (map& x)
    {
        swap(_root, x._root);
        swap(_lastElem, x._lastElem);
        swap(_allocPair, x._allocPair);
        swap(_allocNode, x._allocNode);
        swap(_comp, x._comp);
        swap(_size, x._size);
    }

    void clear() 
    {
        erase(begin(), end());
    }
    
    

    key_compare key_comp() const { return _comp; }
    value_compare value_comp() const { return _comp; }
    allocator_type get_allocator() const { return _allocPair; }
    size_type size() const { return _size; }

    size_type max_size() const
    {
		int offset = 0;
		if (sizeof(value_type) % 8 != 0)
			offset = 4;
        return std::numeric_limits<size_t>::max() / (32 + sizeof(value_type) + offset);
    }

    bool empty() const { return _size == 0; }

    

    friend bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        if (lhs.size() != rhs.size())
            return false;
        for (typename ft::map<Key,T,Compare,Alloc>::const_iterator it = lhs.begin(), ite = rhs.begin(); it != lhs.end() && ite != rhs.end(); ++it, ++ite)
            if (it->first != ite->first || it->second != ite->second)
                return false;
        return true;
    }


    friend bool operator!= ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (!(lhs == rhs));
    }

    friend bool operator<  ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        for (typename ft::map<Key,T,Compare,Alloc>::const_iterator it = lhs.begin(), ite = rhs.begin(); it != lhs.end() && ite != rhs.end(); ++it, ++ite)
        {
            if (it->first < ite->first || (it->first == ite->first && it->second < ite->second))
                return true;
            if (ite->first < it->first || (ite->first == it->first && ite->second < it->second))
                return false;
        }
        return lhs.size() < rhs.size();
    }

    friend bool operator<= ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (!(rhs < lhs));
    }


    friend bool operator>  ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (rhs < lhs);
    }


    friend bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (!(lhs < rhs));
    }


   
private:
    

    Node* createNode(const value_type& pair)
    {
        Node* newNode = _allocNode.allocate(1);

        _allocPair.construct(&newNode->content, pair);
        newNode->parent = NULL;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->next = NULL;
        newNode->prev = NULL;
        return newNode;
    }

    void deallocateNode(Node* del)
    {
        _allocPair.destroy(&del->content);
        _allocNode.deallocate(del, 1);
    }

    Node* searchNode(Node* root, const key_type & key) const
    {
        if (!root || root == _lastElem)
            return NULL;
        if (!_comp(root->content.first, key) && !_comp(key, root->content.first))
            return root;
        if (_comp(key, root->content.first) && root->left && root->left != _lastElem)
            return searchNode(root->left, key);
        if (_comp(root->content.first, key) && root->right && root->right != _lastElem)
            return searchNode(root->right, key);
        return NULL;
    }

    Node* insertNode(Node* insertPos, const value_type& pair) {
        if (_size == 1) {
            _root = createNode(pair);
            _root->left = _lastElem;
            _root->right = _lastElem;
            _lastElem->left = _root;
            _lastElem->right = _root;
            _lastElem->next = _root;
            _lastElem->prev = _root;
            _root->next = _lastElem;
            _root->prev = _lastElem;
            return _root;
        }
        if (!_comp(insertPos->content.first, pair.first) && !_comp(pair.first, insertPos->content.first))
            return NULL;
        if (_comp(pair.first, insertPos->content.first) && insertPos->left && insertPos->left != _lastElem)
            return insertNode(insertPos->left, pair);
        if (_comp(insertPos->content.first, pair.first) && insertPos->right && insertPos->right != _lastElem)
            return insertNode(insertPos->right, pair);
        Node* newNode = createNode(pair);
        newNode->parent = insertPos;
        if (_comp(pair.first, insertPos->content.first) && !insertPos->left) 
            insertPos->left = newNode;
        else if (_comp(insertPos->content.first, pair.first) && !insertPos->right)
            insertPos->right = newNode;
         else if (insertPos->left && _comp(pair.first,insertPos->content.first))
        {
            newNode->left = _lastElem;
            _lastElem->right = newNode;
            insertPos->left = newNode;
        }
        else if (insertPos->right && _comp(insertPos->content.first, pair.first))
        {
            newNode->right = _lastElem;
            _lastElem->left = newNode;
            insertPos->right = newNode;
        }
        adaptTree(newNode);
        return newNode;
    }

    void adaptTree(Node* newNode)
    {
        Node* parent = newNode->parent;
        if (parent->left == newNode)
        {
            newNode->next = parent;
            parent->prev = newNode;
            while (parent && _comp(newNode->content.first, parent->content.first))
                parent = parent->parent;
            if (parent)
            {
                parent->next = newNode;
                newNode->prev = parent;
            }
            else
            {
                _lastElem->next = newNode;
                newNode->prev = _lastElem;
            }
        }
        else
        {
            newNode->prev = parent;
            parent->next = newNode;
            while (parent && _comp(parent->content.first, newNode->content.first))
                parent = parent->parent;
            if (parent)
            {
                parent->prev = newNode;
                newNode->next = parent;
            }
            else
            {
                _lastElem->prev = newNode;
                newNode->next = _lastElem;
            }
        }
    }

    Node* insertInEmpty (const value_type& pair, Node* prev) {
        _size++;

        Node* newNode = createNode(pair);
        newNode->parent = prev;
        newNode->right = _lastElem;
        _lastElem->left = newNode;
        prev->right = newNode;
        newNode->prev = prev;
        prev->next = newNode;
        _lastElem->prev = newNode;
        newNode->next = _lastElem;
        return newNode;
        
    }

    template <class InputIterator>
    void insertRangeInEmpty (InputIterator first, InputIterator last)
    {
        Node* prev = _root;
        for (InputIterator it = first; it != last; ++it) {
            prev = insertInEmpty(*it, prev);
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

template <class Key, class T, class Compare, class Alloc>
void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) { x.swap(y); }
}



   
#endif
