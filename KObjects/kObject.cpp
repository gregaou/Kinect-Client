#include "kObject.h"

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
	{
		std::ostringstream err;
		std::cout << "Error " << _client->lastCode() << " : "  << _client->lastMessage() << std::endl;
		throw std::runtime_error(err.str());
	}
}

KClient* KObject::getClient()
{
	#ifdef SINGLETON
	KClient* client = KClient::instance();
	#endif

	return client;
}

