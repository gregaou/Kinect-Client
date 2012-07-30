#ifndef SKELETONFRAMEREADYEVENTARGS_H
#define SKELETONFRAMEREADYEVENTARGS_H

/**
 * \file skeletonFrameReadyEventArgs.h
 * \brief C++ version of C# SkeletonFrameReadyEventArgs
 * \author Gaëtan Champarnaud
 *
 * These event arguments provide information about a Kinect for a SkeletonFrameReady event.
 */

#include "unserializable.h"
#include "../network/kPaquet.h"
#include "skeletonFrame.h"

class SkeletonFrameReadyEventArgs : public Unserializable
{
	public:
		SkeletonFrameReadyEventArgs() : _frame()	{}
		/**
		 * \param floorClipPlane The clip plane of the floor in the form of a four component tuple (x, y, z, w)
		 * \param frameNumber The frame number
		 * \param skeletonArrayLength The maximum number of skeletons that can be tracked
		 * \param timestamp The time that the frame was created [always 0]
		 * \param trackingMode The skeleton tracking mode
		 * \param skeletonData An array of skeletons
		 *
		 * For internal use \e only
		 */
		SkeletonFrameReadyEventArgs(float floorClipPlane[4], int frameNumber, int skeletonArrayLength, int timestamp, SkeletonTrackingMode trackingMode, Skeleton* skeletonData);

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			_frame.unserialize(buffer);
		}

		virtual int serializedSize(void) const { return _frame.serializedSize(); }

		/* Methods */
		/** \brief Opens a SkeletonFrame, which contains one frame of skeleton data.
		 *  \return The skeleton frame that corresponds to this event */
		const SkeletonFrame& openSkeletonFrame(void) const;

	protected:
		SkeletonFrame _frame;
};

#endif
