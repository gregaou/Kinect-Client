#include "kinectSensor.h"

KinectSensor::KinectSensor(int id) :
	KObject("KinectSensor", id)
{
}

KinectSensorCollection KinectSensor::KinectSensors()
{
	return sensors();
}



