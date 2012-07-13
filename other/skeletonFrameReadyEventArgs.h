#ifndef SKELETONFRAMEREADYEVENTARGS_H
#define SKELETONFRAMEREADYEVENTARGS_H

#include "skeletonFrame.h"

class SkeletonFrameReadyEventArgs
{
	public:
		SkeletonFrameReadyEventArgs(float floorClipPlane[4], int frameNumber, int skeletonArrayLength, int timestamp, SkeletonTrackingMode trackingMode, Skeleton* skeletonData);
		~SkeletonFrameReadyEventArgs(void);

		SkeletonFrame& openSkeletonFrame(void) const;

	protected:
		SkeletonFrame* _frame;
};

#endif
