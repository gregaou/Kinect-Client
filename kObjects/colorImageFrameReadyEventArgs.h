#ifndef COLORIMAGEFRAMEREADYEVENTARGS_H
#define COLORIMAGEFRAMEREADYEVENTARGS_H

#include "colorImageframe.h"

class ColorImageFrameReadyEventArgs
{
	public:
		ColorImageFrameReadyEventArgs(ColorImageFormat format, byte* pixelData, int pixelDataLength);
		~ColorImageFrameReadyEventArgs(void);
		ColorImageFrame* openColorImageFrame(void) const;

	protected:
		ColorImageFrame* _frame;
};

#endif
