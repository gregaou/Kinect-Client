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
			int id, bytesPerPixel, pixelDataLength, frameNumber, width, height, timestamp;
			ColorImageFormat format;
			byte* pixelData;

			pixelData = _paquet->data() + 5;
			pixelDataLength = _paquet->bodySize() - 5;
			frameNumber = KPaquet::getUint32(_paquet->data() + 1);

			switch (format)
			{
				case RgbResolution640x480Fps30:
				case YuvResolution640x480Fps15:
				case RawYuvResolution640x480Fps15:
					width = 640;
					height = 480;
					break;
				case RgbResolution1280x960Fps12:
					width = 1280;
					height = 960;
					break;
				default:
					width = height = -1;
					break;
			}

			bytesPerPixel = (width * height) / pixelDataLength;
			timestamp = _paquet->timestamp();

			byte firstByte = (_paquet->data())[0];
			id = firstByte >> 4;
			format = (ColorImageFormat)(firstByte & 0xf);

			std::cout << "id : " << id << std::endl;
			std::cout << "format : " << format << std::endl;
			std::cout << "frame number " << frameNumber << std::endl;

			std::list<KinectSensor*>::const_iterator it;
			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					kEventHandler<ColorImageFrameReadyEventArgs&> handler = sensor->colorFrameReadyCb();
					ColorImageFrameReadyEventArgs arg(bytesPerPixel, pixelDataLength, frameNumber, width, height, timestamp, format, pixelData);
					handler(sensor, arg);
				}
			}
		}

	protected:
		KServerPaquet* _paquet;
		const std::list<KinectSensor*>& _sensors;
};

#endif
