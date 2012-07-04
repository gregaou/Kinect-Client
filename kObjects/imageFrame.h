#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H

#include "kObject.h"

class ImageFrame : public KObject
{
	public:
		ImageFrame(int bytesPerPixel, int pixelDataLength, int frameNumber, int height, int width, int timestamp, const char* classname = "ImageFrame", int id = -1) :
			KObject(classname, id),
			_bytesPerPixel(bytesPerPixel),
			_pixelDataLength(pixelDataLength),
			_frameNumber(frameNumber),
			_height(height),
			_width(width),
			_timestamp(timestamp)
		{}

		/* Properties */
		int getBytesPerPixel(void) const	{ return _bytesPerPixel;	}
		int getPixelDataLength(void) const	{ return _pixelDataLength;	}
		int getFrameNumber(void) const		{ return _frameNumber;		}
		int getHeight(void) const			{ return _height;			}
		int getWidth(void) const			{ return _width;			}
		int getTimestamp (void) const		{ return _timestamp;		}

	protected:
		int _bytesPerPixel;
		int _pixelDataLength;
		int _frameNumber;
		int _height;
		int _width;
		int _timestamp;
};

#endif
