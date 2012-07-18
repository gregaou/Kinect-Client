#ifndef DEPTHIMAGESTREAM_H
#define DEPTHIMAGESTREAM_H

#include "kObject.h"
#include "../enums/depthImageFormat.h"
#include "../enums/depthRange.h"

class DepthImageStream : public KObject
{
	public:
		DepthImageStream(int id = -1) : KObject("DepthImageStream", id)
		{}

		/* Properties */
		DepthImageFormat getFormat(void) const					{ return (DepthImageFormat)getQuery<int>(__func__); }
		int getMaxDepth(void) const								{ return getQuery<int>(__func__); }
		int getMinDepth(void) const								{ return getQuery<int>(__func__); }
		float getNominalDiagonalFieldOfView(void) const			{ return getQuery<float>(__func__); }
		float getNominalFocalLengthInPixels(void) const			{ return getQuery<float>(__func__); }
		float getNominalHorizontalFieldOfView(void) const		{ return getQuery<float>(__func__); }
		float getNominalInverseFocalLengthInPixels(void) const	{ return getQuery<float>(__func__); }
		float getNominalVerticalFieldOfView(void) const			{ return getQuery<float>(__func__); }
		DepthRange getRange(void) const							{ return (DepthRange)getQuery<int>(__func__); }
		int getTooFarDepth(void) const							{ return getQuery<int>(__func__); }
		int getTooNearDepth(void) const							{ return getQuery<int>(__func__); }
		int getUnknownDepth(void) const							{ return getQuery<int>(__func__); }

		/* Methods */
		void enable(DepthImageFormat format = Resolution640x480Fps30)	{ processQuery(buildQuery(__func__, toString<int>((int)format))); }
//		DepthImageFrame* openNextFrame(int milliSecondsWait)			{}
};

#endif
