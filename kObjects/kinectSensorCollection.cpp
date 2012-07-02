#include "kinectSensorCollection.h"

KinectSensorCollection* KinectSensorCollection::_sensors = 0;

KinectSensorCollection::KinectSensorCollection() :
	KObject("KinectSensorCollection"),
	_statusChangedCb(0)
{
}

KinectSensorCollection* KinectSensorCollection::instance()
{
	if (!_sensors)
		_sensors = new KinectSensorCollection();
	return _sensors;
}

void KinectSensorCollection::deleteInstance()
{
	if (_sensors)
		delete _sensors;
	_sensors = 0;
}

int KinectSensorCollection::Count() const
{
	return getQuery<int>(__func__);
}

KinectSensor KinectSensorCollection::operator[](int i) const
{
	return KinectSensor(i);
}

kEventHandler<KinectStatus> KinectSensorCollection::statusChangedCb() const
{
	return _statusChangedCb;
}

void KinectSensorCollection::setStatusChangeCb(kEventHandler<KinectStatus> cb)
{
	processQuery(buildQuery("StatusChanged"));
	_statusChangedCb = cb;
}
