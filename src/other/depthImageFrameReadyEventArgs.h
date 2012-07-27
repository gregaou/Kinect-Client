#ifndef DEPTHIMAGEFRAMEREADYEVENTARGS_H
#define DEPTHIMAGEFRAMEREADYEVENTARGS_H

/**
 * \file depthImageFrameReadyEventArgs.h
 * \brief C++ version of C# DepthImageFrameReadyEventArgs
 * \author Gaëtan Champarnaud
 *
 * These event arguments provide information about an DepthFrameReady Event.
 */

#include "../kObjects/depthImageFrame.h"

class DepthImageFrameReadyEventArgs
{
	public:
		/**
		 * \param bytesPerPixel The size of a pixel of data (in bytes per pixel)
		 * \param pixelDataLength The length of the pixel data buffer
		 * \param pixelData Buffer containing the pixel data
		 * \param frameNumber The frame number
		 * \param width	The data buffer width (in pixels)
		 * \param height The data buffer height (in pixels
		 * \param timestamp The time the data was captured (in milliseconds) [always 0]
		 * \param format The format for the depth data, which includes the data type, the resolution, and the frame rate
		 * \param playerIndexBitmask A bitmask for extracting the player index from the depth data; the player index is stored in the lowest order bits
		 * \param playerIndexBitmaskWidth The width, or number of bits, in the player index bitmask. This is the number of low order bits in the depth data that stores the player index
		 * \param id The sensor id (index in the sensors collection)
		 *
		 * For internal use \e only
		 */
		DepthImageFrameReadyEventArgs(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp,
									  DepthImageFormat format, int playerIndexBitmask, int playerIndexBitmaskWidth, int id = -1);

		/* Methods */
		/** \brief Gets the most recent frame of depth data.
		 *  \return A frame of depth data */
		const DepthImageFrame& openDepthImageFrame(void) const;

	protected:
		DepthImageFrame _frame;
};

#endif
