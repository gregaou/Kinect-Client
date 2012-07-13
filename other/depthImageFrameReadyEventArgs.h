#ifndef DEPTHIMAGEFRAMEREADYEVENTARGS_H
#define DEPTHIMAGEFRAMEREADYEVENTARGS_H

#include "../kObjects/depthImageFrame.h"

class DepthImageFrameReadyEventArgs
{
	public:
		DepthImageFrameReadyEventArgs(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp,
									  DepthImageFormat format, int playerIndexBitmask, int playerIndexBitmaskWidth, int id = -1);
		~DepthImageFrameReadyEventArgs(void);

		/* Methods */
		DepthImageFrame& openDepthImageFrame(void) const;

	protected:
		DepthImageFrame* _frame;
};

#endif
