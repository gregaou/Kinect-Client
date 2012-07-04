#include "colorImageFrameReadyEventArgs.h"

ColorImageFrameReadyEventArgs::ColorImageFrameReadyEventArgs(int bytesPerPixel, int pixelDataLength, int frameNumber, int height, int width, int timestamp,
															 ColorImageFormat format, byte* pixelData) :
	_frame(0)
{
	_frame = new ColorImageFrame(bytesPerPixel, pixelDataLength, frameNumber, height, width, timestamp, format, pixelData);
}

ColorImageFrameReadyEventArgs::~ColorImageFrameReadyEventArgs()
{
	if (_frame)
		delete _frame;
}

ColorImageFrame* ColorImageFrameReadyEventArgs::openColorImageFrame() const
{
	return _frame;
}
