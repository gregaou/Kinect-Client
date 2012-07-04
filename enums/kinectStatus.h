#ifndef KINECTSTATUS_H
#define KINECTSTATUS_H

#ifndef Undefined
#define Undefined	0
#endif

typedef enum KinectStatus
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
