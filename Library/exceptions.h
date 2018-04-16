#pragma once
#include <string>
#include <vector>

class RepositoryException
{
private:
	std::string message;
public:
	/*
	Constructor for RepositoryException class.
	*/
	RepositoryException(const std::string& message) : message{message} {}

	/*
	Gets the string message.
	*/
	std::string getMessage() const {
		return message;
	}
};

class ValidateException
{
private:
	std::vector<std::string> messages;
public:
	/*
	Constructor for ValidateException class.
	*/
	ValidateException(const std::vector<std::string>& messages) : messages{ messages } {}

	/*
	Gets the string message.
	*/
	std::string getMessage() const {
		std::string s = "";
		for (const auto& msg : messages)
			s += msg + "\n";
		return s;
	}
};

class LinkedListException
{
private:
	std::string message;
public:
	/*
	Constructor for LinkedListException class.
	*/
	LinkedListException(const std::string& message) : message{ message } {}

	/*
	Gets the string message.
	*/
	std::string getMessage() const {
		return message;
	}
};