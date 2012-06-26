#ifndef KCLIENT_H
#define KCLIENT_H

#include <iostream>
#include <exception>
#include <vector>
#include <pthread.h>
#include "byte.h"
#include "codes.h"
#include "kTcpSocket.h"
#include "kServerPaquet.h"
#include "kServerListener.h"

//#define SINGLETON

typedef void (*kCallback)(const std::vector<byte>& frame);
class KClient
{
	#ifdef SINGLETON
		private:
			KClient(int port = PORT, std::string host = HOST);
			~KClient(void);
		protected:
			static KClient* client;
		public:
			static KClient* instance(void);
			static void deleteInstance(void);
	#else
		public:
			KClient(int port = PORT, std::string host = HOST);
			~KClient(void);
	#endif

		/* Getters */
        KTcpSocket* socket(void) const;
		ServerCode lastCode(void) const;
		std::string lastMessage(void) const;

		bool sendQuery(const std::string& query, unsigned int ms_timeout = QUERY_MS_TIMEOUT);

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

		ServerCode _lastCode;
		std::string _lastMessage;
};

extern KClient* client;

#endif // KCLIENT_H
