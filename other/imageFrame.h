#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H

#include <string.h>
#include "../network/byte.h"

class ImageFrame
{
	public:
		ImageFrame(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp) :
			_bytesPerPixel(bytesPerPixel),
			_pixelDataLength(pixelDataLength),
			_pixelData(pixelData),
			_frameNumber(frameNumber),
			_width(width),
			_height(height),
			_timestamp(timestamp)
		{}

		/* Properties */
		int getBytesPerPixel(void) const	{ return _bytesPerPixel;	}
		int getPixelDataLength(void) const	{ return _pixelDataLength;	}
		int getFrameNumber(void) const		{ return _frameNumber;		}
		int getHeight(void) const			{ return _height;			}
		int getWidth(void) const			{ return _width;			}
		int getTimestamp (void) const		{ return _timestamp;		}

		/* Methods */
		void CopyPixelDataTo(byte* pixelData)
		{
			memcpy(pixelData, _pixelData, _pixelDataLength);
		}

	protected:
		int _bytesPerPixel;
		int _pixelDataLength;
		byte* _pixelData;
		int _frameNumber;
		int _width;
		int _height;
		int _timestamp;
};

#endif
