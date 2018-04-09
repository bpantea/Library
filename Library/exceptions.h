#pragma once
#include <string>
#include <vector>

class RepositoryException
{
private:
	std::string message;
public:
	RepositoryException(const std::string& message) : message{message} {}

	std::string getMessage() const {
		return message;
	}
};

class ValidateException
{
private:
	std::vector<std::string> messages;
public:
	ValidateException(const std::vector<std::string>& messages) : messages{ messages } {}

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
	LinkedListException(const std::string& message) : message{ message } {}

	std::string getMessage() const {
		return message;
	}
};