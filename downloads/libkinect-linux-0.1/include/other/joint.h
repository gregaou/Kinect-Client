#ifndef JOINT_H
#define JOINT_H

/**
 * \file joint.h
 * \brief C++ version of C# Joint
 * \author Gaëtan Champarnaud
 *
 * Contains joint data for one skeleton joint; joint data includes information such as the joint type, position and whether or not the joint is being tracked.
 */

#include "unserializable.h"
#include "../network/kPaquet.h"
#include "../enums/jointType.h"
#include "../enums/jointTrackingState.h"
#include "skeletonPoint.h"

class Joint : public Unserializable
{
	public:
		Joint () : _position()  {}
		/**
		 * \param jointType The type of skeleton joint
		 * \param position The joint position
		 * \param trackingState The tracking state of the joint
		 */
		Joint(JointType jointType, SkeletonPoint position, JointTrackingState trackingState) :
			_jointType(jointType),
			_position(position),
			_trackingState(trackingState)
		{}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			/*
			 *	The first byte contains :
			 *		- 2 bits for the tracking state
			 *		- 6 bits for the joint type (0x3f = 00111111(2))
			 */
			byte b = *buffer;										buffer++;
			_jointType = (JointType)(b & 0x3f);
			_trackingState = (JointTrackingState)(b >> 6);

			_position.setX((float)KPaquet::getUint32(buffer));		buffer += 4;
			_position.setY((float)KPaquet::getUint32(buffer));		buffer += 4;
			_position.setZ((float)KPaquet::getUint32(buffer));		buffer += 4;
		}

		virtual int serializedSize(void) const		{ return 1 + 3*4; }

		/* Properties */
		/** \brief Gets the type of skeleton joint.
		 *  \return The JointType of the Joint */
		JointType getJointType(void) const							{ return _jointType; }
		/** \brief Gets joint position.
		 *  \return The Position of the Joint */
		SkeletonPoint getPosition(void) const						{ return _position; }
		/** \brief Sets joint position.
		 *  \param position The Position of the Joint */
		void setPosition(SkeletonPoint position)					{ _position = position; }
		/** \brief Gets the tracking state of the joint.
		 *  \return The TrackingState of the Joint
		 *
		 * indicates the quality of the joint position that was produced by the skeleton stream.
		 */
		JointTrackingState getTrackingState(void) const				{ return _trackingState; }
		/** \brief Sets the tracking state of the joint.
		 *  \param trackingState The TrackingState of the Joint */
		void setTrackingState(JointTrackingState trackingState)		{ _trackingState = trackingState; }

	protected:
		JointType _jointType;
		SkeletonPoint _position;
		JointTrackingState _trackingState;
};

#endif
