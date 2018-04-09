#pragma once

#include "service.h"
#include <cassert>
#include "exceptions.h"
#include "SimplyLinkedList.h"

class Tests
{
private:

	/*
	Test Book class.
	*/
	void testBook();
	/*
	Test Repository class.
	*/
	void testRepository();

	/*
	Test add method of class Service
	*/
	void testServiceAdd();

	/*
	Test modify method of class Service
	*/
	void testServiceModify();

	/*
	Test remove method of class Service
	*/
	void testServiceRemove();

	/*
	Test sort method of class Service
	*/
	void testServiceSort();

	/*
	Test filter method of class Service
	*/
	void testServiceFilter();

public:
	/*
	Run all tests.
	*/
	void run();
};