#include "kTcpSocket.h"

static bool first = true;

KTcpSocket::KTcpSocket(int port, std::string host) :
    _port(port),
    _host(host)
{
    if (first)
    {
        #if defined (WIN32)
			WSADATA WSAData;
			if (WSAStartup(MAKEWORD(2,2), &WSAData))
                throw std::runtime_error("WSAStartup failed");
		#endif
	}
	first = false;

    _sock = socket(PF_INET, SOCK_STREAM, 0);
	if (_sock == INVALID_SOCKET)
        throw std::runtime_error("Unable to initialize the socket");

    buildAddr();
	connectToHost();
}

KTcpSocket::~KTcpSocket()
{
    if (_sock != INVALID_SOCKET)
        closesocket(_sock);
}

void KTcpSocket::end()
{
    if (!first)
    {
        #if defined (WIN32)
            WSACleanup();
        #endif
    }
}

void KTcpSocket::writeBuffer(const byte* buffer, size_t len)
{
    int r;
    std::ostringstream msg;

    r = send(_sock, (const char*)buffer, len, 0);

    /* Paquet successffuly send */
    if (r == len)
        return;

    /* Paquet partially send (should not occur) */
    if (r < len)
    {
        msg << r << "/" << len << " bytes written";
        throw std::runtime_error(msg.str());
    }

    /* Error */
    msg << "an error occured writting reading data ";
    if (r == SOCKET_ERROR)
        msg << "(send() error " << errno << ")";
    if (r == 0)
        msg << "(connexion lost)";

    throw std::runtime_error(msg.str());
}

void KTcpSocket::readBuffer(byte* buffer, size_t len)
{
    int r;
    std::ostringstream msg;
    fd_set set;
    struct timeval t;

    msg << "an error occured while reading data ";

    FD_ZERO(&set);
    FD_SET(_sock, &set);
    t.tv_sec = 2;
    t.tv_usec = 0;

    r = select(_sock+1, &set, NULL, NULL, &t);

    if (r < 0)
    {
        msg << "(select() error)" << errno;
        throw std::runtime_error(msg.str());
    }
    if (r == 0)
        throw std::runtime_error("cannot read (server timeout expired)");

    if (FD_ISSET(_sock, &set))
    {
        r = recv(_sock, (char*)buffer, len, 0);
        if (r < 0)
        {
            msg << "(recv() error)" << errno;
            throw std::runtime_error(msg.str());
        }
        if (r == 0)
        {
            msg << "(connexion lost)";
            throw std::runtime_error(msg.str());
        }
    }
}

void KTcpSocket::buildAddr()
{
    _sin.sin_addr.s_addr = inet_addr(_host.c_str());
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(_port);
}

void KTcpSocket::connectToHost()
{
    if (_sock == INVALID_SOCKET)
        throw std::runtime_error("Coudn't connect : invalid socket");

    std::ostringstream msg;
    msg << "Connexion to " << _host << ":" << _port;

    if (connect(_sock, (SOCKADDR*)&_sin, sizeof(_sin)) == SOCKET_ERROR)
    {
        msg << " failed";
        throw std::runtime_error(msg.str());
    }

    msg << " successed";
    std::cout << msg.str() << std::endl;
}

