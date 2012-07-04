#ifndef COLORIMAGEFRAME_H
#define COLORIMAGEFRAME_H

#include "../enums/colorImageFormat.h"
#include "../network/byte.h"
#include "imageFrame.h"

class ColorImageFrame : public ImageFrame
{
	public:
		ColorImageFrame(int bytesPerPixel, int pixelDataLength, int frameNumber, int height, int width, int timestamp,
						ColorImageFormat format, byte* pixelData);

		/* Properties */
		ColorImageFormat getFormat(void) const	{ return _format; }

		/* Methods */
		void CopyPixelDataTo(byte* pixelData);

	protected:
		ColorImageFormat _format;
		byte* _pixelData;
};

#endif
