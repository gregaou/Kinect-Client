#ifndef KCONNECTIONEXCEPTION_H
#define KCONNECTIONEXCEPTION_H

#include <exception>
#include <exception>
#include <stdexcept>

class KConnectionException : public std::runtime_error
{
	public:
		KConnectionException(std::string msg) :
			std::runtime_error(msg)
		{}
};

#endif
