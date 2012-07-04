#ifndef KKINECTSENSORCOLLECTIONSTATUSCHANGEDACTION_H
#define KKINECTSENSORCOLLECTIONSTATUSCHANGEDACTION_H

#include "enums/kinectStatus.h"
#include "network/network.h"
#include "kObjects/kObjects.h"
#include "kAction.h"

class KKinectSensorCollectionStatusChangedAction: public KAction
{
	public:
		KKinectSensorCollectionStatusChangedAction(KServerPaquet* paquet) :
			_paquet(paquet)
		{}

		virtual void exec(void)
		{
			std::vector<std::string>* res = KObject::splitString(_paquet->stringData(), SEP);
//			int id = valueOf<int>((*res)[0]);
			KinectStatus newStatus = (KinectStatus)valueOf<int>((*res)[1]);

			KinectSensorCollection* sensors = KinectSensorCollection::instance();
			kEventHandler<KinectStatus> handler = sensors->statusChangedCb();
			handler(sensors, newStatus);

			delete res;
		}

	protected:
		KServerPaquet* _paquet;
};

#endif
