#include "colorImageFrameReadyEventArgs.h"

ColorImageFrameReadyEventArgs::ColorImageFrameReadyEventArgs(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp, ColorImageFormat format) :
	_frame(0)
{
	_frame = new ColorImageFrame(bytesPerPixel, pixelDataLength, pixelData, frameNumber, width, height, timestamp, format);
}

ColorImageFrameReadyEventArgs::~ColorImageFrameReadyEventArgs()
{
	if (_frame)
		delete _frame;
}

ColorImageFrame& ColorImageFrameReadyEventArgs::openColorImageFrame() const
{
	return *_frame;
}
