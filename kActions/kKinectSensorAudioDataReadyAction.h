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
			int id = _paquet->data()[0], length = _paquet->bodySize() - 1;
			byte* data = _paquet->data() + 1;

			AudioDataReadyEventArgs args(data, length);

			std::list<KinectSensor*>::const_iterator it;
			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					kEventHandler<AudioDataReadyEventArgs&> handler = sensor->audioDataReadyCb();
					handler(sensor, args);
				}
			}
		}

	protected:
		KServerPaquet* _paquet;
		std::list<KinectSensor*> _sensors;
};

#endif
