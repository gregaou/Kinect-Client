#ifndef KKINECTAUDIOSOURCEBEAMANGLECHANGEDACTION_H
#define KKINECTAUDIOSOURCEBEAMANGLECHANGEDACTION_H

#include "kAction.h"
#include "network/network.h"
#include "../kObjects/kinectAudioSource.h"
#include "../other/kEventHandler.h"
#include "../other/beamAngleChangedEventArgs.h"

class KKinectAudioSourceBeamAngleChangedAction : public KAction
{
	public:
		KKinectAudioSourceBeamAngleChangedAction(KServerPaquet* paquet, const std::list<KinectSensor*>& sensors) :
			_paquet(paquet),
			_sensors(sensors)
		{}

		virtual void exec(void)
		{
			std::vector<std::string>* res = KObject::splitString(_paquet->stringData(), SEP);
			KObject::checkRet(2, res->size());

			int id = valueOf<int>((*res)[0]);
			double angle = valueOf<double>((*res)[1]);

			delete res;

			std::list<KinectSensor*>::const_iterator it;
			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					kEventHandler<BeamAngleChangedEventArgs&> handler = sensor->getAudioSource().beamAngleChangedCb();
					BeamAngleChangedEventArgs args(angle);
					handler(sensor, args);
				}
			}
		}

	protected:
		KServerPaquet* _paquet;
		std::list<KinectSensor*> _sensors;
};

#endif
