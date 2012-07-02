#ifndef KKINECTSENSORCOLLECTIONSTATUSCHANGEDACTION_H
#define KKINECTSENSORCOLLECTIONSTATUSCHANGEDACTION_H

#include "enums/kinectStatus.h"
#include "network/network.h"
#include "kObjects/kObjects.h"
#include "kAction.h"

class KKinectSensorCollectionStatusChangedAction: public KAction
{
	public:
		KKinectSensorCollectionStatusChangedAction(KServerPaquet* paquet, const std::list<KinectSensor*>& sensors) :
			_paquet(paquet),
			_sensors(sensors)
		{}

		virtual void exec(void)
		{
			std::vector<std::string>* res = KObject::splitString(_paquet->stringData(), SEP);
//			int id = valueOf<int>((*res)[0]);
			KinectStatus newStatus = (KinectStatus)valueOf<int>((*res)[1]);

			KinectSensorCollection* sensors = KinectSensorCollection::instance();
			sensors->statusChangedCb()(newStatus);

			delete res;
		}

	protected:
		KServerPaquet* _paquet;
		const std::list<KinectSensor*>& _sensors;
};

#endif
