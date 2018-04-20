#pragma once

#include "exceptions.h"


template<typename T>
class Node
{
public:
	/*
	Constructor for Node class.
	*/
	Node() {
		next = NULL;
	}

	/*
	Constructor for Node class.
	value - T object for the new node.
	*/
	Node(const T& value) : next{ NULL }, value{ value } {}

	/*
	Sets next pointer.
	*/
	void setNext(Node<T>* nxt) {
		next = nxt;
	}

	/*
	Sets new value.
	val - T object
	*/
	void setValue(const T& val) {
		value = val;
	}

	/*
	Gets the reference to value.
	*/
	T& getValue() {
		return value;
	}
	
	/*
	Gets the pointer to the next node.
	*/
	Node<T>* getNext() {
		return next;
	}

private:
	Node<T> * next;
	T value;
};

template<typename T>
class IteratorSimplyLinkedList;

template<typename T>
class SimplyLinkedList
{
private:
	Node<T> *first;
	Node<T> *last;
	int n;

	void copyList(const SimplyLinkedList<T>& other) {
		first = NULL;
		last = NULL;
		n = 0;
		Node<T>* x = other.first;
		while (x != NULL) {
			push_back(x->getValue());
			x = x->getNext();
		}
	}

	void destroyList() {
		while (first != NULL) {
			Node<T> *q = first;
			first = first->getNext();
			delete q;
		}
	}

public:
	/*
	Constructor for SimplyLinkedList class.
	*/
	SimplyLinkedList() {
		n = 0;
		first = last = NULL;
	}

	/*
	Copy constructor for SimplyLinkedList class.
	*/
	SimplyLinkedList(const SimplyLinkedList<T>& other) {
		copyList(other);
	}

	/*
	Destructor for SimplyLinkedList class.
	*/
	~SimplyLinkedList() {
		destroyList();
	}

	friend class IteratorSimplyLinkedList<T>;

	/*
	Begin iterator for SimplyLinkedList class.
	*/
	const IteratorSimplyLinkedList<T> begin() const {
		return IteratorSimplyLinkedList<T>(*this);
	}

	/*
	End iterator for SimplyLinkedList class.
	*/
	const IteratorSimplyLinkedList<T> end() const {
		return IteratorSimplyLinkedList<T>(*this, n);
	}

	/*
	Adds T-object element to the list.
	*/
	void push_back(const T& value);

	/*
	Removes T-object element from the list
	index- index of the element.
	*/
	void erase(const int& index);

	/*
	Overrides operator[] for the class.
	*/
	T& operator[](int index);

	/*
	Overrides = operator.
	*/
	SimplyLinkedList<T>& operator=(const SimplyLinkedList<T>& other) {
		if (this == &other)
			return *this;
		destroyList();
		copyList(other);
		return *this;
	}

	/*
	Returnes number of elements in the list.
	*/
	int size() const {
		return n;
	}
};

template<typename T>
inline void SimplyLinkedList<T>::push_back(const T & value)
{
	Node<T> *x = new Node<T>(value);
	n++;
	if (first == NULL)
	{
		first = x;
		last = x;
	}
	else
	{
		last->setNext(x);
		last = x;
	}
}

template<typename T>
inline void SimplyLinkedList<T>::erase(const int & index)
{
	int newIndex = index;
	if (newIndex < 0 || newIndex >= n)
		throw LinkedListException("Index out of range.");

	if (newIndex == 0)
	{
		Node<T> * x = first;
		first = first->getNext();
		delete x;
		n--;
		return;
	}
	Node<T> * q = first;

	for (int i = 1; i < newIndex; q = q->getNext(), i++);
	
	Node<T> * qNext = q->getNext();
	
	q->setNext(q->getNext()->getNext());
	if (q->getNext() == NULL)
		last = q;

	delete qNext;
	n--;
}

template<typename T>
inline T & SimplyLinkedList<T>::operator[](int index)
{
	if (index < 0 || index >= n)
		throw LinkedListException("Index out of range.");
	
	Node<T> * q = first;
	
	for (int i = 0; i < index; q = q->getNext(), i++);

	return q->getValue();
}


template<typename T>
class IteratorSimplyLinkedList
{
private:
	const SimplyLinkedList<T>& list;
	int poz = 0;
	Node<T>* point;

public:
	/*
	Constructor for IteratorSimplyLinkedList class
	*/
	IteratorSimplyLinkedList(const SimplyLinkedList<T>& v) noexcept;

	/*
	Constructor for IteratorSimplyLinkedList class
	*/
	IteratorSimplyLinkedList(const SimplyLinkedList<T>& v, const int& poz) noexcept;

	/*
	Checks if poz is valid.
	*/
	bool valid() const;

	/*
	Return current element.
	*/
	T& element();

	/*
	The pointer is set to the next element.
	*/
	void next();

	/*
	Overrides the *operator.
	*/
	T& operator*();
	
	/*
	Overrides operator++.
	*/
	IteratorSimplyLinkedList<T>& operator++();

	/*
	Overrides operator==
	*/
	bool operator==(const IteratorSimplyLinkedList<T>& other) {
		return poz == other.poz;
	}

	/*
	Overrides operator!=
	*/
	bool operator!=(const IteratorSimplyLinkedList<T>& other) {
		return !(*this == other);
	}
};

template<typename T>
inline IteratorSimplyLinkedList<T>::IteratorSimplyLinkedList(const SimplyLinkedList<T>& v) noexcept : list{ v }, point{ v.first } {}

template<typename T>
inline IteratorSimplyLinkedList<T>::IteratorSimplyLinkedList(const SimplyLinkedList<T>& v, const int& poz) noexcept : list{ v }, poz{ poz }, point{ v.last } {}

template<typename T>
inline bool IteratorSimplyLinkedList<T>::valid() const
{
	return poz < list.size();
}

template<typename T>
inline T & IteratorSimplyLinkedList<T>::element()
{
	return point->getValue();
}

template<typename T>
inline void IteratorSimplyLinkedList<T>::next()
{
	poz++;
	point = point->getNext();
}

template<typename T>
inline T & IteratorSimplyLinkedList<T>::operator*()
{
	return element();
}

template<typename T>
inline IteratorSimplyLinkedList<T>& IteratorSimplyLinkedList<T>::operator++()
{
	next();
	return *this;
}