#ifndef KINECTSENSORCOLLECTION_H
#define KINECTSENSORCOLLECTION_H

#include "kObject.h"
#include "kEventHander.h"
#include "kinectSensor.h"

class KinectSensor;

class KinectSensorCollection : public KObject
{
	private:
		KinectSensorCollection();

	public:
		~KinectSensorCollection() {}

		static KinectSensorCollection* instance(void);
		static void deleteInstance(void);

		int Count() const;
		inline int size() const { return Count(); }
		KinectSensor operator[](int i) const;
		kEventHandler<KinectStatus> statusChangedCb(void) const;
		void setStatusChangeCb(kEventHandler<KinectStatus> cb);

	protected:
		static KinectSensorCollection* _sensors;
		/* Event callback */
		kEventHandler<KinectStatus> _statusChangedCb;
};

#endif
