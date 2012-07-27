#include "colorImageFrameReadyEventArgs.h"

ColorImageFrameReadyEventArgs::ColorImageFrameReadyEventArgs(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp, ColorImageFormat format) :
	_frame(bytesPerPixel, pixelDataLength, pixelData, frameNumber, width, height, timestamp, format)
{}

const ColorImageFrame& ColorImageFrameReadyEventArgs::openColorImageFrame() const
{
	return _frame;
}
