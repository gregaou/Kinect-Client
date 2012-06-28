#include <string.h>
#include "kObject.h"
#include "../kQueryErrorException.h"

KObject::KObject(const char* className, int sensorId) :
	_className(className),
	_sensorId(sensorId),
	_client(getClient())
{

}

std::string* KObject::buildQuery(const std::string& method, const std::vector<std::string>& args) const
{
	std::ostringstream queryStream;

	queryStream << _className << SEP << method;
	if (_sensorId >= 0)
		queryStream << SEP << _sensorId;

	for (unsigned int i=0; i<args.size(); i++)
		queryStream << SEP << args[i];

	std::cout << queryStream.str() << std::endl;

	return new std::string(queryStream.str());
}

std::string* KObject::buildQuery(const std::string& method, const std::string& arg) const
{
	return buildQuery(method, std::vector<std::string>(1, arg));
}

void KObject::processQuery(std::string* query) const
{
	if (!_client->sendQuery(*query))
		throw KQueryErrorException(_client->lastCode(), _client->lastMessage());

	delete query;
}

KClient* KObject::getClient()
{
	#ifdef SINGLETON
	KClient* client = KClient::instance();
	#endif

	return client;
}

std::vector<std::string>* KObject::splitString(const std::string& str, const char* sep)
{
	std::vector<std::string>* res = new std::vector<std::string>();
	size_t sepLen = strlen(sep);
	size_t beg = 0, end = 0;

	do
	{
		end = str.find(sep, beg, sepLen);
		res->push_back(str.substr(beg, end-beg));
		beg = end + sepLen;
	} while (end != std::string::npos);

	return res;
}

