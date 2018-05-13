#pragma once
#include <string>
#include <vector>

class Exception
{
protected:
	std::string message;
public:
	/*
	Constructor for Exception class.
	*/
	Exception(const std::string& message) : message{ message } {}

	/*
	Gets the string message.
	*/
	virtual std::string getMessage() const {
		return message;
	}
};


class RepositoryException : public Exception
{
public:
	/*
	Constructor for RepositoryException class.
	*/
	RepositoryException(const std::string& message) : Exception{message} {}

	/*
	Gets the string message.
	*/
	std::string getMessage() const override {
		return message;
	}
};

class ValidateException : public Exception
{
private:
	std::vector<std::string> messages;
public:
	/*
	Constructor for ValidateException class.
	*/
	ValidateException(const std::vector<std::string>& messages) : messages{ messages }, Exception{ getMessage() } {}

	/*
	Gets the string message.
	*/
	std::string getMessage() const override {
		std::string s = "";
		for (const auto& msg : messages)
			s += msg + "\n";
		return s;
	}
};

class LinkedListException : public Exception
{
public:
	/*
	Constructor for LinkedListException class.
	*/
	LinkedListException(const std::string& message) : Exception{ message } {}

	/*
	Gets the string message.
	*/
	std::string getMessage() const override {
		return message;
	}
};