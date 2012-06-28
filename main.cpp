#include <iostream>
#include <exception>

#include "network/network.h"
#include "KObjects/kObjects.h"
#include "kQueryErrorException.h"

using namespace std;

void kinectProcess(void);

int main()
{
	int r = EXIT_SUCCESS;
	#ifdef SINGLETON
		KClient* client;
	#endif

	try
	{
		/* Initializing */
		#ifdef SINGLETON
			client = KClient::instance();
		#else
			client = new KClient();
		#endif

		kinectProcess();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		r =  EXIT_FAILURE;
	}

	/* Closing */
    KTcpSocket::end();
	#ifdef SINGLETON
		KClient::deleteInstance();
	#else
		delete client;
	#endif

    return r;
}

void kinectProcess()
{
	KinectSensorCollection sensors = KinectSensor::KinectSensors();
	KinectSensor sensor;
	int i, nsensors = sensors.size();

	std::cout << nsensors << " sensors" << std::endl;

	for (i=0; i<nsensors; i++)
	{
		KinectStatus status = sensors[i].getStatus();
		std::cout << "status " << i << " : " << status << std::endl;

		if (status == Connected)
		{
			sensor = sensors[i];
			break;
		}
	}

	if (i == nsensors)
		throw runtime_error("No Kinect found");

	std::cout << "Elevation angle : " << sensor.getElevationAngle() << std::endl;
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
			switch (e.code())
			{
				case InvalidOperation:
					angle -= inc;
					break;
				case BadArgument:
					std::cout << "invalid angle " << angle << std::endl;
					return;
				default:
					throw runtime_error(e.what());
			}
		}
	}
}

