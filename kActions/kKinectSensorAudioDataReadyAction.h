#ifndef KKINECTSENSORAUDIODATAREADYACTION_H
#define KKINECTSENSORAUDIODATAREADYACTION_H

#include <list>
#include "kAction.h"
#include "../network/network.h"
#include "../kObjects/kinectSensor.h"
#include "../other/kEventHandler.h"
#include "../other/audioDataReadyEventArgs.h"

class KKinectSensorAudioDataReadyAction : public KAction
{
	public:
		KKinectSensorAudioDataReadyAction(KServerPaquet* paquet, const std::list<KinectSensor*>& sensors) :
			_paquet(paquet),
			_sensors(sensors)
		{}

		virtual void exec(void)
		{
			int length = _paquet->bodySize() - 1, id = _paquet->data()[0];
			byte* data = _paquet->data() + 1;

//			std::cout << "audio data received : " << std::endl;
//			std::cout << "id = " << id << std::endl;
//			std::cout << "audio data size : " << length << std::endl;

			std::list<KinectSensor*>::const_iterator it;
			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					kEventHandler<AudioDataReadyEventArgs&> handler = sensor->audioDataReadyCb();
					AudioDataReadyEventArgs args(data, length);
					handler(sensor, args);
				}
			}
		}

	protected:
		KServerPaquet* _paquet;
		std::list<KinectSensor*> _sensors;
};

#endif
