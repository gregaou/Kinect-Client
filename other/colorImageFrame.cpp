#include "colorImageframe.h"

ColorImageFrame::ColorImageFrame(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int height, int width, int timestamp, ColorImageFormat format) :
	ImageFrame(bytesPerPixel, pixelDataLength, pixelData, frameNumber, height, width, timestamp),
	_format(format)
{
}
