#ifndef KQUERYERROREXCEPTION_H
#define KQUERYERROREXCEPTION_H

#include <exception>
#include <string>

class KQueryErrorException : public std::exception
{
	public:
		KQueryErrorException(int code, std::string msg) :
			std::exception(),
			_code(code),
			_msg(msg)
		{}

		~KQueryErrorException() throw() {}

		virtual const char* what() const throw()
		{
			std::ostringstream stream;

			stream << "Error " << _code << " : " << _msg;
			return stream.str().c_str();
		}

		int code(void) const
		{
			return _code;
		}

		const std::string& msg(void) const
		{
			return _msg;
		}

	protected:
		int _code;
		std::string _msg;
};


#endif
