#ifndef DEPTHIMAGEFRAME_H
#define DEPTHIMAGEFRAME_H

/**
 * \file depthImageFrame.h
 * \brief C++ version of C# DepthImageFrame
 * \author Gaëtan Champarnaud
 *
 * Contains a per-frame buffer for depth data streamed out of a Kinect.
 */

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
		/**
		 * \brief Constructor
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
		 */
		DepthImageFrame(int bytesPerPixel, int pixelDataLength, byte* pixelData, int frameNumber, int width, int height, int timestamp,
						DepthImageFormat format, int playerIndexBitmask, int playerIndexBitmaskWidth, int id = -1) :
			ImageFrame(bytesPerPixel, pixelDataLength, pixelData, frameNumber, width, height, timestamp),
			KObject("DepthImageFrame", id),
			_format(format),
			_playerIndexBitmask(playerIndexBitmask),
			_playerIndexBitmaskWidth(playerIndexBitmaskWidth)
		{}

		/* Fields */
		/** \brief Getter for the 'PlayerIndexBitmask' field
		 *  \return The playerIndexBitmask of the DepthImageFrame */
		int getPlayerIndexBitmask(void) const		{ return _playerIndexBitmask; }
		/** \brief Getter for the 'PlayerIndexBitmaskWidth' field
		 *  \return The playerIndexBitmaskWidth of the DepthImageFrame */
		int getPlayerIndexBitmaskWidth(void) const	{ return _playerIndexBitmaskWidth; }

		/* Properties */
		/** \brief Getter for the 'Format' property
		 *  \return The format of the DepthImageFrame */
		DepthImageFormat getFormat(void) const		{ return _format; }

		/* Methods */
		/**
		 * \brief Looks up the depth point from skeleton point
		 * \param skeletonPoint The skeleton point
		 * \return The depth point
		 */
		DepthImagePoint MapFromSkeletonPoint(SkeletonPoint skeletonPoint);
		/**
		 * \brief Maps a depth point to a color point
		 * \param depthX The depth point X coordinate
		 * \param depthY The depth point Y coordinate
		 * \param colorImageFormat The color format
		 * \return The color point
		 */
		ColorImagePoint MapToColorImagePoint(int depthX, int depthY, ColorImageFormat colorImageFormat);
		/**
		 * \brief Looks up the skeleton point from a depth point
		 * \param depthX The depth point X coordinate
		 * \param depthY The depth point Y coordinate
		 * \return A skeleton point
		 */
		SkeletonPoint MapToSkeletonPoint(int depthX, int depthY);

	protected:
		DepthImageFormat _format;
		const int _playerIndexBitmask;
		const int _playerIndexBitmaskWidth;

};

#endif
