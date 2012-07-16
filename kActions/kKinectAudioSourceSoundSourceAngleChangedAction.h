#ifndef KKINECTAUDIOSOURCESOUNDSOURCEANGLECHANGED_H
#define KKINECTAUDIOSOURCESOUNDSOURCEANGLECHANGED_H

#include "kAction.h"
#include "../network/network.h"
#include "../other/kEventHandler.h"
#include "../other/soundSourceAngleChangedEventArgs.h"

class KKinectAudioSourceSoundSourceAngleChangedAction : public KAction
{
	public:
		KKinectAudioSourceSoundSourceAngleChangedAction(KServerPaquet* paquet, const std::list<KinectSensor*>& sensors) :
			_paquet(paquet),
			_sensors(sensors)
		{}

		virtual void exec(void)
		{
			std::vector<std::string>* res = KObject::splitString(_paquet->stringData(), SEP);
			KObject::checkRet(3, res->size());

			int id = valueOf<int>((*res)[0]);
			double angle = valueOf<double>((*res)[1]);
			double confidenceLevel = valueOf<double>((*res)[2]);

			delete res;

			std::list<KinectSensor*>::const_iterator it;
			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					kEventHandler<SoundSourceAngleChangedEventArgs&> handler = sensor->getAudioSource().soundSourceAngleChangedCb();
					SoundSourceAngleChangedEventArgs args(angle, confidenceLevel);
					handler(sensor, args);
				}
			}
		}

	protected:
		KServerPaquet* _paquet;
		std::list<KinectSensor*> _sensors;
};

#endif
