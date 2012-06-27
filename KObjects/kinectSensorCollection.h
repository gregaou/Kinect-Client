#ifndef KINECTSENSORCOLLECTION_H
#define KINECTSENSORCOLLECTION_H

#include "kObject.h"
#include "kinectSensor.h"

class KinectSensor;

class KinectSensorCollection : public KObject
{
	friend KinectSensorCollection sensors(void);

	private:
		KinectSensorCollection();

	public:
		int Count() const;
		inline int size() const { return Count(); }
		KinectSensor operator[](int i) const;
};

KinectSensorCollection sensors(void);


#endif
