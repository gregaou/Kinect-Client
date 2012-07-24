#ifndef JOINT_H
#define JOINT_H

#include "unserializable.h"
#include "../network/kPaquet.h"
#include "../enums/jointType.h"
#include "../enums/jointTrackingState.h"
#include "skeletonPoint.h"

class Joint : public Unserializable
{
	public:
		Joint () : _position()  {}
		Joint(JointType jointType, SkeletonPoint position, JointTrackingState trackingState) :
			_jointType(jointType),
			_position(position),
			_trackingState(trackingState)
		{}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			int pos = 0;

			/*
			 *	The first byte contains :
			 *		- 2 bits for the tracking state
			 *		- 6 bits for the joint type (0x3f = 00111111(2))
			 */
			byte b = buffer[pos++];
			_jointType = (JointType)(b & 0x3f);
			_trackingState = (JointTrackingState)(b >> 6);

			_position.setX((float)KPaquet::getUint32(buffer, pos));		pos += 4;
			_position.setY((float)KPaquet::getUint32(buffer, pos));		pos += 4;
			_position.setZ((float)KPaquet::getUint32(buffer, pos));
		}

		virtual int serializedSize(void) const		{ return 1 + 3*4; }

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
