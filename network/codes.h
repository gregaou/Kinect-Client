#ifndef CODES_H
#define CODES_H

typedef enum ServerCode
{
	BadArgument = 101,
	InvalidOperation,
	/* ... */
	KinectSensorCollectionStatusChanged = 200,
	KinectSensorColorImageFrameReady,
	KinectSensorDepthImageFrameReady,
	KinectSensorSkeletonFrameReady,
	KinectSensorAudioDataReady,
	KinectAudioSourceBeamAngleChanged,
	KinectAudioSourceSoundSourceAngleChanged,
	/* ... */
	QueryOK = 1
} ServerCode;

#endif
