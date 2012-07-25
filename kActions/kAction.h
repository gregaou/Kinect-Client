#ifndef KACTION_H
#define KACTION_H

/**
 * \file beamAngleMode.h
 * \brief C++ version of BeamAngleMode enum in C#
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
