#ifndef KSERVERLISTENER_H
#define KSERVERLISTENER_H

#include <pthread.h>
#include "kTcpSocket.h"
#include "kServerPaquet.h"

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
		}

		KTcpSocket*& _socket;
		pthread_cond_t& _cond;
		KServerPaquet*& _messagePaquet;
};


#endif
