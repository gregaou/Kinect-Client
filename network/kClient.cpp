#include "kClient.h"
#include "kClientPaquet.h"
#include "kAction.h"

const int KClient::PORT = 1337;
const std::string KClient::HOST = "192.168.3.23";
const unsigned int KClient::QUERY_MS_TIMEOUT = 5000;

#ifdef SINGLETON
	KClient* KClient::client = 0;
#else
	KClient* client = 0;
#endif

KClient::KClient(int port, std::string host) :
    _socket(0),
    _listener(0),
	_messagePaquet(0),
	_lastCode((ServerCode)0),
	_lastMessage()
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
    if (pthread_cancel(_serverListener))
        std::cout << "pthread_cancel failed" << std::endl;
    if (_socket)
        delete _socket;
    if (_messagePaquet)
        delete _messagePaquet;
}

#ifdef SINGLETON
KClient* KClient::instance()
{
	if (!client)
		client = new KClient();

	return client;
}

void KClient::deleteInstance()
{
	if (!client)
		return;

	delete client;
	client = 0;
}
#endif

void* KClient::listenerRoutine(void* p)
{
    KServerListener* listener = (KServerListener*)p;
    KServerPaquet* paquet = 0;

    while (true)
    {
		try
		{
			paquet = new KServerPaquet(listener->_socket);

			KAction* action = KAction::getAction(listener, paquet);
			action->exec();
			delete action;
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

std::string KClient::lastMessage() const
{
	return _lastMessage;
}

bool KClient::sendQuery(const std::string& query, unsigned int ms_timeout)
{
	/* Sending query */
	KClientPaquet cp(query);
	cp.send(_socket);

	/* Passive waiting for server paquet */
	struct timespec t = {time(NULL) + ms_timeout/1000, (ms_timeout%1000) * 1000000};
	int r = pthread_cond_timedwait(&_cond, &_mutex, &t);

	if (r == ETIMEDOUT)
		throw std::runtime_error("server timeout");
	else if (r != 0)
		throw std::runtime_error("pthread_cond_timedwait() failed");

	/* Processing answer */
	_lastCode = (ServerCode)_messagePaquet->id();
	_lastMessage = std::string((const char*)_messagePaquet->data(), _messagePaquet->bodySize());
	_lastMessage.push_back('\0');

	return (_lastCode == QueryOK);
}
