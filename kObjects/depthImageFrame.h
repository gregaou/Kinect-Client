#ifndef DEPTHIMAGEFRAME_H
#define DEPTHIMAGEFRAME_H

#include "../enums/depthImageFormat.h"
#include "../enums/colorImageFormat.h"
#include "imageFrame.h"
#include "depthImagePoint.h"
#include "skeletonPoint.h"
#include "colorImagePoint.h"

class DepthImageFrame : public ImageFrame
{
	public:
		DepthImageFrame(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int height, int width, int timestamp,
						DepthImageFormat format, int playerIndexBitmask, int playerIndexBitmaskWidth) :
			ImageFrame(bytesPerPixel, pixelDataLength, pixelData, frameNumber, height, width, timestamp, "DepthImageFrame"),
			_format(format),
			_playerIndexBitmask(playerIndexBitmask),
			_playerIndexBitmaskWidth(playerIndexBitmaskWidth)
		{}

		/* Fields */
		int getPlayerIndexBitmask(void) const		{ return _playerIndexBitmask; }
		int getPlayerIndexBitmaskWidth(void) const	{ return _playerIndexBitmaskWidth; }

		/* Properties */
		DepthImageFormat getFormat(void) const		{ return _format; }

		/* Methods */
		DepthImagePoint MapFromSkeletonPoint(SkeletonPoint skeletonPoint);
		ColorImagePoint MapToColorImagePoint(int depthX, int depthY, ColorImageFormat colorImageFormat);
		SkeletonPoint MapToSkeletonPoint(int depthX, int depthY);

	protected:
		DepthImageFormat _format;
		const int _playerIndexBitmask;
		const int _playerIndexBitmaskWidth;

};

#endif
