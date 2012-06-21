#ifndef KCLIENT_H
#define KCLIENT_H

#include <iostream>
#include <exception>
#include <vector>
#include <pthread.h>
#include "byte.h"
#include "kTcpSocket.h"
#include "kServerPaquet.h"

typedef void (*kCallback)(const std::vector<byte>& frame);

class KServerListener
{
    public:
        KServerListener(KTcpSocket*& socket,
                        pthread_cond_t& cond,
                        KServerPaquet*& messagePaquet) :
            _socket(socket),
            _cond(cond),
            _messagePaquet(messagePaquet)
        {
//            pthread_cond_init(&_cond, 0);
        }

        KTcpSocket*& _socket;
        pthread_cond_t& _cond;
        KServerPaquet*& _messagePaquet;
//        pthread_cond_t _cond;
};

class KClient
{
	public:
        KClient(int port = PORT, std::string host = HOST);
		~KClient(void);
        KTcpSocket* socket(void) const;
        bool sendQuery(std::string query, unsigned int ms_timeout = QUERY_MS_TIMEOUT);

	protected:
        static void* listenerRoutine(void* p);
        static const int PORT;
        static const std::string HOST;
        static const unsigned int QUERY_MS_TIMEOUT;

		KTcpSocket* _socket;
        pthread_t _serverListener;

        KServerListener* _listener;
        KServerPaquet* _messagePaquet;
        pthread_cond_t _cond;
        pthread_mutex_t _mutex;
};

#endif // KCLIENT_H
