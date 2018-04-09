#pragma once

#include "exceptions.h"


template<typename T>
class Node
{
public:
	Node() {
		next = NULL;
	}
	Node(const T& value) : next{ NULL }, value{ value } {}

	void setNext(Node<T>* nxt) {
		next = nxt;
	}
	void setValue(const T& val) {
		value = val;
	}

	T& getValue() {
		return value;
	}
	Node<T>* getNext() const {
		return next;
	}
	T value;

private:
	Node<T> * next;
	//T value;
};

template<typename T>
class SimplyLinkedList
{
private:
	Node<T> *first;
	Node<T> *last;
	int n;

public:
	SimplyLinkedList() {
		n = 0;
		first = last = NULL;
	}

	~SimplyLinkedList() {
		while (first != NULL) {
			Node<T> *q = first;
			first = first->getNext();
			delete q;
		}
	}

	void push_back(const T& value);

	void erase(const int& index);

	T& operator[](int index);

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
	if (index < 0 || index >= n)
		throw LinkedListException("Index out of range.");

	if (index == 0)
	{
		Node<T> * x = first;
		first = first->getNext();
		delete x;
		n--;
		return;
	}
	Node<T> * q = first;

	for (int i = 1; i < index; q = q->getNext(), i++);
	
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

	//return q->getValue();
	return q->value;
}
