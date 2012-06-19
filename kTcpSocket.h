#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "byte.h"

#if defined (WIN32)
    #include <winsock2.h>
    //#include <Ws2tcpip.h>
	typedef int socklen_t;
#elif defined (linux)
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#define INVALID_SOCKET		-1
	#define SOCKET_ERROR		-1
	#define closesocket(s)		close(s)
	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
#endif

class KTcpSocket
{
	public:
        KTcpSocket(int port, std::string host = "127.0.0.1");
        ~KTcpSocket();
		static void end(void);
        void writeBuffer(const byte* buffer, size_t len);
        void readBuffer(byte* buffer, size_t len);

	protected:
        void buildAddr(void);
        void connectToHost(void);

		SOCKET _sock;
		SOCKADDR_IN _sin;
		int _port;
		std::string _host;
};

#endif // TCPSOCKET_H
