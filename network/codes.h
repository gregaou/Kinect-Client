#ifndef CODES_H
#define CODES_H

typedef enum ServerCode
{
	ColorStream = 2,
	SkeletonStream = 3,
	/* ... */
	BadArgument = 101,
	InvalidOperation = 102,
	/* ... */
	KinectSensorCollectionStatusChanged = 200,
	KinectSensorColorImageFrameReady = 201,
	KinectSensorDepthImageFrameReady = 202,
	KinectSensorSkeletonFrameReady = 203,
	/* ... */
	QueryOK = 1
} ServerCode;

#endif
