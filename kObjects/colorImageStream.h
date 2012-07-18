#ifndef COLORIMAGESTREAM_H
#define COLORIMAGESTREAM_H

#include "../enums/colorImageFormat.h"
#include "kObject.h"

class ColorImageStream : public KObject
{
	public:
		ColorImageStream(int id = -1) : KObject("ColorImageStream", id)
		{}

		/* Properties */
		ColorImageFormat getFormat(void) const					{ return (ColorImageFormat)getQuery<int>(__func__); }
		float getNominalDiagonalFieldOfView(void) const			{ return getQuery<float>(__func__); }
		float getNominalFocalLengthInPixels(void) const			{ return getQuery<float>(__func__); }
		float getNominalHorizontalFieldOfView(void) const		{ return getQuery<float>(__func__); }
		float getNominalInverseFocalLengthInPixels(void) const	{ return getQuery<float>(__func__); }
		float getNominalVerticalFieldOfView(void) const			{ return getQuery<float>(__func__); }

		/* Methods */
		void enable(ColorImageFormat format = RgbResolution640x480Fps30)	{ processQuery(buildQuery(__func__, toString<int>((int)format))); }
//		ColorImageFrame* openNextFrame(int milliSecondsWait) {}
};

#endif

