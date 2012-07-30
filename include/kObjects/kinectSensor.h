#ifndef KINECTSENSOR_H
#define KINECTSENSOR_H

/**
 * \file kinectSensor.h
 * \brief C++ version of C# KinectSensor
 * \author Gaëtan Champarnaud
 *
 * Represents a single Kinect.
 */

#include "../enums/enums.h"
#include "kObject.h"
#include "kinectAudioSource.h"
#include "colorImageStream.h"
#include "depthImageStream.h"
#include "skeletonStream.h"
#include "kinectSensorCollection.h"
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
		/** \param id The sensor id (index in the sensors collection) */
		KinectSensor(int id = -1);
		/** \brief Destructor */
		~KinectSensor(void);

		/* Properties */
		/** \brief Gets the audio source for the Kinect.
		 *  \return The AudioSource of the KinectSensor */
		KinectAudioSource& getAudioSource(void)			{ return _audioSource; }
		/** \brief Gets the color stream for the Kinect.
		 *  \return The ColorStream of the KinectSensor */
		ColorImageStream& getColorStream(void)			{ return _colorStream; }
		/** \brief Gets the depth stream for the Kinect.
		 *  \return The DepthStream of the KinectSensor */
		DepthImageStream& getDepthStream(void)			{ return _depthStream; }
		/** \brief Gets the USB HUB device instance for the Kinect
		 *  \return The DeviceConnectionId of the KinectSensor */
		std::string getDeviceConnectionId(void) const	{ return getQuery<std::string>(__func__); }
		/** \brief Gets the elevation angle for the Kinect.
		 *  \return The ElevationAngle of the KinectSensor */
		int getElevationAngle(void) const				{ return getQuery<int>(__func__); }
		/** \brief Sets the elevation angle for the Kinect.
		 *  \param angle The ElevationAngle of the KinectSensor */
		void setElevationAngle(int angle)				{ setQuery<int>(__func__, angle); }
		/** \brief Gets a value indicating whether the Kinect is streaming data.
		 *  \return A boolean value that indicates whether the kinect sensor is running */
		bool isRunning(void) const						{ return (bool)getQuery<int>(__func__); }
		/** \brief Gets a collection of Kinect sensors.
		 *  \return A collection of kinect sensors */
		static KinectSensorCollection* KinectSensors(void);
		/** \brief Gets the maximum elevation angle for the Kinect sensor.
		 *  \return The MaxElevationAngle of the KinectSensor */
		int getMaxElevationAngle(void) const			{ return getQuery<int>(__func__); }
		/** \brief Gets the minimum elevation angle for the Kinect.
		 *  \return The MinElevationAngle of the KinectSensor */
		int getMinElevationAngle(void) const			{ return getQuery<int>(__func__); }
		/** \brief Gets the skeleton stream for the Kinect.
		 *  \return The SkeletonStream of the KinectSensor */
		SkeletonStream& getSkeletonStream(void) 		{ return _skeletonStream; }
		/** \brief Gets the Kinect status.
		 *  \return The Status of the KinectSensor */
		KinectStatus getStatus(void) const				{ return (KinectStatus)getQuery<int>(__func__); }
		/** \brief Do not use this property.
		 *  \return The UniqueKinectId of the KinectSensor */
		std::string getUniqueKinectId(void) const		{ return getQuery<std::string>(__func__); }

		/* Methods */
		/** \brief Terminates all data streaming and frees all memory associated with the Kinect. */
		void dispose(void)								{ processQuery(buildQuery(__func__)); }

		/**
		 * \brief Maps every point in a depth frame to the specified ColorImageFormat coordinate space.
		 * \param depthImageFormat The depth format of the source
		 * \param depthPixelData The depth frame pixel data, as retrieved from the CopyPixelDataTo method. Must be equal in length to Width*Height of the depth format specified by depthImageFormat
		 * \param colorImageFormat The desired target image format
		 * \param colorCoordinates The ColorImagePoint array to receive the data. Each element will be be the result of mapping the corresponding depthPixelData element to the specified ColorImageFormat coordinate space. Must be equal in length to depthPixelData
		 *
		 * There is a known issue with calling this method when the sensor is stopped or disconnected.
		 */
		void MapDepthFrameToColorFrame
		(
			DepthImageFormat depthImageFormat,
			std::vector<short>& depthPixelData,
			ColorImageFormat colorImageFormat,
			std::vector<ColorImagePoint>* colorCoordinates
		);

		/**
		 * \brief Map a depth coordinate with depth value to a color coordinate.
		 * \param depthImageFormat The depth format of the source
		 * \param depthX The X coordinate of the depth frame
		 * \param depthY The Y coordinate of the depth frame
		 * \param depthPixelValue The value from the depth frame's pixel data at the given (depthX, depthY) coordinate
		 * \param colorImageFormat The desired target image format
		 * \return The ColorImagePoint corresponding to the point in DepthImageFrame space.
		 *
		 * Since the input format is based on the depth frame's pixel data, the depth is in the high-order 13 bits of the pixel (see Depth Stream). If you are calling this function using the depth value in depthPixelValue, bit shift the depth value left by 3 bits before calling this function.
		 * There is a known issue with calling this method when the sensor is stopped or disconnected.
		 */
		ColorImagePoint MapDepthToColorImagePoint
		(
			DepthImageFormat depthImageFormat,
			int depthX,
			int depthY,
			short depthPixelValue,
			ColorImageFormat colorImageFormat
		);

		/**
		 * \brief Looks up the skeleton point location from a coordinate (depthX, depthY) and depth value.
		 * \param depthImageFormat The format to use in the conversion
		 * \param depthX The X coordinate of the depth frame
		 * \param depthY The Y coordinate of the depth frame
		 * \param depthPixelValue The value from the depth frame's pixel data at the given coordinate (depthX, depthY)
		 * \return The SkeletonPoint The skeleton point for the given position (X, Y), depth and format
		 *
		 * This method performs a mapping from depth space to the same 3D space the skeleton data is described in. The coordinate and depth values may come from the depth frame or artificial values can be used.
		 * There is a known issue with calling this method when the sensor is stopped or disconnected.
		 */
		SkeletonPoint MapDepthToSkeletonPoint
		(
			DepthImageFormat depthImageFormat,
			int depthX,
			int depthY,
			short depthPixelValue
		);

		/**
		 * \brief Looks up the color frame coordinates for a given skeleton point.
		 * \param skeletonPoint The supplied SkeletonPoint
		 * \param colorImageFormat The color format to convert to
		 * \return The ColorImagePoint corresponding to the given skeleton point
		 *
		 * There is a known issue with calling this method when the sensor is stopped or disconnected.
		 */
		ColorImagePoint MapSkeletonPointToColor
		(
			SkeletonPoint skeletonPoint,
			ColorImageFormat colorImageFormat
		);

		/**
		 * \brief Looks up the depth frame coordinate for a given skeleton point.
		 * \param skeletonPoint The given SkeletonPoint
		 * \param depthImageFormat The depth format to convert to
		 * \return The DepthImagePoint that that contains the coordinate (X, Y) and depth of the given skeleton point
		 *
		 * The DepthImagePoint that that contains the coordinate (X, Y) and depth of the given skeleton point.
		 */
		DepthImagePoint MapSkeletonPointToDepth
		(
			SkeletonPoint skeletonPoint,
			DepthImageFormat depthImageFormat
		);

		/** \brief Start streaming data from the Kinect. */
		void start(void)								{ processQuery(buildQuery(__func__), 15000); }
		/** \brief Stop streaming data from the Kinect. */
		void stop(void)									{ processQuery(buildQuery(__func__)); }

		/* Events */
		KEventHandler<ColorImageFrameReadyEventArgs&> colorFrameReadyCb(void) const;
		/** \brief Sets the callback that is called when a new color frame for the ColorStream is available.
		 *  \param cb The function to be called */
		void setColorFrameReadyCb(KEventHandler<ColorImageFrameReadyEventArgs&> cb);

		KEventHandler<DepthImageFrameReadyEventArgs&> depthFrameReadyCb() const;
		/** \brief Sets the callback that is called when a new depth frame for the DepthStream is available.
		 *  \param cb The function to be called */
		void setDepthFrameReadyCb(KEventHandler<DepthImageFrameReadyEventArgs&> cb);

		KEventHandler<SkeletonFrameReadyEventArgs&> skeletonFrameReadyCb(void) const;
		/** \brief Sets the callback that is called when a new skeleton frame for the SkeletonStream is available.
		 *  \param cb The function to be called */
		void setSkeletonFrameReadyCb(KEventHandler<SkeletonFrameReadyEventArgs&> cb);

		KEventHandler<AudioDataReadyEventArgs&> audioDataReadyCb(void) const;
		/** \brief Sets the callback that is called when some new audio data for the AudioSource are available.
		 *  \param cb The function to be called */
		void setAudioDataReadyCb(KEventHandler<AudioDataReadyEventArgs&> cb);

	protected:
		KinectAudioSource _audioSource;
		ColorImageStream _colorStream;
		DepthImageStream _depthStream;
		SkeletonStream _skeletonStream;
		KEventHandler<ColorImageFrameReadyEventArgs&> _colorFrameReadyCb;
		KEventHandler<DepthImageFrameReadyEventArgs&> _depthFrameReadyCb;
		KEventHandler<SkeletonFrameReadyEventArgs&> _skeletonFrameReadyCb;
		KEventHandler<AudioDataReadyEventArgs&> _audioDataReadyCb;
};

#endif
