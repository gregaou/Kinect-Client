#ifndef SKELETON_H
#define SKELETON_H

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
			int pos = 0;

			int boneOrientationsLength = KPaquet::getUint32(buffer, pos);		pos += 4;

			/* Building the bone orientations (42 bytes/boneOrientation) */
			for (int i=0; i<boneOrientationsLength; i++)
			{
				BoneOrientation boneOrientation;
				boneOrientation.unserialize(buffer + pos);
				pos += boneOrientation.serializedSize();

				_boneOrientations.push_back(boneOrientation);
			}

			_clippedEdges = KPaquet::getUint32(buffer, pos);					pos += 4;
			int jointsLength = KPaquet::getUint32(buffer, pos);					pos += 4;

			/* Building the joints (13 bytes/joint) */
			for (int j=0; j<jointsLength; j++)
			{
				Joint joint;
				joint.unserialize(buffer + pos);
				pos += joint.serializedSize();

				_joints.push_back(joint);
			}

			_position.unserialize(buffer + pos);
			pos += _position.serializedSize();

			_trackingId = KPaquet::getUint32(buffer, pos);							pos += 4;
			_trackingState = (SkeletonTrackingState)(buffer[pos++]);
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
		const std::vector<BoneOrientation>& getBoneOrientations(void) const		{ return _boneOrientations; }
		FrameEdges getClippedEdges(void) const									{ return _clippedEdges; }
		void setClippedEdges(FrameEdges clippedEdges)							{ _clippedEdges = clippedEdges; }
		const std::vector<Joint>& getJoints(void) const							{ return _joints; }
		void setJoints(const std::vector<Joint>& joints)						{ _joints = joints; }
		SkeletonPoint getPosition(void) const									{ return _position; }
		void setPosition(SkeletonPoint position)								{ _position = position; }
		int getTrackingId(void) const 											{ return _trackingId; }
		void setTrackingId(int trackingId)										{ _trackingId = trackingId; }
		SkeletonTrackingState getTrackingState(void) const						{ return _trackingState; }
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
