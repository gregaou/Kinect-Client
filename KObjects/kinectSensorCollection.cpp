#include "kinectSensorCollection.h"

KinectSensorCollection::KinectSensorCollection() :
	KObject("KinectSensorCollection")
{
}

int KinectSensorCollection::Count() const
{
	return getQuery<int>(__func__);
}

KinectSensorCollection sensors()
{
	return KinectSensorCollection();
}

KinectSensor KinectSensorCollection::operator[](int i) const
{
	return KinectSensor(i);
}
