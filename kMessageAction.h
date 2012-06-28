#ifndef KMESSAGEACTION_H
#define KMESSAGEACTION_H

#include "kAction.h"
#include "network/network.h"

class KMessageAction: public KAction
{
	public:
		KMessageAction(KServerListener* listener, KServerPaquet* paquet) :
			_listener(listener),
			_paquet(paquet)
		{}

		virtual void exec(void)
		{
			_listener->_messagePaquet = _paquet;
			if (pthread_cond_signal(&_listener->_cond))
				throw std::runtime_error("pthread_cond_signal() failed");
		}

	protected:
		KServerListener* _listener;
		KServerPaquet* _paquet;
};

#endif
