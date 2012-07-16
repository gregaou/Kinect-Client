#include "network/codes.h"
#include "network/kServerListener.h"

#include "kActions.h"

KAction* KAction::getAction(KClient* client, KServerPaquet* paquet)
{
	switch ((ServerCode)paquet->id())
	{
		case KinectSensorCollectionStatusChanged:
			return new KKinectSensorCollectionStatusChangedAction(paquet);
		case KinectSensorColorImageFrameReady:
			return new KKinectSensorColorFrameReadyAction(paquet, client->sensors());
		case KinectSensorDepthImageFrameReady:
			return new KKinectSensorDepthFrameReadyAction(paquet, client->sensors());
		case KinectSensorSkeletonFrameReady:
			return new KKinectSensorSkeletonFrameReadyAction(paquet, client->sensors());
		case KinectSensorAudioDataReady:
			return new KKinectSensorAudioDataReadyAction(paquet, client->sensors());
		case KinectAudioSourceBeamAngleChanged:
			return new KKinectAudioSourceBeamAngleChangedAction(paquet, client->sensors());
		case KinectAudioSourceSoundSourceAngleChanged:
			return new KKinectAudioSourceSoundSourceAngleChangedAction(paquet, client->sensors());
		default:
			return new KMessageAction(paquet, client->listener());
	}
}
