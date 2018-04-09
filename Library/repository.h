#pragma once

#include <vector>
#include <algorithm>
#include "exceptions.h"
#include "SimplyLinkedList.h"

using namespace std;

template < typename T >
class Repository
{
private:
	SimplyLinkedList<T> elems;
public:
	/*
	The constructor of the class Repository.
	*/
	Repository() {
		//elems.clear();
	}

	/*
	Add function
	@param el Element to be added in repository
	@return 1 if element was added successfuly or 0 otherwise.
	*/
	void add(const T& el);

	/*
	This function gets the position of the element in the list.
	@param el Element to be searched.
	@return Position of the element or -1 if it is not present in the list
	*/
	int getPosition(const T& el) const;

	/*
	This function modifies an element in the list.
	@param oldElement Old element.
	@param newElement New element
	@return 1 if the element was modified or 0 otherwise.
	*/
	void modify(const T& oldElement, const T& newElement);

	/*
	Removes element from the list.
	@param element Element to be removed.
	@return 1 if the element was removed. 0 otherwise.
	*/
	void remove(const T& element);

	/*
	Gets the element from the position given.
	@param index: Index of the wanted element.
	@return The element from the index.
	*/
	T getElement(const int& index) {
		return elems[index];
	}

	/*
	@return Element list.
	*/
	const vector<T>& getAllElements() const {
		vector<T> v;
		v.clear();
		for (int i = 0; i < elems.size(); i++)
			v.push_back(elems[i]);
		return v;
	}
};

template<typename T>
inline void Repository<T>::add(const T& el)
{
	if (getPosition(el) != -1)
		throw RepositoryException("Already in repository.");
	elems.push_back(el);
}

template<typename T>
inline int Repository<T>::getPosition(const T& el) const
{
	for (unsigned i = 0; i < elems.size(); i++)
		if (elems[i] == el)
			return i;
	return -1;
}

template<typename T>
inline void Repository<T>::modify(const T& oldElement, const T& newElement)
{
	int index = getPosition(oldElement);
	if (index == -1)
		throw RepositoryException("Element not found.");
	
	elems[index] = newElement;
}

template<typename T>
inline void Repository<T>::remove(const T& element)
{
	int index = getPosition(element);
	if (index == -1)
		throw RepositoryException("Element not found.");
	elems.erase(elems.begin() + index);
}