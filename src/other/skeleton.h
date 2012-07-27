#ifndef SKELETON_H
#define SKELETON_H

/**
 * \file skeleton.h
 * \brief C++ version of C# Skeleton
 * \author Gaëtan Champarnaud
 *
 * Contains skeleton tracking data, which is joint data that is streamed out of a Kinect in the skeleton stream.
 */

#include <vector>
#include "unserializable.h"
#include "../network/kPaquet.h"
#include "boneOrientation.h"
#include "../enums/skeletonTrackingState.h"
#include "../enums/frameEdges.h"
#include "joint.h"
#include "skeletonPoint.h"

class Skeleton : public Unserializable
{
	public:
		Skeleton() :
			_boneOrientations(),
			_joints(),
			_position()
		{}

		/**
		 * \param boneOrientations The collection of bone orientations for a skeleton
		 * \param clippedEdges The edges (of a frame of depth data) that intersect with (and therefore clip) the skeleton data
		 * \param joints A collection of skeleton joints
		 * \param position The skeleton position
		 * \param trackingId A skeleton tracking ID
		 * \param trackingState The skeleton data tracking option
		 *
		 * For internal use \e only
		 */
		Skeleton(std::vector<BoneOrientation>& boneOrientations, FrameEdges clippedEdges, std::vector<Joint>& joints, SkeletonPoint position, int trackingId, SkeletonTrackingState trackingState) :
			_boneOrientations(boneOrientations),
			_clippedEdges(clippedEdges),
			_joints(joints),
			_position(position),
			_trackingId(trackingId),
			_trackingState(trackingState)
		{}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			int boneOrientationsLength = KPaquet::getUint32(buffer);		buffer += 4;

			/* Building the bone orientations (42 bytes/boneOrientation) */
			for (int i=0; i<boneOrientationsLength; i++)
			{
				BoneOrientation boneOrientation;
				boneOrientation.unserialize(buffer);
				buffer += boneOrientation.serializedSize();

				_boneOrientations.push_back(boneOrientation);
			}

			_clippedEdges = KPaquet::getUint32(buffer);					buffer += 4;
			int jointsLength = KPaquet::getUint32(buffer);				buffer += 4;

			/* Building the joints (13 bytes/joint) */
			for (int j=0; j<jointsLength; j++)
			{
				Joint joint;
				joint.unserialize(buffer);
				buffer += joint.serializedSize();

				_joints.push_back(joint);
			}

			_position.unserialize(buffer);
			buffer += _position.serializedSize();

			_trackingId = KPaquet::getUint32(buffer);							buffer += 4;
			_trackingState = (SkeletonTrackingState)(*buffer);
			buffer++;
		}

		virtual int serializedSize(void) const
		{
			int size = 0;

			size += _boneOrientations.size() * _boneOrientations[0].serializedSize();
			size += 4;
			size += _joints.size() * _joints[0].serializedSize();
			size += _position.serializedSize();
			size += 4;
			size += 1;

			return size;
		}

		/* Properties */
		/** \brief Gets the collection of bone orientations for a skeleton.
		 *  \return The BoneOrientations of the Skeleton */
		const std::vector<BoneOrientation>& getBoneOrientations(void) const		{ return _boneOrientations; }
		/** \brief Gets the edges (of a frame of depth data) that intersect with (and therefore clip) the skeleton data.
		 *  \return The ClippedEdges of the Skeleton */
		FrameEdges getClippedEdges(void) const									{ return _clippedEdges; }
		/** \brief Sets the edges (of a frame of depth data) that intersect with (and therefore clip) the skeleton data.
		 *  \param clippedEdges The ClippedEdges of the Skeleton */
		void setClippedEdges(FrameEdges clippedEdges)							{ _clippedEdges = clippedEdges; }
		/**
		 * \brief Gets a collection of skeleton joints.
		 * \return The BoneOrientations of the Skeleton
		 *
		 * Each joint contains data such as the joint type, position and whether or not the joint is being tracked.
		 */
		const std::vector<Joint>& getJoints(void) const							{ return _joints; }
		/**
		 * \brief Sets a collection of skeleton joints.
		 * \param joints The BoneOrientations of the Skeleton
		 *
		 * Each joint contains data such as the joint type, position and whether or not the joint is being tracked.
		 */
		void setJoints(const std::vector<Joint>& joints)						{ _joints = joints; }
		/** \brief Gets the skeleton position.
		 *  \return The Position of the Skeleton */
		SkeletonPoint getPosition(void) const									{ return _position; }
		/** \brief Sets the skeleton position.
		 *  \param position The Position of the Skeleton */
		void setPosition(SkeletonPoint position)								{ _position = position; }
		/**
		 * \brief Gets a skeleton tracking ID.
		 * \return The TrackingId of the Skeleton
		 *
		 * The id is unique for each tracked skeleton.
		 */
		int getTrackingId(void) const 											{ return _trackingId; }
		/**
		 * \brief Sets a skeleton tracking ID.
		 * \param trackingId The TrackingId of the Skeleton
		 *
		 * The id is unique for each tracked skeleton.
		 */
		void setTrackingId(int trackingId)										{ _trackingId = trackingId; }
		/** \brief Gets the skeleton data tracking option.
		 *  \return The TrackingState of the Skeleton */
		SkeletonTrackingState getTrackingState(void) const						{ return _trackingState; }
		/** \brief Sets the skeleton data tracking option.
		 *  \param trackingState The TrackingState of the Skeleton */
		void setTrackingState(SkeletonTrackingState trackingState)				{ _trackingState = trackingState; }

	protected:
		std::vector<BoneOrientation> _boneOrientations;
		FrameEdges _clippedEdges;
		std::vector<Joint> _joints;
		SkeletonPoint _position;
		int _trackingId;
		SkeletonTrackingState _trackingState;
};

#endif
