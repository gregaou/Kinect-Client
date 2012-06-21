#include "codes.h"
#include "kClient.h"
#include "kClientPaquet.h"

const int KClient::PORT = 1337;
const std::string KClient::HOST = "192.168.56.1";
const unsigned int KClient::QUERY_MS_TIMEOUT = 2000;

KClient::KClient(int port, std::string host) :
    _socket(0),
    _listener(0),
    _messagePaquet(0)
{
    try
    {
        _socket = new KTcpSocket(port, host);
        _socket->buildAddr();
        _socket->connectToHost();
    }
    catch (std::exception& e)
    {
        if (_socket)
            delete _socket;
        _socket = 0;

        std::string err("couldn't initialize kinect client : ");
        throw std::runtime_error(err + e.what());
    }

    pthread_cond_init(&_cond, 0);
    pthread_mutex_init(&_mutex, 0);
    _listener = new KServerListener(_socket, _cond, _messagePaquet);

    if (pthread_create(&_serverListener, 0, &listenerRoutine, (void*)_listener))
    {
        if (_socket)
            delete _socket;
        _socket = 0;
        throw std::runtime_error("couldn't start stream listener thread");
    }
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

void* KClient::listenerRoutine(void* p)
{
    KServerListener* listener = (KServerListener*)p;
    KServerPaquet* paquet = 0;

    while (true)
    {
        paquet = new KServerPaquet(listener->_socket);

        switch ((ServerCode)paquet->id())
        {
            case ColorStream:
                break;
            case SkeletonStream:
                break;
            /* ... */
            default:
                listener->_messagePaquet = paquet;
                if (pthread_cond_signal(&listener->_cond))
                    throw std::runtime_error("pthread_cond_signal() failed");
                break;
        }
    }

    return NULL;
}

KTcpSocket* KClient::socket() const
{
    return _socket;
}

bool KClient::sendQuery(std::string query, unsigned int ms_timeout)
{
    try
    {
        /* Sending query */
        KClientPaquet cp(query);
        cp.send(_socket);

        /* Passive waiting for server paquet */
        struct timespec t = {time(NULL) + ms_timeout/1000, (ms_timeout%1000) * 1000000};
        int r = pthread_cond_timedwait(&_cond, &_mutex, &t);

        if (r == ETIMEDOUT)
            throw std::runtime_error("server timeout");
        else if (r)
            throw std::runtime_error("pthread_cond_timedwait");

        /* Processing answer */
        ServerCode code = (ServerCode)_messagePaquet->id();
        std::string answer((const char*)_messagePaquet->data(), _messagePaquet->bodySize());
        answer.push_back('\0');

        if (code != QueryOK)
        {
            std::ostringstream msg;
            msg << "Error " << code << " : " << answer;
            throw std::runtime_error(msg.str());
        }
        else
            std::cout << "Query successfully processed" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}
