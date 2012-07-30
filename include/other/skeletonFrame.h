#ifndef SKELETONFRAME_H
#define SKELETONFRAME_H

/**
 * \file skeletonFrame.h
 * \brief C++ version of C# SkeletonFrame
 * \author Gaëtan Champarnaud
 *
 * Contains a single frame of skeleton data for all of the tracked skeletons.
 */

#include "unserializable.h"
#include "../network/kPaquet.h"
#include "../enums/skeletonTrackingMode.h"
#include "skeleton.h"

class SkeletonFrame : public Unserializable
{
	public:
		SkeletonFrame() : _skeletonData(0)  {}
		/**
		 * \param floorClipPlane The clip plane of the floor in the form of a four component tuple (x, y, z, w)
		 * \param frameNumber The frame number
		 * \param skeletonArrayLength The maximum number of skeletons that can be tracked
		 * \param timestamp The time that the frame was created [always 0]
		 * \param trackingMode The skeleton tracking mode
		 * \param skeletonData An array of skeletons
		 */
		SkeletonFrame(float floorClipPlane[4], int frameNumber, int skeletonArrayLength, int timestamp, SkeletonTrackingMode trackingMode, Skeleton* skeletonData) :
			_frameNumber(frameNumber),
			_skeletonArrayLength(skeletonArrayLength),
			_timestamp(timestamp),
			_trackingMode(trackingMode),
			_skeletonData(skeletonData)
		{
			setFloorClipPlane(floorClipPlane);
		}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			/*
			 *	The first byte contains :
			 *		- 1 bit for the tracking mode
			 *		- 3 bits for the sensor id
			 *		- 4 bits for the length of the skeleton array
			 */
			byte firstByte = *buffer;								buffer++;
			_trackingMode = (SkeletonTrackingMode)(firstByte >> 7);
			_skeletonArrayLength = firstByte & 0xf;

			_frameNumber = KPaquet::getUint32(buffer);				buffer += 4;
			_timestamp = KPaquet::getUint32(buffer);				buffer += 4;

			for (int i=0; i<4; i++)
			{
				_floorClipPlane[i] = (float)KPaquet::getUint32(buffer);
				buffer += 4;
			}

			/* Building the skeletons (26 + <boneOrientationsSize> + <jointsSize> bytes/skeleton) */
			_skeletonData = new Skeleton[_skeletonArrayLength];
			for (int i=0; i<_skeletonArrayLength; i++)
			{
				_skeletonData[i].unserialize(buffer);
				buffer += _skeletonData[i].serializedSize();
			}
		}

		virtual int serializedSize(void) const
		{
			return 1 + 2*4 + 4*4 + _skeletonArrayLength * _skeletonData[0].serializedSize();
		}

		/* Properties */
		/** \brief Gets the clip plane of the floor in the form of a four component tuple (x, y, z, w).
		 *  \return The FloorClipPlane of the SkeletonFrame */
		const float* getFloorClipPlane(void) const			{ return _floorClipPlane; }
		/** \brief Sets the clip plane of the floor in the form of a four component tuple (x, y, z, w).
		 *  \param floorClipPlane The FloorClipPlane of the SkeletonFrame */
		void setFloorClipPlane(float* floorClipPlane)
		{
			for (int i=0; i<4; i++)
				_floorClipPlane[i] = floorClipPlane[i];
		}
		/** \brief Gets the frame number.
		 *  \return The FrameNumber of the SkeletonFrame */
		int getFrameNumber(void) const						{ return _frameNumber; }
		/** \brief Sets the frame number.
		 *  \param frameNumber The FrameNumber of the SkeletonFrame */
		void setFrameNumber(int frameNumber)				{ _frameNumber = frameNumber; }
		/** \brief Gets the maximum number of skeletons that can be tracked.
		 *  \return The SkeletonArrayLength of the SkeletonFrame */
		int getSkeletonArrayLength(void) const				{ return _skeletonArrayLength; }
		/** \brief Gets the time that the frame was created.
		 *  \return The Timestamp of the SkeletonFrame */
		int getTimestamp(void) const						{ return _timestamp; }
		/** \brief Sets the time that the frame was created.
		 *  \param timestamp The Timestamp of the SkeletonFrame */
		void setTimestamp(int timestamp)					{ _timestamp = timestamp; }
		/**
		 * \brief Gets the tracking mode
		 * \return The TrackingMode of the SkeletonFrame
		 *
		 * Do not use this property; this value may change in a future release.
		 */
		SkeletonTrackingMode getTrackingMode(void) const	{ return _trackingMode; }

		/* Methods */
		/** \brief Copies skeleton data to an array of Skeletons, where each Skeleton contains a collection of the joints in that skeleton.
		 *  \param skeletonData An array of Skeleton to receive the skeleton data. */
		void CopySkeletonDataTo(Skeleton* skeletonData)
		{
			for (int i=0; i<_skeletonArrayLength; i++)
				skeletonData[i] = _skeletonData[i];
		}

	protected:
		float _floorClipPlane[4];
		int _frameNumber;
		int _skeletonArrayLength;
		int _timestamp;
		SkeletonTrackingMode _trackingMode;
		Skeleton* _skeletonData;
};

#endif
