#ifndef SKELETON_H
#define SKELETON_H

#include <vector>
#include "../enums/skeletonTrackingState.h"
#include "../enums/frameEdges.h"
#include "joint.h"
#include "skeletonPoint.h"

class Skeleton
{
	public:
		Skeleton() {}
		Skeleton(FrameEdges clippedEdges, const std::vector<Joint> joints, SkeletonPoint position, int trackingId, SkeletonTrackingState trackingState) :
			_clippedEdges(clippedEdges),
			_joints(joints),
			_position(position),
			_trackingId(trackingId),
			_trackingState(trackingState)
		{}

		/* Properties */
		FrameEdges getClippedEdges(void) const						{ return _clippedEdges; }
		void setClippedEdges(FrameEdges clippedEdges)				{ _clippedEdges = clippedEdges; }
		const std::vector<Joint>& getJoints(void) const				{ return _joints; }
		void setJoints(const std::vector<Joint>& joints)			{ _joints = joints; }
		SkeletonPoint getPosition(void) const						{ return _position; }
		void setPosition(SkeletonPoint position)					{ _position = position; }
		int getTrackingId(void) const 								{ return _trackingId; }
		void setTrackingId(int trackingId)							{ _trackingId = trackingId; }
		SkeletonTrackingState getTrackingState(void) const			{ return _trackingState; }
		void setTrackingState(SkeletonTrackingState trackingState)	{ _trackingState = trackingState; }

	protected:
//		TO DO : std::vector<BoneOrientation> _boneOrientations;			get
		FrameEdges _clippedEdges;
		std::vector<Joint> _joints;
		SkeletonPoint _position;
		int _trackingId;
		SkeletonTrackingState _trackingState;
};

#endif
