#ifndef KACTION_H
#define KACTION_H

/**
 * \file kAction.h
 * \brief
 * \author Gaëtan Champarnaud
 */

#include "../network/network.h"

class KAction
{
	public:
		virtual ~KAction() {}
		static KAction* getAction(KClient* client, KServerPaquet* paquet);
		virtual void exec(void) = 0;
};

#endif
