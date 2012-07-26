#ifndef DEPTHIMAGESTREAM_H
#define DEPTHIMAGESTREAM_H

/**
 * \file depthImageStream.h
 * \brief C++ version of C# DepthImageStream
 * \author Gaëtan Champarnaud
 *
 * Represents a stream of DepthImageFrame objects.
 */

#include "kObject.h"
#include "../enums/depthImageFormat.h"
#include "../enums/depthRange.h"

class DepthImageStream : public KObject
{
	public:
		/** \param id The sensor id (index in the sensors collection) */
		DepthImageStream(int id = -1) : KObject("DepthImageStream", id)
		{}

		/* Properties */
		/** \brief Gets the format of the depth data, which includes the type, resolution and frame rate.
		 *  \return The format of the DepthImageStream */
		DepthImageFormat getFormat(void) const					{ return (DepthImageFormat)getQuery<int>(__func__); }
		/** \brief Gets the maximum depth value (in millimeters) for the depth sensor range.
		 *  \return The maxDepth of the DepthImageStream */
		int getMaxDepth(void) const								{ return getQuery<int>(__func__); }
		/** \brief Gets the minimum depth value (in millimeters) for the depth sensor range.
		 *  \return The minDepth of the DepthImageStream */
		int getMinDepth(void) const								{ return getQuery<int>(__func__); }
		/** \brief Gets the nominal diagonal field-of-view (in degrees) of the depth image.
		 *  \return The nominalDiagonalFieldOfView of the DepthImageStream */
		float getNominalDiagonalFieldOfView(void) const			{ return getQuery<float>(__func__); }
		/** \brief Gets the nominal focal length (in pixels) of the depth image.
		 *  \return The nominalFocalLengthInPixels of the DepthImageStream */
		float getNominalFocalLengthInPixels(void) const			{ return getQuery<float>(__func__); }
		/** \brief Gets the nominal horizontal field-of-view (in degrees) of the depth image.
		 *  \return The nominalHorizontalFieldOfView of the DepthImageStream */
		float getNominalHorizontalFieldOfView(void) const		{ return getQuery<float>(__func__); }
		/** \brief Gets the nominal inverse focal length (in pixels) of the depth image, adjusted for resolution.
		 *  \return The nominalInverseFocalLengthInPixels of the DepthImageStream */
		float getNominalInverseFocalLengthInPixels(void) const	{ return getQuery<float>(__func__); }
		/** \brief Gets the nominal vertical field-of-view (in degrees) of the depth image.
		 *  \return The nominalVerticalFieldOfView of the DepthImageStream */
		float getNominalVerticalFieldOfView(void) const			{ return getQuery<float>(__func__); }
		/** \brief Gets the depth data range, which determines how close or far away from the Kinect you can be and still be tracked.
		 *  \return The range of the DepthImageStream */
		DepthRange getRange(void) const							{ return (DepthRange)getQuery<int>(__func__); }
		/** \brief Ssets the depth data range, which determines how close or far away from the Kinect you can be and still be tracked.
		 *  \param range The range of the DepthImageStream */
		void setRange(DepthRange range)							
		{ 
			int intValue = (int)range;
			setQuery<int>(__func__, intValue); 
		}
		/** \brief Gets the depth value (in millimeters) that indictates a person is too for from the Kinect to track.
		 *  \return The tooFarDepth of the DepthImageStream */
		int getTooFarDepth(void) const							{ return getQuery<int>(__func__); }
		/** \brief Gets the depth value (in millimeters) that indictates a person is too close to the Kinect to track.
		 *  \return The tooNearDepth of the DepthImageStream */
		int getTooNearDepth(void) const							{ return getQuery<int>(__func__); }
		/** \brief Gets the depth value (in millimeters) for depth data that is unknown because a person is outside of a depth sensor range that can be tracked.
		 *  \return The unknownDepth of the DepthImageStream */
		int getUnknownDepth(void) const							{ return getQuery<int>(__func__); }

		/* Methods */
		/** \brief Method for enabling the Kinect to stream out depth data.
		 *  \param format The specified format */
		void enable(DepthImageFormat format = Resolution640x480Fps30)	{ processQuery(buildQuery(__func__, toString<int>((int)format))); }
//		DepthImageFrame* openNextFrame(int milliSecondsWait)			{}
};

#endif
