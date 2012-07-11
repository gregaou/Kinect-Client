#include "depthImageFrameReadyEventArgs.h"

DepthImageFrameReadyEventArgs::DepthImageFrameReadyEventArgs(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp,
									  DepthImageFormat format, int playerIndexBitmask, int playerIndexBitmaskWidth) :
	_frame(0)
{
	_frame = new DepthImageFrame(bytesPerPixel, pixelDataLength, pixelData, frameNumber, width, height, timestamp, format, playerIndexBitmask, playerIndexBitmaskWidth);
}

DepthImageFrameReadyEventArgs::~DepthImageFrameReadyEventArgs(void)
{
	if (_frame)
		delete _frame;
}

DepthImageFrame& DepthImageFrameReadyEventArgs::openDepthImageFrame() const
{
	return *_frame;
}

