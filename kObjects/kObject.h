#ifndef KOBJECT_H
#define KOBJECT_H

#include <vector>
#include "../enums/enums.h"
#include "../network/network.h"

#define SEP		"||"

template<typename T>
T valueOf(const std::string& str)
{
	T v;
	std::stringstream stream(str);
	stream >> v;

	return v;
}

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
		KObject(const char* className = "unknown class", int sensorId = -1);
		~KObject() {}
		static std::vector<std::string>* splitString(const std::string& str, const char* sep);
		int sensorId(void) const	{ return _sensorId; }

	protected:
		std::string* buildQuery(const std::string& method, const std::vector<std::string>& args = std::vector<std::string>()) const;
		std::string* buildQuery(const std::string& method, const std::string& arg) const;
		void processQuery(std::string* query, int timeout = KClient::QUERY_MS_TIMEOUT) const;
		const std::string& lastMessage(void) const	{ return _client->lastMessage(); }
		byte* lastData(void) const					{ return _client->lastData();	 }
		static void checkRet(const std::vector<int>& n, int size);
		static void checkRet(int n, int size);

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
