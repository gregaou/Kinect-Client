#include <iostream>
#include <exception>

#include "network/network.h"
#include "kObjects/kObjects.h"
#include "kExceptions/kQueryErrorException.h"

using namespace std;

void kinectProcess(void);

void statusChanged(KinectStatus status)
{
	cout << "Status changed to " << status << endl;
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
	//*/
	KinectSensorCollection sensors = *(KinectSensor::KinectSensors());
	KinectSensor sensor;
	int i, nsensors = sensors.size();

	cout << nsensors << " sensors" << endl;

	for (i=0; i<nsensors; i++)
	{
		KinectStatus status = sensors[i].getStatus();
		cout << "status " << i << " : " << status << endl;

		if (status == Connected)
		{
			sensor = sensors[i];
			break;
		}
	}

	if (i == nsensors)
		throw runtime_error("No Kinect found");

	cout << "Elevation angle : " << sensor.getElevationAngle() << endl;
	int angle = sensor.getElevationAngle();
	int inc = 10;

	while (true)
	{
		if (angle + inc > 27 || angle + inc < -27)
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
	//*/
}
