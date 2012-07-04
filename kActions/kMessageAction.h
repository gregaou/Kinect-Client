#ifndef KMESSAGEACTION_H
#define KMESSAGEACTION_H

#include "kAction.h"
#include "network/network.h"

class KMessageAction: public KAction
{
	public:
		KMessageAction(KServerPaquet* paquet, KServerListener* listener) :
			_paquet(paquet),
			_listener(listener)
		{}

		virtual void exec(void)
		{
			_listener->_messagePaquet = _paquet;
			if (pthread_cond_signal(&_listener->_cond))
				throw std::runtime_error("pthread_cond_signal() failed");
		}

	protected:
		KServerPaquet* _paquet;
		KServerListener* _listener;
};

#endif
