#ifndef KINECTSENSORCOLLECTION_H
#define KINECTSENSORCOLLECTION_H

/**
 * \file kinectSensorCollection.h
 * \brief C++ version of C# KinectSensorCollection
 * \author Gaëtan Champarnaud
 *
 * Contains a collection of Kinects, each of which is represented by a KinectSensor object. This class is a singleton
 */

#include "kObject.h"
#include "kinectSensor.h"
#include "../other/kEventHandler.h"

class KinectSensor;

class KinectSensorCollection : public KObject
{
	private:
		KinectSensorCollection();

	public:
		~KinectSensorCollection() {}

		/** \brief Gets the intance */
		static KinectSensorCollection* instance(void);
		/** \brief Deletes the instance */
		static void deleteInstance(void);

		/**
		 * \brief Gets the numbers of sensors in the KinectSensorCollection
		 * \return The number of sensors
		 * \see size()
		 */
		int Count() const;
		/**
		 * \brief Gets the numbers of sensors in the KinectSensorCollection
		 * \return The number of sensors
		 * \see Count()
		 */
		inline int size() const { return Count(); }
		/**
		 * \brief Array subscript operator
		 * \param i The desired index
		 * \return The KinectSensor at the specified index
		 */
		KinectSensor operator[](int i) const;

		/* Events */
		KEventHandler<KinectStatus> statusChangedCb(void) const;
		/** \brief Sets the callback that is called when the status of a KinectSensor changes.
		 *  \param cb The function to be called */
		void setStatusChangeCb(KEventHandler<KinectStatus> cb);

	protected:
		static KinectSensorCollection* _sensors;
		KEventHandler<KinectStatus> _statusChangedCb;
};

#endif
