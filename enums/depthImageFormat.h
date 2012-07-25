#ifndef DEPTHIMAGEFORMAT_H
#define DEPTHIMAGEFORMAT_H

/**
 * \file depthImageFormat.h
 * \brief C++ version of C# enum DepthImageFormat
 * \author Gaëtan Champarnaud
 *
 * Image formats for a DepthImageStream.
 * Each image format contains the data type, the resolution, and the frame rate.
 */

/** \def Undefined */
#ifndef Undefined
#define Undefined	0
#endif

typedef enum
{
	Resolution640x480Fps30 = 1,
	Resolution320x240Fps30,
	Resolution80x60Fps30
} DepthImageFormat;

/**
 * \brief Returns the width corresponding to a format
 * \param format The depth image format to be analyzed
 * \return the width
 */
int getDepthImageWidth(DepthImageFormat format);

/**
 * \brief Returns the height corresponding to a format
 * \param format The depth image format to be analyzed
 * \return the height
 */
int getDepthImageHeight(DepthImageFormat format);

#endif
