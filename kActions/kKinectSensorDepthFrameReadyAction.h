#ifndef KKINECTSENSORDEPTHFRAMEREADYACTION_H
#define KKINECTSENSORDEPTHFRAMEREADYACTION_H

#include <list>
#include "../enums/enums.h"
#include "../network/kServerPaquet.h"
#include "../kObjects/kObjects.h"
#include "kAction.h"

class KKinectSensorDepthFrameReadyAction: public KAction
{
	public:
		KKinectSensorDepthFrameReadyAction(KServerPaquet* paquet, const std::list<KinectSensor*>& sensors) :
			_paquet(paquet),
			_sensors(sensors)
		{}

		virtual void exec(void)
		{
			int id, bytesPerPixel, pixelDataLength, frameNumber, width, height, timestamp;
			DepthImageFormat format;
			int playerIndexBitmask, playerIndexBitmaskWidth;
			byte* pixelData;

			byte firstByte = (_paquet->data())[0];
			id = firstByte >> 4;
			format = (DepthImageFormat)(firstByte & 0xf);

			frameNumber = KPaquet::getUint32(_paquet->data(), 1);
			playerIndexBitmask = KPaquet::getUint32(_paquet->data(), 5);
			playerIndexBitmaskWidth = KPaquet::getUint32(_paquet->data(), 9);
			pixelData = _paquet->data() + 13;
			pixelDataLength = _paquet->bodySize() - 13;

			width = getDepthImageWidth(format);
			height = getDepthImageHeight(format);

			bytesPerPixel = (width * height) / pixelDataLength;
			timestamp = _paquet->timestamp();

			DepthImageFrameReadyEventArgs args(bytesPerPixel, pixelDataLength, pixelData, frameNumber, width, height,
											  timestamp, format, playerIndexBitmask, playerIndexBitmaskWidth, id);

			std::list<KinectSensor*>::const_iterator it;
			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					kEventHandler<DepthImageFrameReadyEventArgs&> handler = sensor->depthFrameReadyCb();
					handler(sensor, args);
				}
			}
		}

	protected:
		KServerPaquet* _paquet;
		const std::list<KinectSensor*>& _sensors;
};

#endif
