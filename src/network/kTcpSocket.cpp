#include "kTcpSocket.h"
#include "../kExceptions/kConnectionException.h"

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
        throw std::runtime_error("unable to initialize the socket");
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
    if (r == (int)len)
        return;

    /* Error */
    if (r <= 0)
    {
        msg << "an error occured writting reading data ";
        if (r == SOCKET_ERROR)
		{
			msg << "(send() error " << errno << ")";
			throw std::runtime_error(msg.str());
		}
		if (r == 0)
			throw KConnectionException(msg.str());
    }

    /* Paquet partially send (should not occur) */
    if (r < (int)len)
    {
        msg << r << "/" << len << " bytes written";
        throw std::runtime_error(msg.str());
    }
}

void KTcpSocket::readBuffer(byte* buffer, size_t len)
{
    int r;
    std::ostringstream msg;
	fd_set set;

    msg << "an error occured while reading data ";

    FD_ZERO(&set);
	FD_SET(_sock, &set);
	//    struct timeval t;
//    t.tv_sec = 2;
//    t.tv_usec = 0;
//    r = select(_sock+1, &set, NULL, NULL, &t);
    r = select(_sock+1, &set, NULL, NULL, NULL);

    if (r < 0)
    {
		msg << "(select() failed)" << errno;
        throw std::runtime_error(msg.str());
    }
    if (r == 0)
		throw std::runtime_error("couldn't read (server timeout expired)");

    if (FD_ISSET(_sock, &set))
    {
		size_t n = 0;

		while (n < len)
		{
			r = recv(_sock, (char*)buffer+n, len-n, 0);
			if (r < 0)
			{
				msg << "(recv() failed)" << errno;
				throw std::runtime_error(msg.str());
			}
			if (r == 0)
				throw KConnectionException(msg.str());

		   n += r;
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
    std::ostringstream msg;

    if (_sock == INVALID_SOCKET)
        throw std::runtime_error("coudn't connect : invalid socket");

    if (connect(_sock, (SOCKADDR*)&_sin, sizeof(_sin)) == SOCKET_ERROR)
    {
        msg << "Connexion to " << _host << ":" << _port << " failed";
        throw std::runtime_error(msg.str());
    }
}

