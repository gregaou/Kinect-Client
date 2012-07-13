#ifndef SKELETONFRAME_H
#define SKELETONFRAME_H

#include "../enums/skeletonTrackingMode.h"
#include "skeleton.h"

class SkeletonFrame
{
	public:
		SkeletonFrame(float floorClipPlane[4], int frameNumber, int skeletonArrayLength, int timestamp, SkeletonTrackingMode trackingMode, Skeleton* skeletonData) :
			_frameNumber(frameNumber),
			_skeletonArrayLength(skeletonArrayLength),
			_timestamp(timestamp),
			_trackingMode(trackingMode),
			_skeletonData(skeletonData)
		{
			setFloorClipPlane(floorClipPlane);
		}

		/* Properties */
		const float* getFloorClipPlane(void) const			{ return _floorClipPlane; }
		void setFloorClipPlane(float* floorClipPlane)
		{
			for (int i=0; i<4; i++)
				_floorClipPlane[i] = floorClipPlane[i];
		}
		int getFrameNumber(void) const						{ return _frameNumber; }
		void setFrameNumber(int frameNumber)				{ _frameNumber = frameNumber; }
		int getSkeletonArrayLength(void) const				{ return _skeletonArrayLength; }
		int getTimestamp(void) const						{ return _timestamp; }
		void setTimestamp(int timestamp)					{ _timestamp = timestamp; }
		SkeletonTrackingMode getTrackingMode(void) const	{ return _trackingMode; }

		/* Methods */
		void CopySkeletonDataTo(Skeleton* skeletonData)
		{
			for (int i=0; i<_skeletonArrayLength; i++)
				skeletonData[i] = _skeletonData[i];
		}

	protected:
		float _floorClipPlane[4];
		int _frameNumber;
		int _skeletonArrayLength;
		int _timestamp;
		SkeletonTrackingMode _trackingMode;
		Skeleton* _skeletonData;
};

#endif
