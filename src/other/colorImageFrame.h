#ifndef COLORIMAGEFRAME_H
#define COLORIMAGEFRAME_H

/**
 * \file colorImageFrame.h
 * \brief C++ version of C# ColorImageFrame
 * \author Gaëtan Champarnaud
 *
 * Contains a buffer for color data data streamed out of a Kinect.
 */

#include "../enums/colorImageFormat.h"
#include "../network/byte.h"
#include "imageFrame.h"

class ColorImageFrame : public ImageFrame
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
		 * \param format The format for the color data, which includes the data type, the resolution, and the frame rate.
		 */
		ColorImageFrame(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp, ColorImageFormat format);

		/* Properties */
		/** \brief Gets the total length of the pixel data buffer.
		 *  \return The ColorImageFormat of the ColorImageFrame */
		ColorImageFormat getFormat(void) const	{ return _format; }

	protected:
		ColorImageFormat _format;
};

#endif
