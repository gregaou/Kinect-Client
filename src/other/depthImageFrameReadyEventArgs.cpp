#include "depthImageFrameReadyEventArgs.h"

DepthImageFrameReadyEventArgs::DepthImageFrameReadyEventArgs(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp,
									  DepthImageFormat format, int playerIndexBitmask, int playerIndexBitmaskWidth, int id) :
	_frame(bytesPerPixel, pixelDataLength, pixelData, frameNumber, width, height, timestamp, format, playerIndexBitmask, playerIndexBitmaskWidth, id)
{
}

const DepthImageFrame& DepthImageFrameReadyEventArgs::openDepthImageFrame() const
{
	return _frame;
}

