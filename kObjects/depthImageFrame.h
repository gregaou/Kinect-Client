#ifndef DEPTHIMAGEFRAME_H
#define DEPTHIMAGEFRAME_H

#include <vector>
#include <string>
#include "../enums/depthImageFormat.h"
#include "../enums/colorImageFormat.h"
#include "kObject.h"
#include "../other/imageFrame.h"
#include "../other/depthImagePoint.h"
#include "../other/skeletonPoint.h"
#include "../other/colorImagePoint.h"

class DepthImageFrame : public ImageFrame, public KObject
{
	public:
		DepthImageFrame(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp,
						DepthImageFormat format, int playerIndexBitmask, int playerIndexBitmaskWidth, int id = -1) :
			ImageFrame(bytesPerPixel, pixelDataLength, pixelData, frameNumber, width, height, timestamp),
			KObject("DepthImageFrame", id),
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
