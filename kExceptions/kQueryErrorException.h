#ifndef KQUERYERROREXCEPTION_H
#define KQUERYERROREXCEPTION_H

/**
 * \file kQueryErrorException.h
 * \brief This exception is thown if a problem occurs during the processing of a query
 * \author Gaëtan Champarnaud
 */

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

class KQueryErrorException : public std::exception
{
	public:
		/**
		 * \brief Constructor
		 * \param code The error code
		 * \param msg The error message
		 */
		KQueryErrorException(int code, std::string msg) :
			std::exception(),
			_code(code),
			_msg(msg)
		{}

		/** \brief Destructor */
		~KQueryErrorException() throw() {}

		/** \brief Displays the error code and the error message */
		virtual const char* what() const throw()
		{
			std::ostringstream stream;

			stream << "Error " << _code << " : " << _msg;
			return stream.str().c_str();
		}

		/**
		 * \brief Getter for the error code
		 * \return The error code
		 */
		int code(void) const
		{
			return _code;
		}

		/**
		 * \brief Getter for the error message
		 * \return The error message
		 */
		const std::string& msg(void) const
		{
			return _msg;
		}

	protected:
		int _code; /*!< Error code */
		std::string _msg; /*!< Error message */
};


#endif
