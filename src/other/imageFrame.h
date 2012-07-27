#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H

/**
 * \file imageFrame.h
 * \brief C++ version of C# ImageFrame
 * \author Gaëtan Champarnaud
 *
 * Contains per-frame buffers for color or depth data streamed out of a Kinect.
 */

#include <string.h>
#include "../network/byte.h"

class ImageFrame
{
	public:
		/**
		 * \param bytesPerPixel The size of a pixel of data (in bytes per pixel)
		 * \param pixelDataLength The total length of the pixel data buffer
		 * \param pixelData Buffer containing the pixel data
		 * \param frameNumber The frame number
		 * \param width The data buffer width (in pixels)
		 * \param height The data buffer height (in pixels)
		 * \param timestamp The time the data was captured (in milliseconds) [always 0]
		 */
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
		/** \brief Gets the size of a pixel of data (in bytes per pixel).
		 *  \return The BytesPerPixel of the ImageFrame */
		int getBytesPerPixel(void) const	{ return _bytesPerPixel;	}
		/** \brief Gets the length of the pixel data buffer.
		 *  \return The PixelDataLength of the ImageFrame */
		int getPixelDataLength(void) const	{ return _pixelDataLength;	}
		/** \brief Gets the frame number.
		 *  \return The FrameNumber of the ImageFrame */
		int getFrameNumber(void) const		{ return _frameNumber;		}
		/** \brief Gets the data buffer height (in pixels).
		 *  \return The Height of the ImageFrame */
		int getHeight(void) const			{ return _height;			}
		/** \brief Gets the data buffer width (in pixels).
		 *  \return The Width of the ImageFrame */
		int getWidth(void) const			{ return _width;			}
		/** \brief Gets the time the data was captured (in milliseconds).
		 *  \return The Timestamp of the ImageFrame */
		int getTimestamp(void) const		{ return _timestamp;		}

		/* Methods */
		/**
		 * \brief Copies the per-pixel color data to a pre-allocated array of bytes.
		 * \param pixelData An array of bytes to receive the pixel data
		 *
		 * When creating the array, the array size must be equal to the PixelDataLength property.
		 */
		void CopyPixelDataTo(byte* pixelData) const
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
