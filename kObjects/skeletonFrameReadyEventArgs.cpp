#include "skeletonFrameReadyEventArgs.h"

SkeletonFrameReadyEventArgs::SkeletonFrameReadyEventArgs(float floorClipPlane[4], int frameNumber, int skeletonArrayLength, int timestamp, SkeletonTrackingMode trackingMode, Skeleton* skeletonData) :
	_frame(0)
{
	_frame = new SkeletonFrame(floorClipPlane, frameNumber, skeletonArrayLength, timestamp, trackingMode, skeletonData);
}

SkeletonFrameReadyEventArgs::~SkeletonFrameReadyEventArgs()
{
	if (_frame)
		delete _frame;
}

SkeletonFrame& SkeletonFrameReadyEventArgs::openSkeletonFrame(void) const
{
	return *_frame;
}
