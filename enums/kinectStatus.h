#ifndef KINECTSTATUS_H
#define KINECTSTATUS_H

#ifndef Undefined
#define Undefined	0
#endif

//*
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
/*/
class KinectStatus
{
	public:
		static const int
				Undefined,
				Disconnected,
				Connected,
				Initializing,
				Error,
				NotPowered,
				NotReady,
				DeviceNotGenuine,
				DeviceNotSupported,
				InsufficientBandwidth;
};

const int
				KinectStatus::Undefined = 0,
				KinectStatus::Disconnected = 1,
				KinectStatus::Connected = 2,
				KinectStatus::Initializing = 3,
				KinectStatus::Error = 4,
				KinectStatus::NotPowered = 5,
				KinectStatus::NotReady = 6,
				KinectStatus::DeviceNotGenuine = 7,
				KinectStatus::DeviceNotSupported = 8,
				KinectStatus::InsufficientBandwidth = 9;
*/

#endif
