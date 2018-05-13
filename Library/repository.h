#pragma once

#include <vector>
#include <algorithm>
#include "exceptions.h"
#include <map>
#include <random>
#include <fstream>

using namespace std;

template < typename T >
class AbstractRepository
{
public:
	/*
	Default constructor for AbstractRepository class.
	*/
	AbstractRepository() = default;

	/*
	Deletes copy constructor
	*/
	AbstractRepository(const AbstractRepository<T>&) = delete;

	/*
	Gives other classes the option to override destructor.
	*/
	virtual ~AbstractRepository() = default;

	/*
	Adds an element in repository.
	*/
	virtual void add(const T&) = 0;

	/*
	Modifies an element in repository.
	*/
	virtual void modify(const T&, const T&) = 0;

	/*
	Removes an element from repository.
	*/
	virtual void remove(const T&) = 0;

	/*
	Gets an element from index
	*/
	virtual T getElement(const int&) = 0;

	/*
	Gets position of an element.
	*/
	virtual int getPosition(const T&) noexcept = 0;

	/*
	Returnes all elements.
	*/
	virtual vector<T> getAllElements() = 0;

	/*
	Returnes the size of repository.
	*/
	virtual int getSize() const = 0;

	virtual void clearRepository() noexcept = 0;
};

template < typename T >
class Repository : public AbstractRepository<T>
{
protected:
	vector<T> elems;

public:
	/*
	The constructor of the class Repository.
	*/
	Repository() : AbstractRepository<T>() {}

	/*
	Add function
	@param el Element to be added in repository
	@return 1 if element was added successfuly or 0 otherwise.
	*/
	void add(const T& el) override {
		if (getPosition(el) != -1)
			throw RepositoryException("Already in repository.");
		elems.push_back(el);
	}

	/*
	This function gets the position of the element in the list.
	@param el Element to be searched.
	@return Position of the element or -1 if it is not present in the list
	*/
	int getPosition(const T& el) noexcept override
	{
		int i = 0;
		for (const auto& it : elems)
		{
			if (it == el)
				return i;
			i++;
		}
		return -1;
	}

	/*
	This function modifies an element in the list.
	@param oldElement Old element.
	@param newElement New element
	@return 1 if the element was modified or 0 otherwise.
	*/
	void modify(const T& oldElement, const T& newElement) override {
		const int index = getPosition(oldElement);
		if (index == -1)
			throw RepositoryException("Element not found.");

		elems[index] = newElement;
	}

	/*
	Removes element from the list.
	@param element Element to be removed.
	@return 1 if the element was removed. 0 otherwise.
	*/
	void remove(const T& element) override {
		const int index = getPosition(element);
		if (index == -1)
			throw RepositoryException("Element not found.");
		elems.erase(elems.begin() + index);
	}

	/*
	Gets the element from the position given.
	@param index: Index of the wanted element.
	@return The element from the index.
	*/
	T getElement(const int& index) {
		if (index == -1)
			throw Exception("Index out of range.");
		return elems[index];
	}

	/*
	@return Element list.
	*/
	vector<T> getAllElements() noexcept override {
		return elems;
	}

	/*
	Gets size of repository.
	*/
	int getSize() const noexcept override {
		return (int)elems.size();
	}

	/*
	Clear repository.
	*/
	virtual void clearRepository() noexcept override {
		elems.clear();
	}
};


template<typename T>
class FileRepository : public Repository<T>
{
	string fileName;
private:
	/*
	Reads all elements from file.
	*/
	void readFromFile() {
		T t;
		ifstream f(fileName);
		while (f >> t)
		{
			//if (f.eof())
				//break;
			Repository<T>::add(t);
		}
		f.close();
	}

	/*
	Writes all elements to file.
	*/
	void writeToFile() {
		ofstream g(fileName);
		for (auto& it : Repository<T>::elems)
			g << it << '\n';
		g.close();
	}

public:
	/*
	Constructor for FileRepository class.
	fileName - name of the file to read/write objects.
	*/
	FileRepository(const string& fileName) : Repository<T>(), fileName{ fileName } {
		readFromFile();
	}

	/*
	Adds an element in repository.
	*/
	void add(const T& el) override {
		Repository<T>::add(el);
		writeToFile();
	}

	/*
	MOdifies an element in repository.
	*/
	void modify(const T& elFrom, const T& elTo) override {
		Repository<T>::modify(elFrom, elTo);
		writeToFile();
	}

	/*
	Remove an element from repository.
	*/
	void remove(const T& el) override {
		Repository<T>::remove(el);
		writeToFile();
	}
};


template<typename T>
class MapRepository : public AbstractRepository<T>
{
private:
	map<int, T> all;

	double p;

	/*
	Generate a free key for map all.
	*/
	int generateKey() noexcept {
		const int MAX_INT = 1000000; // 1 mil
		int x = 0;
		while (all.find(x) != all.end())
			x = rand() % MAX_INT;
		return x;
	}

public:
	/*
	Default constructor.
	*/
	MapRepository() : AbstractRepository<T>(), p{ 0 } {}

	MapRepository(double p) : AbstractRepository<T>(), p{ p } {}

	/*
	Adds an element in repository.
	*/
	virtual void add(const T& el) override {
		const int MAX = 100;
		double throwPosibility = double(rand() % MAX) / (MAX - 1);

		if (throwPosibility < p)
			throw Exception("Posibiliy.");

		if (getPosition(el) != -1)
			throw RepositoryException("Element already in repository.");
		all[generateKey()] = el;
	}

	/*
	Modifies an element in repository.
	*/
	virtual void modify(const T& elFrom, const T& elTo) override {
		int pos = getPosition(elFrom);
		if (pos == -1)
			throw RepositoryException("Element not in repository.");
		all[pos] = elTo;
	}

	/*
	Adds an element from repository.
	*/
	virtual void remove(const T& el) override {
		int pos = getPosition(el);
		if (pos == -1)
			throw RepositoryException("Element not in repository.");
		all.erase(pos);
	}

	/*
	Get an element from index.
	*/
	virtual T getElement(const int& index) override {
		if (all.find(index) == all.end())
			throw RepositoryException("Element not in repository.");
		return all[index];
	}

	/*
	Get index of an element.
	*/
	int getPosition(const T& el) noexcept override {
		for (const auto& it : all)
			if (it.second == el)
				return it.first;
		return -1;
	}

	/*
	Get all elements.
	*/
	virtual vector<T> getAllElements() override {
		vector<T> v;
		for (const auto& it : all)
			v.push_back(it.second);
		return v;
	}

	/*
	Get size of repository.
	*/
	virtual int getSize() const override {
		return all.size();
	}

	/*
	Clear repository.
	*/
	virtual void clearRepository() noexcept override {
		all.clear();
	}
};