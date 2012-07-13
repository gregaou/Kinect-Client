#ifndef JOINT_H
#define JOINT_H

#include "../enums/jointType.h"
#include "../enums/jointTrackingState.h"
#include "skeletonPoint.h"

class Joint
{
	public:
		Joint(JointType jointType, SkeletonPoint position, JointTrackingState trackingState) :
			_jointType(jointType),
			_position(position),
			_trackingState(trackingState)
		{}

		/* Properties */
		JointType getJointType(void) const							{ return _jointType; }
		SkeletonPoint getPosition(void) const						{ return _position; }
		void setPosition(SkeletonPoint position)					{ _position = position; }
		JointTrackingState getTrackingState(void) const				{ return _trackingState; }
		void setTrackingState(JointTrackingState trackingState)		{ _trackingState = trackingState; }

	protected:
		JointType _jointType;
		SkeletonPoint _position;
		JointTrackingState _trackingState;
};

#endif
