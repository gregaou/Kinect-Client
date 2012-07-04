#ifndef COLORIMAGEFRAME_H
#define COLORIMAGEFRAME_H

#include "../enums/colorImageFormat.h"
#include "../network/byte.h"

class ColorImageFrame
{
	public:
		ColorImageFrame(ColorImageFormat format, byte* pixelData, int pixelDataLength);
		~ColorImageFrame(void);

		/* Members */
		ColorImageFormat getFormat(void) const	{ return _format; }
		int getPixelDataLength(void) const		{ return _pixelDataLength; }

		/* Methods */
		void CopyPixelDataTo(byte* pixelData);

	protected:
		ColorImageFormat _format;
		byte* _pixelData;
		int _pixelDataLength;
};

#endif
