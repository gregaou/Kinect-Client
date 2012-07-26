#include <time.h>
#include "kClient.h"
#include "kClientPaquet.h"
#include "../kActions/kAction.h"
#include "../kExceptions/kConnectionException.h"

const int KClient::PORT = 1337;
const std::string KClient::HOST = "127.0.0.1";
const unsigned int KClient::QUERY_MS_TIMEOUT = 5000;

KClient* KClient::client = 0;

KClient::KClient(std::string host, int port) :
    _socket(0),
    _listener(0),
	_messagePaquet(0),
	_lastCode((ServerCode)0),
	_lastMessage(),
	_sensors(0),
	_logs("logs.txt", std::ios::out)
{
	try
    {
        _socket = new KTcpSocket(port, host);
        _socket->buildAddr();
        _socket->connectToHost();
    }
    catch (std::exception& e)
	{
        std::string err("couldn't initialize kinect client : ");
        throw std::runtime_error(err + e.what());
    }

    pthread_cond_init(&_cond, 0);
    pthread_mutex_init(&_mutex, 0);
    _listener = new KServerListener(_socket, _cond, _messagePaquet);

	if (pthread_create(&_serverListener, 0, &listenerRoutine, (void*)_listener))
		throw std::runtime_error("couldn't start server listener thread");
}

KClient::~KClient()
{
	pthread_cancel(_serverListener);
    if (_socket)
        delete _socket;
    if (_messagePaquet)
        delete _messagePaquet;
    _logs.close();
}

KClient* KClient::instance(std::string host, int port)
{
	if (!client)
		client = new KClient(host, port);

	return client;
}

void KClient::deleteInstance()
{
	if (!client)
		return;

	delete client;
	client = 0;
}

void* KClient::listenerRoutine(void* p)
{
    KServerListener* listener = (KServerListener*)p;
    KServerPaquet* paquet = 0;

    while (true)
    {
		try
		{
			paquet = new KServerPaquet(listener->_socket);

			KAction* action = KAction::getAction(instance(), paquet);
			action->exec();
			delete action;
		}
		catch (KConnectionException& e)
		{
			std::cout << "Connection lost : " << e.what() << std::endl;
			std::cout << "Please restart the client." << std::endl;
			return NULL;
		}
		catch (std::exception& e)
		{
			std::cout << "Warning : " << e.what() << std::endl;
		}
    }

    return NULL;
}

KTcpSocket* KClient::socket() const
{
    return _socket;
}

ServerCode KClient::lastCode() const
{
	return _lastCode;
}

const std::string& KClient::lastMessage() const
{
	return _lastMessage;
}

byte* KClient::lastData() const
{
	return _messagePaquet->data();
}

KServerListener* KClient::listener(void) const
{
	return _listener;
}

const std::list<KinectSensor*>& KClient::sensors(void) const
{
	return _sensors;
}

void KClient::addLog(std::string log)
{
    struct tm* t;
	time_t now;

	time(&now);
	t = localtime(&now);

    _logs << "[" << t->tm_mday << "/" << t->tm_mon+1 << "/" << t->tm_year+1900 << " ";
    _logs << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << "]\t";
    _logs << log.c_str() << std::endl;
}

void KClient::addSensor(KinectSensor* sensor)
{
	_sensors.push_back(sensor);
}

void KClient::removeSensor(KinectSensor* sensor)
{
	_sensors.remove(sensor);
}

bool KClient::sendQuery(const std::string& query, unsigned int ms_timeout)
{
	/* Sending query */
	KClientPaquet cp(query);
	cp.send(_socket);

	/* Passive waiting for server paquet */
	struct timespec t = {time(NULL) + ms_timeout/1000, (ms_timeout%1000) * 1000000};

	pthread_mutex_lock(&_mutex);
	int r = pthread_cond_timedwait(&_cond, &_mutex, &t);
	pthread_mutex_unlock(&_mutex);

	if (r == ETIMEDOUT)
		throw std::runtime_error("server timeout");
	else if (r != 0)
		throw std::runtime_error("pthread_cond_timedwait() failed");

	/* Processing answer */
	_lastCode = (ServerCode)_messagePaquet->id();
	_lastMessage = std::string((const char*)_messagePaquet->data(), _messagePaquet->bodySize());
	_lastMessage.push_back('\0');

	return codeOk(_lastCode);
}

bool KClient::codeOk(ServerCode c)
{
	return (c == QueryOK);
}
