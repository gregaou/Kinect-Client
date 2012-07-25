#ifndef KINECTSTATUS_H
#define KINECTSTATUS_H

/**
 * \file kinectStatus.h
 * \brief C++ version of C# enum KinectStatus
 * \author Gaëtan Champarnaud
 *
 * The connected state of a Kinect.
 */

#ifndef Undefined
#define Undefined	0
#endif

typedef enum
{
	Disconnected = 1,
	Connected,
	Initializing,
	Error,
	NotPowered,
	NotReady,
	DeviceNotGenuine,
	DeviceNotSupported,
	InsufficientBandwidth
} KinectStatus;

#endif
