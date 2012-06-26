#include "network/codes.h"
#include "network/kServerListener.h"

#include "kAction.h"
#include "kMessageAction.h"

KAction* KAction::getAction(KServerListener* listener, KServerPaquet* paquet)
{
	switch ((ServerCode)paquet->id())
	{
		/*
		case ColorStream:
			return NULL;
		case SkeletonStream:
			return NULL;
			*/
		default:
			return new KMessageAction(listener, paquet);
	}
}
