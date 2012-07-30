#ifndef COLORIMAGESTREAM_H
#define COLORIMAGESTREAM_H

/**
 * \file colorImageStream.h
 * \brief C++ version of C# ColorImageStream
 * \author Gaëtan Champarnaud
 *
 * Represents a stream of ColorImageFrame objects.
 */

#include "../enums/colorImageFormat.h"
#include "kObject.h"

class ColorImageStream : public KObject
{
	public:
		/** \param id The sensor id (index in the sensors collection) */
		ColorImageStream(int id = -1) : KObject("ColorImageStream", id)
		{}

		/* Properties */
		/** \brief Getter for the 'Format' property
		 *  \return The format of the ColorImageStream */
		ColorImageFormat getFormat(void) const					{ return (ColorImageFormat)getQuery<int>(__func__); }
		/** \brief Getter for the 'NominalDiagonalFieldOfView' property
		 *  \return The nominalDiagonalFieldOfView of the ColorImageStream */
		float getNominalDiagonalFieldOfView(void) const			{ return getQuery<float>(__func__); }
		/** \brief Getter for the 'NominalFocalLengthInPixels' property
		 *  \return The nominalFocalLengthInPixels of the ColorImageStream */
		float getNominalFocalLengthInPixels(void) const			{ return getQuery<float>(__func__); }
		/** \brief Getter for the 'NominalHorizontalFieldOfView' property
		 *  \return The nominalHorizontalFieldOfView of the ColorImageStream */
		float getNominalHorizontalFieldOfView(void) const		{ return getQuery<float>(__func__); }
		/** \brief Getter for the 'NominalInverseFocalLengthInPixels' property
		 *  \return The nominalInverseFocalLengthInPixels of the ColorImageStream */
		float getNominalInverseFocalLengthInPixels(void) const	{ return getQuery<float>(__func__); }
		/** \brief Getter for the 'NominalVerticalFieldOfView' property
		 *  \return The nominalVerticalFieldOfView of the ColorImageStream */
		float getNominalVerticalFieldOfView(void) const			{ return getQuery<float>(__func__); }

		/* Methods */
		/** \brief Enables the sensor to stream out color data */
		void enable(ColorImageFormat format = RgbResolution640x480Fps30)	{ processQuery(buildQuery(__func__, toString<int>((int)format))); }
//		ColorImageFrame* openNextFrame(int milliSecondsWait) {}
};

#endif

