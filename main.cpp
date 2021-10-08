#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <stack>
#include <stdlib.h>

#if STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
	
#else
	#include "containers/map.hpp"
	#include "containers/stack.hpp"
	#include "containers/vector.hpp"
#endif
#include <list>

// /**
//     * ------------------------------------------------------------- *
//     * ------------------------ FT::VECTOR ------------------------- *
//     *
//     * - Coplien form:
//     * (constructor):        Construct vector ++++++++++++++++
//     * (destructor):         Destruct vector ++++++++++++++++
//     * operator=:            Assign vector ++++++++++++++++
//     *
//     * - Iterators:
//     * begin:                Return iterator to beginning ++++++++++++++++
//     * end:                  Return iterator to end ++++++++++++++++
//     * rbegin:               Return reverse iterator to reverse beginning ++++++++++++++++
//     * rend:                 Return reverse iterator to reverse end ++++++++++++++++
//     *
//     * - Capacity:
//     * size:                 Return size ++++++++++++++++
//     * max_size:             Return maximum size ++++++++++++++++
//     * resize:               Change size ++++++++++++++++
//     * capacity:             Return size of allocated storage capacity ++++++++++++++++
//     * empty:                Test whether vector is empty ++++++++++++++++
//     * reserve:              Request a change in capacity ++++++++++++++++
//     *
//     * - Element access:
//     * operator[]:           Access element  ++++++++++++++++
//     * at:                   Access element ++++++++++++++++
//     * front:                Access first element ++++++++++++++++
//     * back:                 Access last element ++++++++++++++++
//     *
//     * - Modifiers:
//     * assign:               Assign vector content  ++++++++++++++++
//     * push_back:            Add element at the end ++++++++++++++++
//     * pop_back:             Delete last element ++++++++++++++++
//     * insert:               Insert elements  ++++++++++++++++
//     * erase:                Erase elements  ++++++++++++++++
//     * swap:                 Swap content  ++++++++++++++++
//     * clear:                Clear content  ++++++++++++++++
//     *
//     * - Non-member function overloads:
//     * relational operators: Relational operators for vector  ++++++++++++++++
//     * swap:                 Exchange contents of two vectors  ++++++++++++++++
//     * ------------------------------------------------------------- *
//     */

// *
//     * ------------------------------------------------------------- *
//     * ------------------------- FT::MAP --------------------------- *
//     *
//     * - Coplien form:           
//     * (constructor):    Construct map
//     * (destructor):     Map destructor
//     * operator=:        Assign map
//     *
//     * - Iterators:
//     * begin:            Return iterator to beginning ++++++++++++++++++++++++++++++
//     * end:              Return iterator to end ++++++++++++++++++++++++++++++
//     * rbegin:           Return reverse iterator to reverse beginning ++++++++++++++++++++++++++++++
//     * rend:             Return reverse iterator to reverse end ++++++++++++++++++++++++++++++
//     *
//     * - Capacity:
//     * empty:            Test whether container is empty ++++++++++++++++++++++++++++++
//     * size:             Return container size ++++++++++++++++++++++++++++++
//     * max_size:         Return maximum size ++++++++++++++++++++++++++++++
//     *
//     * - Element access:
//     * operator[]:       Access element ++++++++++++++++++++++++++++++
//     *
//     * - Modifiers:
//     * insert:           Insert elements ++++++++++++++++++++++++++++++
//     * erase:            Erase elements ++++++++++++++++++++++++++++++
//     * swap:             Swap content
//     * clear:            Clear content ++++++++++++++++++++++++++++++
//     *
//     * - Observers:
//     * key_comp:         Return key comparison object ++++++++++++++++++++++++++++++
//     * value_comp:       Return value comparison object ++++++++++++++++++++++++++++++
//     *
//     * - Operations:
//     * find:             Get iterator to element ++++++++++++++++++++++++++++++
//     * count:            Count elements with a specific key ++++++++++++++++++++++++++++++
//     * lower_bound:      Return iterator to lower bound ++++++++++++++++++++++++++++++
//     * upper_bound:      Return iterator to upper bound ++++++++++++++++++++++++++++++
//     * equal_range       Get range of equal elements ++++++++++++++++++++++++++++++
//     * ------------------------------------------------------------- *





#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
#if STL
	std::cout << "---- std results ----" << std::endl;
#else
	std::cout << "---- ft results ----" << std::endl;
#endif
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::map<int, int> map_int;
	std::map<int, int> map_int_std;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	ft::vector<int> vector_int_ft;
	std::vector<int> vector_int_std;
	time_t start_vec1_ft = clock();
	for (int i = 0; i < COUNT; ++i)
	{
		vector_int.push_back(rand());
	}
	time_t end_vec1_ft = clock();
    std::cout << "vec push duration : " << (end_vec1_ft - start_vec1_ft)  << std::endl;
	time_t start_vec2_ft = clock();
	vector_int.clear();
	time_t end_vec2_ft = clock();
    std::cout << "vec clear duration : " << (end_vec2_ft - start_vec2_ft) << std::endl;
	time_t start_1_ft = clock();
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}
	time_t end_1_ft = clock();
	
    std::cout << "map insert duration : " << (end_1_ft - start_1_ft) << std::endl;

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;


	
	
	time_t start_2_ft = clock();
	
		ft::map<int, int> copy_ft = map_int;
	
	time_t end_2_ft = clock();
	
    std::cout << "map assign duration : " << (end_2_ft - start_2_ft) << std::endl;
	
	

    ft::vector<int> v;
    v.push_back(4);
    v.push_back(3);
    v.begin();
    v.end();
    v.rbegin();
    v.size();
    v.max_size();
    v.resize(5);
    v.reserve(10);
    v[1] = 2;
    v.at(4);
    v.front();
    v.end();
    v.assign(5, 8);
    v.insert(v.begin(), 9);
    v.erase(--(v.end()));
    ft::vector<int> d;
    d.swap(v);
    v.clear();

    ft::map<int, char> mp;
    std::map<int, char> mpstd;
    ft::map<int, char> copy(mp);
    copy.insert(ft::pair<int, char>(1, 'c'));
    
	
	time_t start_clear_ft = clock();
    map_int.clear();
    time_t end_clear_ft = clock();
	
    std::cout << "clear duration : " << (end_clear_ft - start_clear_ft) << std::endl;
    mp.empty();
    mp.size();
    mp.max_size();
    mp.find(4);
    mp.count(4);
    mp.lower_bound(4);
    mp.upper_bound(4);
    mp.equal_range(4);
    mp.find(4);
    mp.count(4);
    mp.swap(copy);
	return (0);
}
