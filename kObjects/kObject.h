#ifndef KOBJECT_H
#define KOBJECT_H

/**
 * \file kObject.h
 * \brief Base class for all the classes that use network
 * \author Gaëtan Champarnaud
 */

#include <vector>
#include "../enums/enums.h"
#include "../network/network.h"

#define SEP		"||"

/**
 * \brief Tries to interprets a string as a specified type
 * \param str The string to be interpreted
 * \return The value of the string in the specified type
 */
template<typename T>
T valueOf(const std::string& str)
{
	T v;
	std::stringstream stream(str);
	stream >> v;

	return v;
}

/**
 * \brief Converts a value from a specified type to a string
 * \param v The value in a specified type
 * \return The resulting string
 */
template<typename T>
std::string toString(T v)
{
	std::ostringstream stream;
	stream << v;

	return stream.str();
}

class KObject
{
	public:
		/**
		 * \brief Constructor
		 * \param className The name of the class
		 * \param sensorId The id of the sensor (index in the sensors collection)
		 *
		 * Both parameters are used to build the queries.
		 */
		KObject(const char* className = "unknown class", int sensorId = -1);
		/** \brief destructor */
		~KObject() {}
		/**
		 * \brief Splits a string into a vector of strings using a specified separator
		 * \param str The string to be split
		 * \param sep The separator
		 * \return A dynamically allocated vector of the resulting strings
		 *
		 * N.B : freeing the result is in charge of the user.
		 */
		static std::vector<std::string>* splitString(const std::string& str, const char* sep);
		/** \brief Gets the sensor id of the object
		 *  \return The sensor id */
		int sensorId(void) const	{ return _sensorId; }
		/**
		 * \brief Checks that a specified size is in a vector
		 * \param n The vector of possible sizes
		 * \param size The size that must match
		 *
		 * This function is used to check that the return of a query matches the number of expected arguments.
		 * It throws a runtime_error exception when the size doesn't match.
		 */
		static void checkRet(const std::vector<int>& n, int size);
		/**
		 * \brief Checks the number of arguments.
		 * \param n Number of expected argument(s)
		 * \param size Arguments received
		 * \see checkRet(const std::vector<int>& n, int size);
		 */
		static void checkRet(int n, int size);

	protected:
		std::string* buildQuery(const std::string& method, const std::vector<std::string>& args = std::vector<std::string>()) const;
		std::string* buildQuery(const std::string& method, const std::string& arg) const;
		void processQuery(std::string* query, int timeout = KClient::QUERY_MS_TIMEOUT) const;
		const std::string& lastMessage(void) const	{ return _client->lastMessage(); }
		byte* lastData(void) const					{ return _client->lastData();	 }

		template<typename T>
		T getQuery(const std::string& method) const
		{
			processQuery(buildQuery(method));
			return valueOf<T>(_client->lastMessage());
		}

		template<typename T>
		void setQuery(const std::string& method, T& v)
		{
			processQuery(buildQuery(method, toString<T>(v)));
		}

	protected:
		const char* _className;
		int _sensorId;
		KClient* _client;
};

#endif
