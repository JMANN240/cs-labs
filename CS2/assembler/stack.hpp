#ifndef CS2_STACK_HPP_
#define CS2_STACK_HPP_
////////////////////////////////////////////////////////////////////////////
//
// File: stack.hpp
//
// Programmer:
// Updated:    10/2019
//
//
// Do not change the names of the classes or methods.  Otherwise, instructor
//  tests will not work.
//

#include <new>
#include <cassert>
#include <iostream>
#include "string.hpp"

////////////////////////////////////////////////////////////////////////////
//           
template<typename T> 
class Node {
public:
	Node() {next = 0;}
	Node(const T& elem) {data = elem; next = 0;}
	T data;
	Node<T>* next;
};


////////////////////////////////////////////////////////////////////////////
// CLASS INV:
//
//    
template <typename T>
class stack {
public:
    stack     ();
    stack     (const stack<T>&);
    ~stack    ();
    void      swap      (stack<T>&);
    stack<T>& operator= (stack<T>);
	bool      empty     () const;
	bool      full      () const;
	T         top       () const;
	T         pop       ();
	void      push      (const T&);

private:
	Node<T>   *tos;
};

template <typename T>
stack<T>::stack() {
	tos = 0;
}

template <typename T>
stack<T>::stack(const stack<T>& org) {
	tos = org.tos;
	Node<T>* tmp = org.tos;
	stack<T> tmp_stack;
	while (tmp != 0) {
		tmp_stack.push((*tmp).data);
		tmp = (*tmp).next;
	}
	while (tmp_stack.empty() == false) {
		(*this).push(tmp_stack.pop());
	}
}

template <typename T>
stack<T>::~stack() {
	Node<T>* tmp;
	while (tos != 0) {
		tmp = tos;
		tos = (*tos).next;
		delete tmp;
	}
}

template <typename T>
void stack<T>::swap(stack<T>& rhs) {
	Node<T>* tmp = rhs.tos;
	rhs.tos = tos;
	tos = tmp;
}

template <typename T>
stack<T>& stack<T>::operator= (stack<T> rhs) {
	(*this).swap(rhs);
	return *this;
}

template <typename T>
bool stack<T>::empty() const {
	return (tos == 0);
}

template <typename T>
bool stack<T>::full() const {
	Node<T>* tmp = new Node<T>;
	if (tmp == 0) {
		return true;
	} else {
		delete tmp;
		return false;
	}
}

template <typename T>
T stack<T>::top() const {
	assert(empty() == false);
	return (*tos).data;
}

template <typename T>
T stack<T>::pop() {
        assert(!empty());
	Node<T>* tmp = tos;
	T ret = (*tos).data;
	tos = (*tos).next;
	delete tmp;
	return ret;
}

template <typename T>
void stack<T>::push(const T& elem) {
	Node<T>* new_node = new Node<T>(elem);
	(*new_node).next = tos;
	tos = new_node;
}

#endif

