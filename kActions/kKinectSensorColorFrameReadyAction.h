#ifndef KKINECTSENSORCOLORFRAMEREADYACTION_H
#define KKINECTSENSORCOLORFRAMEREADYACTION_H

#include <list>
#include "../enums/enums.h"
#include "../network/kServerPaquet.h"
#include "../kObjects/kObjects.h"
#include "kAction.h"

class KKinectSensorColorFrameReadyAction: public KAction
{
	public:
		KKinectSensorColorFrameReadyAction(KServerPaquet* paquet, const std::list<KinectSensor*>& sensors) :
			_paquet(paquet),
			_sensors(sensors)
		{}

		virtual void exec(void)
		{
			int id, bytesPerPixel, pixelDataLength, frameNumber, width, height, timestamp;
			ColorImageFormat format;
			byte* pixelData;

			byte firstByte = (_paquet->data())[0];
			id = firstByte >> 4;
			format = (ColorImageFormat)(firstByte & 0xf);

			pixelData = _paquet->data() + 5;
			pixelDataLength = _paquet->bodySize() - 5;
			frameNumber = KPaquet::getUint32(_paquet->data() + 1);
			width = getColorImageWidth(format);
			height = getColorImageHeight(format);

			bytesPerPixel = (width * height) / pixelDataLength;
			timestamp = _paquet->timestamp();

			ColorImageFrameReadyEventArgs args(bytesPerPixel, pixelDataLength, pixelData, frameNumber, width, height, timestamp, format);

			std::list<KinectSensor*>::const_iterator it;
			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					kEventHandler<ColorImageFrameReadyEventArgs&> handler = sensor->colorFrameReadyCb();
					handler(sensor, args);
				}
			}
		}

	protected:
		KServerPaquet* _paquet;
		const std::list<KinectSensor*>& _sensors;
};

#endif
