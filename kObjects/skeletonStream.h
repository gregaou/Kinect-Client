#ifndef SKELETONSTREAM_H
#define SKELETONSTREAM_H

/**
 * \file skeletonStream.h
 * \brief C++ version of C# SkeletonStream
 * \author Gaëtan Champarnaud
 *
 * Maintains the stream of skeleton data coming from the Kinect.
 */

#include "kObject.h"
#include "../enums/skeletonTrackingMode.h"
#include "../other/transformSmoothParameters.h"

class SkeletonStream : public KObject
{
	public:
		/** \brief Constructor
		 *  \param id The sensor id (index in the sensors collection) */
		SkeletonStream(int id = -1) : KObject("SkeletonStream", id)
		{}

		/* Properties */
		/** \brief Gets or sets a value indicating whether the application or the runtime chooses which skeletons to track.
		 *  \return The AppChoosesSkeletons of the SkeletonStream */
		bool getAppChoosesSkeletons(void) const								{ return (bool)getQuery<int>(__func__); }
		/** \brief Sets or sets a value indicating whether the application or the runtime chooses which skeletons to track.
		 *  \param appChoosesSkeletons The AppChoosesSkeletons of the SkeletonStream */
		void setAppChoosesSkeletons(bool appChoosesSkeletons)				{ setQuery<int>(__func__, (int)appChoosesSkeletons); }
		/** \brief Gets a value indicating whether skeleton tracking is enabled when the depth range is set to near mode.
		 *  \return The EnableTrackingInNearRange of the SkeletonStream */
		bool getEnableTrackingInNearRange(void) const						{ return (bool)getQuery<int>(__func__); }
		/** \brief Sets a value indicating whether skeleton tracking is enabled when the depth range is set to near mode.
		 *  \param enableTrackingInNearRange The EnableTrackingInNearRange of the SkeletonStream */
		void setEnableTrackingInNearRange(bool enableTrackingInNearRange)	{ setQuery<int>(__func__, (int)enableTrackingInNearRange); }
		/** \brief Gets the maximum number of skeletons that can be tracked.
		 *  \return The FrameSkeletonArrayLength of the SkeletonStream */
		int getFrameSkeletonArrayLength(void) const							{ return getQuery<int>(__func__); }
		/** \brief Gets a value indicating whether output data streaming is enabled.
		 *  \return The IsEnabled of the SkeletonStream */
		bool isEnabled(void) const											{ return (bool)getQuery<int>(__func__); }
		/** \brief Gets a value indicating whether smoothing is enabled, which reduces the amount of variation in the skeleton position data.
		 *  \return The IsSmoothingEnabled of the SkeletonStream */
		bool isSmoothingEnabled(void) const									{ return (bool)getQuery<int>(__func__); }
		/** \brief Gets custom smoothing parameters for smoothing raw skeleton data.
		 *  \return The SmoothParameters of the SkeletonStream */
		TransformSmoothParameters getSmoothParameters(void) const
		{
			/* Processign the query */
			processQuery(buildQuery(__func__));

			/* Getting the result */
			std::vector<std::string>* res = splitString(lastMessage(), SEP);

			/* Checking the result */
			checkRet(5, res->size());

			/* Building the resulting TransformSmoothParameters */
			float correction = valueOf<float>((*res)[0]);
			float jitterRadius = valueOf<float>((*res)[1]);
			float maxDeviationRadius = valueOf<float>((*res)[2]);
			float prediction = valueOf<float>((*res)[3]);
			float smoothing = valueOf<float>((*res)[4]);

			delete res;

			return TransformSmoothParameters(correction, jitterRadius, maxDeviationRadius, prediction, smoothing);
		}
		/** \brief Gets the tracking mode which detemines how many joints to track.
		 *  \return The TrackingMode of the SkeletonStream */
		SkeletonTrackingMode getTrackingMode(void) const					{ return (SkeletonTrackingMode)getQuery<int>(__func__);	}
		/** \brief Sets the tracking mode which detemines how many joints to track.
		 *  \param trackingMode The TrackingMode of the SkeletonStream */
		void setTrackingMode(SkeletonTrackingMode trackingMode)(void) const	{ setQuery<int>(__func__, (int)trackingMode); }

		/* Methods */
		/** \brief Enables the Kinect to stream out skeleton data. */
		void enable()	{ processQuery(buildQuery(__func__, toString<int>((int)format))); }
};

#endif
