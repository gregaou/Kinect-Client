#ifndef SKELETONFRAME_H
#define SKELETONFRAME_H

#include "unserializable.h"
#include "../network/kPaquet.h"
#include "../enums/skeletonTrackingMode.h"
#include "skeleton.h"

class SkeletonFrame : public Unserializable
{
	public:
		SkeletonFrame() : _skeletonData(0)  {}
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
			int pos = 0;

			/*
			 *	The first byte contains :
			 *		- 1 bit for the tracking mode
			 *		- 3 bits for the sensor id
			 *		- 4 bits for the length of the skeleton array
			 */
			byte firstByte = buffer[pos++];
			_trackingMode = (SkeletonTrackingMode)(firstByte >> 7);
			_skeletonArrayLength = firstByte & 0xf;

			_frameNumber = KPaquet::getUint32(buffer, pos);				pos += 4;
			_timestamp = KPaquet::getUint32(buffer, pos);				pos += 4;

			for (int i=0; i<4; i++)
			{
				_floorClipPlane[i] = (float)KPaquet::getUint32(buffer, pos);
				pos += 4;
			}

			/* Building the skeletons (26 + <boneOrientationsSize> + <jointsSize> bytes/skeleton) */
			_skeletonData = new Skeleton[_skeletonArrayLength];
			for (int i=0; i<_skeletonArrayLength; i++)
			{
				_skeletonData[i].unserialize(buffer + pos);
				pos += _skeletonData[i].serializedSize();
			}
		}

		virtual int serializedSize(void) const
		{
			return 1 + 2*4 + 4*4 + _skeletonArrayLength * _skeletonData[0].serializedSize();
		}

		/* Properties */
		const float* getFloorClipPlane(void) const			{ return _floorClipPlane; }
		void setFloorClipPlane(float* floorClipPlane)
		{
			for (int i=0; i<4; i++)
				_floorClipPlane[i] = floorClipPlane[i];
		}
		int getFrameNumber(void) const						{ return _frameNumber; }
		void setFrameNumber(int frameNumber)				{ _frameNumber = frameNumber; }
		int getSkeletonArrayLength(void) const				{ return _skeletonArrayLength; }
		int getTimestamp(void) const						{ return _timestamp; }
		void setTimestamp(int timestamp)					{ _timestamp = timestamp; }
		SkeletonTrackingMode getTrackingMode(void) const	{ return _trackingMode; }

		/* Methods */
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
