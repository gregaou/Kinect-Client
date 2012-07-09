#ifndef COLORIMAGEFRAMEREADYEVENTARGS_H
#define COLORIMAGEFRAMEREADYEVENTARGS_H

#include "colorImageframe.h"

class ColorImageFrameReadyEventArgs
{
	public:
		ColorImageFrameReadyEventArgs(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int height, int width, int timestamp, ColorImageFormat format);
		~ColorImageFrameReadyEventArgs(void);

		/* Methods */
		ColorImageFrame& openColorImageFrame(void) const;

	protected:
		ColorImageFrame* _frame;
};

#endif
