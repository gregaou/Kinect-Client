#include <string.h>
#include "colorImageframe.h"

ColorImageFrame::ColorImageFrame(int bytesPerPixel, int pixelDataLength, int frameNumber, int height, int width, int timestamp,
								 ColorImageFormat format, byte* pixelData) :
	ImageFrame(bytesPerPixel, pixelDataLength, frameNumber, height, width, timestamp, "ColorImageFrame"),
	_format(format),
	_pixelData(pixelData)
{
}

void ColorImageFrame::CopyPixelDataTo(byte* pixelData)
{
	memcpy(pixelData, _pixelData, _pixelDataLength);
}
