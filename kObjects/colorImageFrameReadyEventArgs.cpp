#include "colorImageFrameReadyEventArgs.h"

ColorImageFrameReadyEventArgs::ColorImageFrameReadyEventArgs(ColorImageFormat format, byte* pixelData, int pixelDataLength) :
	_frame(0)
{
	_frame = new ColorImageFrame(format, pixelData, pixelDataLength);
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
