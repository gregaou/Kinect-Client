#ifndef KCLIENT_H
#define KCLIENT_H

#include <iostream>
#include <exception>
#include <vector>
#include <list>
#include <pthread.h>
#include "byte.h"
#include "codes.h"
#include "kTcpSocket.h"
#include "kServerPaquet.h"
#include "kServerListener.h"

class KinectSensor;

class KClient
{
	private:
		KClient(int port = PORT, std::string host = HOST);
		~KClient(void);

	protected:
		static KClient* client;

	public:
		static KClient* instance(void);
		static void deleteInstance(void);

		/* Getters */
        KTcpSocket* socket(void) const;
		ServerCode lastCode(void) const;
		const std::string& lastMessage(void) const;
		KServerListener* listener(void) const;
		const std::list<KinectSensor*>& sensors(void) const;

		/* Methods */
		void addSensor(KinectSensor* sensor);
		void removeSensor(KinectSensor* sensor);
		bool sendQuery(const std::string& query, unsigned int ms_timeout = QUERY_MS_TIMEOUT);
		static bool codeOk(ServerCode c);

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
		std::list<KinectSensor*> _sensors;
};

extern KClient* client;

#endif
