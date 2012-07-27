#ifndef BEAMANGLECHANGEDEVENTARGS_H
#define BEAMANGLECHANGEDEVENTARGS_H

/**
 * \file beamAngleChangedEventArgs.h
 * \brief C++ version of C# BeamAngleChangedEventArgs
 * \author Gaëtan Champarnaud
 *
 * These event arguments provide information about a KinectAudioSource for a BeamAngleChanged event.
 */

class BeamAngleChangedEventArgs
{
	public:
		/**
		 * \param angle The horizontal angle between the Kinect and the direction of the audio source
		 *
		 * For internal use \e only
		 */
		BeamAngleChangedEventArgs(double angle) :
			_angle(angle)
		{}

		/* Properties */
		/** \brief Gets the horizontal angle between the Kinect and the direction of the audio source.
		 *  \return The angle
		 *
		 * This angle is the direction that the sensor is actively listening. It ranges from - 50 to +50 degrees.
		 */
		double getAngle(void) const		{ return _angle; }
		/** \brief Sets the horizontal angle between the Kinect and the direction of the audio source.
		 *  \param angle The angle
		 *
		 * This angle is the direction that the sensor is actively listening. It ranges from - 50 to +50 degrees.
		 */
		void setAngle(double angle)		{ _angle = angle; }

	protected:
		double _angle;
};

#endif
