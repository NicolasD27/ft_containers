#ifndef STACK_H
#define STACK_H

#include "../iterator/iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../iterator/list_iterator.hpp"
#include "../utility.hpp"
#include "vector.hpp"
#include <cmath>
#include <memory>
#include <cstdio>
#include <stdexcept>
#include <iostream>

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack
{

public:
    typedef T 			value_type;
    typedef Container	container_type;
    typedef ptrdiff_t	size_type;



    explicit stack (const container_type& ctnr = container_type())
    {
    	c = ctnr;
    }

    ~stack () {}

    bool empty() const
    {
    	return c.empty();
    }

    void pop()
    {
    	c.pop_back();
    }

    void push (const value_type& val)
    {
    	c.push_back(val);
    }

    size_type size() const
    {
    	return c.size();
    }

     value_type& top()
     {
     	return c.back();
     }

	const value_type& top() const
	{
		return c.back();
	}

	friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.c == rhs.c;
	}
    	
    friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (!(lhs == rhs)); }
    	
    
    friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs.c < rhs.c;
    }
    	
    
    friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (!(rhs < lhs)); }
    	
    
    friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (rhs < lhs); }
    	
    
    friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (!(lhs < rhs)); }

protected:
	container_type c;

   
    
};

}
#endif
