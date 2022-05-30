#pragma once
#include <string>
using std::string;

class BaseException {
protected:
	string message;
public:
	//Class constructor
	BaseException(string message) :message(message) {}
	
	//Getter for the message field.
	const string& getMessage() const noexcept {
		return message;
	}
};

class RepositoryException : public BaseException {
public:
	//Class constructor for RepositoryException
	RepositoryException(string message): BaseException(message){}
};

class ValidationException : public BaseException {
public:
	//Class constructor for ValidationException
	ValidationException(string message) : BaseException(message) {}
};

class ContainerException : public BaseException {
public:
	//Class constructor for ValidationException
	ContainerException(string message) : BaseException(message) {}
};