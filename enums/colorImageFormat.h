#ifndef COLORIMAGEFORMAT_H
#define COLORIMAGEFORMAT_H

/**
 * \file colorImageFormat.h
 * \brief C++ version of C# enum ColorImageFormat
 * \author Gaëtan Champarnaud
 *
 * Image formats for a ColorImageStream.
 * Each image format contains the data type, the resolution, and the frame rate.
 */

/** \def Undefined */
#ifndef Undefined
#define Undefined	0
#endif

typedef enum
{
	RgbResolution640x480Fps30 = 1,
	RgbResolution1280x960Fps12,
	YuvResolution640x480Fps15,
	RawYuvResolution640x480Fps15
} ColorImageFormat;

/**
 * \brief Returns the width corresponding to a format
 * \param format The color image format to be analyzed
 * \return the width
 */
int getColorImageWidth(ColorImageFormat format);

/**
 * \brief Returns the height corresponding to a format
 * \param format The color image format to be analyzed
 * \return the height
 */
int getColorImageHeight(ColorImageFormat format);

/**
 * \brief Returns the FPS corresponding to a format
 * \param format The color image format to be analyzed
 * \return the FPS
 */
int getColorImageFPS(ColorImageFormat format);

#endif
