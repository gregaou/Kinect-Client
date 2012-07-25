#ifndef KCONNECTIONEXCEPTION_H
#define KCONNECTIONEXCEPTION_H

/**
 * \file kConnectionException.h
 * \brief This exception is thown when a connection error occurs
 * \author Gaëtan Champarnaud
 */

#include <exception>
#include <exception>
#include <stdexcept>

class KConnectionException : public std::runtime_error
{
	public:
		/**
		 * \brief Constructor
		 * \param msg The message that will be display on the call of what()
		 */
		KConnectionException(std::string msg) :
			std::runtime_error(msg)
		{}
};

#endif
