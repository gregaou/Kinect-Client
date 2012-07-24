#ifndef SKELETONFRAMEREADYEVENTARGS_H
#define SKELETONFRAMEREADYEVENTARGS_H

#include "unserializable.h"
#include "../network/kPaquet.h"
#include "skeletonFrame.h"

class SkeletonFrameReadyEventArgs : public Unserializable
{
	public:
		SkeletonFrameReadyEventArgs() : _frame(0)	{}
		SkeletonFrameReadyEventArgs(float floorClipPlane[4], int frameNumber, int skeletonArrayLength, int timestamp, SkeletonTrackingMode trackingMode, Skeleton* skeletonData);
		~SkeletonFrameReadyEventArgs(void);

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			if (_frame)
				delete _frame;
			_frame = new SkeletonFrame();
			_frame->unserialize(buffer);
		}

		virtual int serializedSize(void) const { return _frame->serializedSize(); }

		SkeletonFrame& openSkeletonFrame(void) const;

	protected:
		SkeletonFrame* _frame;
};

#endif
