#ifndef UTILITY_H
#define UTILITY_H

#include <iterator>
namespace ft {


template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };


template <typename T>
struct is_integral { static const bool value = false; };

template <>
struct is_integral<bool> { static const bool value = true; };
    
template <>
struct is_integral<char> { static const bool value = true; };

template <>
struct is_integral<signed char> { static const bool value = true; };

template <>
struct is_integral<short int> { static const bool value = true; };

template <>
struct is_integral<int> { static const bool value = true; };

template <>
struct is_integral<long> { static const bool value = true; };

template <>
struct is_integral<long long> { static const bool value = true; };

template <>
struct is_integral<unsigned char> { static const bool value = true; };

template <>
struct is_integral<unsigned short> { static const bool value = true; };

template <>
struct is_integral<unsigned int> { static const bool value = true; };

template <>
struct is_integral<unsigned long> { static const bool value = true; };

template <>
struct is_integral<unsigned long long> { static const bool value = true; };

template <class T>
struct iterator_traits
{
  typedef typename T::value_type value_type;
  typedef typename T::difference_type difference_type;
  typedef typename T::iterator_category iterator_category;
  typedef typename T::pointer pointer;
  typedef typename T::reference reference;
};

template <typename T>
struct iterator_traits<T*>
{
    typedef std::random_access_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::ptrdiff_t                  difference_type;
};

template <class T1, class T2>
struct pair
{
    public:
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;


        pair() : first(), second() {}

        pair(const first_type & first, const second_type & second) : first(first), second(second) {}

        template <typename U, typename V>
        pair(const pair<U, V>& copy) : first(copy.first), second(copy.second) {};

        ~pair() {};

        pair& operator=(const pair & rhs) {
            
            first = rhs.first;
            second = rhs.second;
            
            return (*this);
        }

        

        
        bool operator== (const pair<T1,T2>& rhs)
        { return this->first==rhs.first && this->second==rhs.second; }

        
        bool operator!= (const pair<T1,T2>& rhs)
        { return !(*this==rhs); }

        
        bool operator<  (const pair<T1,T2>& rhs)
        { return this->first<rhs.first || (!(rhs.first<this->first) && this->second<rhs.second); }

        
        bool operator<= (const pair<T1,T2>& rhs)
        { return !(rhs<*this); }

        
        bool operator>  (const pair<T1,T2>& rhs)
        { return rhs<*this; }

        
        bool operator>= (const pair<T1,T2>& rhs)
        { return !(*this<rhs); }
};

template <class T1, class T2>
pair<T1,T2> make_pair (T1 x, T2 y) { return ( pair<T1,T2>(x,y) ); }


#define childDir(N) ( N == (N->parent)->right ? RIGHT : LEFT )
#define LEFT  0
#define RIGHT 1
// #define left  child[LEFT]
// #define right child[RIGHT]

enum color_t { BLACK, RED };




template <bool isConst, typename isFalse, typename isTrue>
struct chooseConst {};


template <typename isFalse, typename isTrue>
struct chooseConst<false, isFalse, isTrue>
{
    typedef isFalse type;
};


template <typename isFalse, typename isTrue>
struct chooseConst<true, isFalse, isTrue>
{
    typedef isTrue type;
};

template <class T> struct less : std::binary_function <T,T,bool> {

    typedef T       first_argument_type;
    typedef T       second_argument_type;
    typedef bool    result_type;

  bool operator() (const T& x, const T& y) const {return x<y;}
};
}

#endif
