#include <string.h>
#include "colorImageframe.h"

ColorImageFrame::ColorImageFrame(ColorImageFormat format, byte* pixelData, int pixelDataLength) :
	_format(format),
	_pixelData(pixelData),
	_pixelDataLength(pixelDataLength)
{
}

ColorImageFrame::~ColorImageFrame()
{
//	if (_pixelData)
//		delete _pixelData;
}

void ColorImageFrame::CopyPixelDataTo(byte* pixelData)
{
	memcpy(pixelData, _pixelData, _pixelDataLength);
}
