#ifndef KINECTSENSOR_H
#define KINECTSENSOR_H

#include "../enums/enums.h"
#include "kObject.h"
#include "kinectSensorCollection.h"
#include "colorImagePoint.h"
#include "skeletonPoint.h"
#include "depthImagePoint.h"
#include "colorImageFrameReadyEventArgs.h"

class KinectSensorCollection;

class KinectSensor : public KObject
{
	public:
		KinectSensor(int id = -1);
		~KinectSensor(void);

		/* Properties */
//		AudioSource& getAudioSource(void) const			{ return AudioSource(id); }
//		ColorImageStream& getColorStream(void) const	{ return ColorImageStream(id); }
//		DepthImageStream& getDepthStream(void) const	{ return DepthImageStream(id); }
		std::string getDeviceConnectionId(void) const	{ return getQuery<std::string>(__func__); }

		int getElevationAngle(void) const				{ return getQuery<int>(__func__); }
		void setElevationAngle(int angle)				{ setQuery<int>(__func__, angle); }

		bool isRunning(void) const						{ return (bool)getQuery<int>(__func__); }

		static KinectSensorCollection* KinectSensors(void);
		int getMinElevationAngle(void) const			{ return getQuery<int>(__func__); }
		int getMaxElevationAngle(void) const			{ return getQuery<int>(__func__); }

//		SkeletonStream& getSkeletonStream(void) const	{ return SkeletonStream(id); }
		KinectStatus getStatus(void) const				{ return (KinectStatus)getQuery<int>(__func__); }
		std::string getUniqueKinectId(void);

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

	protected:
		kEventHandler<ColorImageFrameReadyEventArgs&> _colorFrameReadyCb;
		std::string _uniqueKinectId;
};

#endif
