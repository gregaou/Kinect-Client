#ifndef KKINECTSENSORCOLORFRAMEREADYACTION_H
#define KKINECTSENSORCOLORFRAMEREADYACTION_H

#include <list>
#include "../enums/enums.h"
#include "../network/kServerPaquet.h"
#include "../kObjects/kObjects.h"

class KKinectSensorColorFrameReadyAction: public KAction
{
	public:
		KKinectSensorColorFrameReadyAction(KServerPaquet* paquet, const std::list<KinectSensor*>& sensors) :
			_paquet(paquet),
			_sensors(sensors)
		{}

		virtual void exec(void)
		{
			byte* msg = _paquet->data();
			int id = msg[0] >> 4, size = _paquet->bodySize() - 1;
			ColorImageFormat format = (ColorImageFormat)(msg[0] & 0xff);

//			std::cout << "id : " << id << std::endl;
//			std::cout << "format : " << (int)format << std::endl;
//			std::cout << _paquet->bodySize() << std::endl;

			msg++;

			std::list<KinectSensor*>::const_iterator it;

			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					std::cout << "calling handler ..." << std::endl;
					kEventHandler<ColorImageFrameReadyEventArgs&> handler = sensor->colorFrameReadyCb();
					ColorImageFrameReadyEventArgs arg(format, msg, size);
					handler(sensor, arg);
				}
			}
		}

	protected:
		KServerPaquet* _paquet;
		const std::list<KinectSensor*>& _sensors;
};

#endif
