#ifndef KINECTSENSOR_H
#define KINECTSENSOR_H

#include "../enums/enums.h"
#include "kObject.h"
#include "kinectAudioSource.h"
#include "colorImageStream.h"
#include "depthImageStream.h"
#include "../other/kinectSensorCollection.h"
#include "../other/colorImagePoint.h"
#include "../other/skeletonPoint.h"
#include "../other/depthImagePoint.h"
#include "../other/colorImageFrameReadyEventArgs.h"
#include "../other/depthImageFrameReadyEventArgs.h"
#include "../other/skeletonFrameReadyEventArgs.h"
#include "../other/audioDataReadyEventArgs.h"

class KinectSensorCollection;

class KinectSensor : public KObject
{
	public:
		KinectSensor(int id = -1);
		~KinectSensor(void);

		/* Properties */
		KinectAudioSource& getAudioSource(void)			{ return _audioSource; }
		ColorImageStream& getColorStream(void)			{ return _colorStream; }
		DepthImageStream& getDepthStream(void)			{ return _depthStream; }
		std::string getDeviceConnectionId(void) const	{ return getQuery<std::string>(__func__); }

		int getElevationAngle(void) const				{ return getQuery<int>(__func__); }
		void setElevationAngle(int angle)				{ setQuery<int>(__func__, angle); }

		bool isRunning(void) const						{ return (bool)getQuery<int>(__func__); }

		static KinectSensorCollection* KinectSensors(void);
		int getMinElevationAngle(void) const			{ return getQuery<int>(__func__); }
		int getMaxElevationAngle(void) const			{ return getQuery<int>(__func__); }

//		SkeletonStream& getSkeletonStream(void) const	{ return SkeletonStream(id); }
		KinectStatus getStatus(void) const				{ return (KinectStatus)getQuery<int>(__func__); }
		std::string getUniqueKinectId(void) const		{ return getQuery<std::string>(__func__); }

		/* Methods */
		void dispose(void)								{ processQuery(buildQuery(__func__)); }

		void MapDepthFrameToColorFrame
		(
			DepthImageFormat depthImageFormat,
			std::vector<short> depthPixelData,
			ColorImageFormat colorImageFormat,
			std::vector<ColorImagePoint>* colorCoordinates
		);

		ColorImagePoint MapDepthToColorImagePoint
		(
			DepthImageFormat depthImageFormat,
			int depthX,
			int depthY,
			short depthPixelValue,
			ColorImageFormat colorImageFormat
		);

		SkeletonPoint MapDepthToSkeletonPoint
		(
			DepthImageFormat depthImageFormat,
			int depthX,
			int depthY,
			short depthPixelValue
		);

		ColorImagePoint MapSkeletonPointToColor
		(
			SkeletonPoint skeletonPoint,
			ColorImageFormat colorImageFormat
		);

		DepthImagePoint MapSkeletonPointToDepth
		(
			SkeletonPoint skeletonPoint,
			DepthImageFormat depthImageFormat
		);

		void start(void)								{ processQuery(buildQuery(__func__), 15000); }
		void stop(void)									{ processQuery(buildQuery(__func__)); }

		/* Events */
		kEventHandler<ColorImageFrameReadyEventArgs&> colorFrameReadyCb(void) const;
		void setColorFrameReadyCb(kEventHandler<ColorImageFrameReadyEventArgs&> cb);
		kEventHandler<DepthImageFrameReadyEventArgs&> depthFrameReadyCb() const;
		void setDepthFrameReadyCb(kEventHandler<DepthImageFrameReadyEventArgs&> cb);
		kEventHandler<SkeletonFrameReadyEventArgs&> skeletonFrameReadyCb(void) const;
		void setSkeletonFrameReadyCb(kEventHandler<SkeletonFrameReadyEventArgs&> cb);
		kEventHandler<AudioDataReadyEventArgs&> audioDataReadyCb(void) const;
		void setAudioDataReadyCb(kEventHandler<AudioDataReadyEventArgs&> cb);

	protected:
		KinectAudioSource _audioSource;
		ColorImageStream _colorStream;
		DepthImageStream _depthStream;
		kEventHandler<ColorImageFrameReadyEventArgs&> _colorFrameReadyCb;
		kEventHandler<DepthImageFrameReadyEventArgs&> _depthFrameReadyCb;
		kEventHandler<SkeletonFrameReadyEventArgs&> _skeletonFrameReadyCb;
		kEventHandler<AudioDataReadyEventArgs&> _audioDataReadyCb;
};

#endif
