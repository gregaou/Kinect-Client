#include <iostream>
#include <fstream>
#include <exception>

#include "network/network.h"
#include "kObjects/kObjects.h"
#include "kExceptions/kQueryErrorException.h"

using namespace std;

void kinectProcess(void);

void statusChanged(KObject* sender, KinectStatus status)
{
	cout << "Status changed to " << status << endl;
}

void colorFrameReady(KObject* sender, ColorImageFrameReadyEventArgs& e)
{
	ColorImageFrame frame = e.openColorImageFrame();

	ostringstream name;
	name << "../image" << frame.getFrameNumber() << ".jpg";
	ofstream f(name.str().c_str(), ios::out);

	if (!f)
	{
		cout << "unable to open " << name << endl;
		return;
	}

	byte* img = new byte[frame.getPixelDataLength()];
	frame.CopyPixelDataTo(img);

	f.write((const char*)img, (streamsize)frame.getPixelDataLength());
	f.close();

	delete img;

	cout << "image saved to " << name.str().c_str() << endl;
}

void depthFrameReady(KObject* sender, DepthImageFrameReadyEventArgs& e)
{
	DepthImageFrame frame = e.openDepthImageFrame();

	cout << "depth frame " << frame.getFrameNumber();

	ostringstream name;
	name << "../image" << frame.getFrameNumber() << ".jpg";
	ofstream f(name.str().c_str(), ios::out);
	int w = frame.getWidth(), h = frame.getHeight();

	if (!f)
	{
		cout << "unable to open " << name << endl;
		return;
	}

	/* Writing ASCII PGM header */
	f << "P2\n" << w << " " << h << "\n255\n";

	int length = frame.getPixelDataLength();
	byte* pixels = new byte[length * sizeof(short)];

	frame.CopyPixelDataTo(pixels);

	for (int j=0; j<h; j++)
	{
		for (int i=0; i<w; i++)
		{
			// discard the portion of the depth that contains only the player index
			short depth = (short)(pixels[(j*w+i)*sizeof(short)] >> frame.getPlayerIndexBitmaskWidth());

			// to convert to a byte we're looking at only the lower 8 bits
			// by discarding the most significant rather than least significant data
			// we're preserving detail, although the intensity will "wrap"
			// add 1 so that too far/unknown is mapped to black
			byte intensity = (byte)((depth + 1) & 0xff);

			f << intensity;
			if (i == w-1)
				f << "\n";
			else
				f << " ";
		}
	}

	delete pixels;

	f.close();
}

int main()
{
	int r = EXIT_SUCCESS;

	try
	{
		kinectProcess();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		r =  EXIT_FAILURE;
	}

	/* Closing */
	KClient::deleteInstance();
	KinectSensorCollection::deleteInstance();
	KTcpSocket::end();

    return r;
}

void kinectProcess()
{
	/*
	KinectSensorCollection* sensors = KinectSensor::KinectSensors();
	sensors->setStatusChangeCb(kEventHandler<KinectStatus>(statusChanged));

	while (true);
	/*/
	KinectSensorCollection sensors = *(KinectSensor::KinectSensors());
	KinectSensor sensor;
	int i, nsensors = sensors.size();
	sensors.setStatusChangeCb(kEventHandler<KinectStatus>(statusChanged));

	cout << nsensors << " sensors" << endl;

	for (i=0; i<nsensors; i++)
	{
		KinectStatus status = sensors[i].getStatus();
		cout << "status " << i << " : " << status << endl;

		if (status == Connected)
		{
			sensor = sensors[i];
			sensor.start();
			break;
		}
	}

	if (i == nsensors)
		throw runtime_error("No Kinect found");

	sensor.setColorFrameReadyCb(kEventHandler<ColorImageFrameReadyEventArgs&>(colorFrameReady));
	sensor.setDepthFrameReadyCb(kEventHandler<DepthImageFrameReadyEventArgs&>(depthFrameReady));
	while (true);

	/*
	vector<short> t;
	for (int i=0; i<320*240; i++)
		t.push_back(1);

	vector<ColorImagePoint>* v = new vector<ColorImagePoint>();
	sensor.MapDepthFrameToColorFrame(Resolution320x240Fps30, t, RgbResolution1280x960Fps12, v);

	SkeletonPoint point = sensor.MapDepthToSkeletonPoint(
								Resolution320x240Fps30,
								10,
								10,
								42);
	cout << "(" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ")" << endl;

	DepthImagePoint p = sensor.MapSkeletonPointToDepth(point, Resolution320x240Fps30);
	cout << "(" << p.getX() << ", " << p.getY() << ")";
	cout << " " << p.getDepth() << " " << p.getPalyerIndex() << endl;
	return;
	*/

	cout << "Elevation angle : " << sensor.getElevationAngle() << endl;
	int angle = sensor.getElevationAngle(), min, max;
	int inc = 2;

	min = sensor.getMinElevationAngle();
	max = sensor.getMaxElevationAngle();

	cout << min << " <= angle <= " << max << endl;

	while (true)
	{
		if (angle + inc > max || angle + inc < min)
			inc *= -1;
		angle += inc;

		try
		{
			sensor.setElevationAngle(angle);
		}
		catch (KQueryErrorException& e)
		{
			cout << e.what() << endl;
			switch (e.code())
			{
				case InvalidOperation:
					angle -= inc;
					break;
				case BadArgument:
					cout << "invalid angle " << angle << endl;
					return;
				default:
					throw runtime_error(e.what());
			}
		}
	}

	sensor.stop();
	//*/
}
