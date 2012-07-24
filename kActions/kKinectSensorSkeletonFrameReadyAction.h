#ifndef KKINECTSENSORSKELETONFRAMEREADY_H
#define KKINECTSENSORSKELETONFRAMEREADY_H

#include <list>
#include "../enums/enums.h"
#include "../network/kServerPaquet.h"
#include "../kObjects/kObjects.h"
#include "kAction.h"

class KKinectSensorSkeletonFrameReadyAction: public KAction
{
	public:
		KKinectSensorSkeletonFrameReadyAction(KServerPaquet* paquet, const std::list<KinectSensor*>& sensors) :
			_paquet(paquet),
			_sensors(sensors)
		{}

		virtual void exec(void)
		{
			SkeletonFrameReadyEventArgs args;
			args.unserialize(_paquet->data());

			int id = (_paquet->data()[0] << 1) >> 5;

			std::list<KinectSensor*>::const_iterator it;
			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					kEventHandler<SkeletonFrameReadyEventArgs&> handler = sensor->skeletonFrameReadyCb();
					handler(sensor, args);
				}
			}
		}

	protected:
		KServerPaquet* _paquet;
		const std::list<KinectSensor*>& _sensors;
};

#endif
