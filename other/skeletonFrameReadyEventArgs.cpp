#include "skeletonFrameReadyEventArgs.h"

SkeletonFrameReadyEventArgs::SkeletonFrameReadyEventArgs(float floorClipPlane[4], int frameNumber, int skeletonArrayLength, int timestamp, SkeletonTrackingMode trackingMode, Skeleton* skeletonData) :
	_frame(floorClipPlane, frameNumber, skeletonArrayLength, timestamp, trackingMode, skeletonData)
{
}

const SkeletonFrame& SkeletonFrameReadyEventArgs::openSkeletonFrame(void) const
{
	return _frame;
}
