#ifndef COLORIMAGEFRAMEREADYEVENTARGS_H
#define COLORIMAGEFRAMEREADYEVENTARGS_H

/**
 * \file colorImageFrameReadyEventArgs.h
 * \brief C++ version of C# ColorImageFrameReadyEventArgs
 * \author Gaëtan Champarnaud
 *
 * These event arguments provide information about a ColorFrameReady Event.
 */

#include "colorImageFrame.h"

class ColorImageFrameReadyEventArgs
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
		 *
		 * For internal use \e only
		 */
		ColorImageFrameReadyEventArgs(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp, ColorImageFormat format);

		/* Methods */
		/** \brief Gets the most recent frame of color data.
		 *  \return A frame of color data */
		const ColorImageFrame& openColorImageFrame(void) const;

	protected:
		ColorImageFrame _frame;
};

#endif
