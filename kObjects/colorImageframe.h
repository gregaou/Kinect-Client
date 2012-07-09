#ifndef COLORIMAGEFRAME_H
#define COLORIMAGEFRAME_H

#include "../enums/colorImageFormat.h"
#include "../network/byte.h"
#include "imageFrame.h"

class ColorImageFrame : public ImageFrame
{
	public:
		ColorImageFrame(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int height, int width, int timestamp, ColorImageFormat format);

		/* Properties */
		ColorImageFormat getFormat(void) const	{ return _format; }

	protected:
		ColorImageFormat _format;
};

#endif
