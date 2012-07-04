#include "network/codes.h"
#include "network/kServerListener.h"

#include "kActions.h"

KAction* KAction::getAction(KClient* client, KServerPaquet* paquet)
{
	switch ((ServerCode)paquet->id())
	{
		/*
		case ColorStream:
			return NULL;
		case SkeletonStream:
			return NULL;
			*/
		case KinectSensorCollectionStatusChanged:
			return new KKinectSensorCollectionStatusChangedAction(paquet);
		case KinectSensorColorImageFrameReady:
			return new KKinectSensorColorFrameReadyAction(paquet, client->sensors());
		default:
			return new KMessageAction(paquet, client->listener());
	}
}
