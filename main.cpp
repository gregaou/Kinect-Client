#include <iostream>
#include <exception>

#include "network/network.h"
#include "enums/enums.h"
#include "KObjects/kObjects.h"

using namespace std;

//void fonction3() { throw runtime_error("prout"); }
//void fonction2() { fonction3(); }
//void fonction1() { fonction2(); }

int main()
{
	int r = EXIT_SUCCESS;
	#ifdef SINGLETON
		KClient* client;
	#endif

	try
	{
		#ifdef SINGLETON
			client = KClient::instance();
		#else
			client = new KClient();
		#endif
	}
	catch (exception& e)
	{
		#ifdef SINGLETON
			KClient::deleteInstance();
		#else
			delete client;
		#endif

		cout << e.what() << endl;
		KTcpSocket::end();
		return EXIT_FAILURE;
	}

	//*
	try
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
		{
			std::cout << "No Kinect found" << std::endl;
			exit(EXIT_FAILURE);
		}

		std::cout << "Elevation angle : " << sensor.getElevationAngle() << std::endl;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		r =  EXIT_FAILURE;
	}

	/*/
	while (true)
	{
		string msg;

		cout << "Message : ";

		cin >> msg;
        if (msg == "close" || msg == "exit" || msg == "quit")
            break;

		if (!client->sendQuery(msg))
            break;
	}
	//*/

	while (true);

    KTcpSocket::end();
	#ifdef SINGLETON
		KClient::deleteInstance();
	#else
		delete client;
	#endif

    return r;
}

