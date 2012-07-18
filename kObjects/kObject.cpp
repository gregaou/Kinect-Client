#include <string.h>
#include "kObject.h"
#include "../kExceptions/kQueryErrorException.h"

KObject::KObject(const char* className, int sensorId) :
	_className(className),
	_sensorId(sensorId),
	_client(KClient::instance())
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

	return new std::string(queryStream.str());
}

std::string* KObject::buildQuery(const std::string& method, const std::string& arg) const
{
	return buildQuery(method, std::vector<std::string>(1, arg));
}

void KObject::processQuery(std::string* query, int timeout) const
{
	std::cout << *query << std::endl;

	if (!_client->sendQuery(*query, timeout))
		throw KQueryErrorException(_client->lastCode(), _client->lastMessage());

	delete query;
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

void KObject::checkRet(const std::vector<int>& n, int size)
{
	for (unsigned int i=0; i<n.size(); i++)
		if (n[i] == size)
			return;

	throw std::runtime_error("invalid number of arguments");
}

void KObject::checkRet(int n, int size)
{
	std::vector<int> tab(1, n);
	checkRet(tab, size);
}

