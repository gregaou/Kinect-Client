#ifndef SOUNDSOURCEANGLECHANGEDEVENTARGS_H
#define SOUNDSOURCEANGLECHANGEDEVENTARGS_H

/**
 * \file soundSourceAngleChangedEventArgs.h
 * \brief C++ version of C# SoundSourceAngleChangedEventArgs
 * \author Gaëtan Champarnaud
 *
 * These event arguments provide information about a KinectAudioSource for a SoundSourceAngleChanged event.
 */

class SoundSourceAngleChangedEventArgs
{
	public:
		/**
		 * \param angle The sound source angle
		 * \param confidenceLevel The confidence that the sound source angle is correct
		 *
		 * For internal use \e only
		 */
		SoundSourceAngleChangedEventArgs(double angle, double confidenceLevel) :
			_angle(angle),
			_confidenceLevel(confidenceLevel)
		{}

		/* Properties */
		/**
		 * \brief Gets the sound source angle.
		 * \return The sound source angle
		 *
		 * It is the direction the sensor believes the strongest speech signal is coming from (and the confidence it has that the speech signal is coming from that direction). The angle ranges from - 50 to +50 degrees.
		 */
		double getAngle(void) const						{ return _angle; }
		/**
		 * \brief Gets the confidence that the sound source angle is correct.
		 * \return The confidence level
		 *
		 * It is the direction the sensor believes the strongest speech signal is coming from. The value ranges from 0.0 (no confidence) to 1.0 (total confidence).
		 */
		double getConfidenceLevel(void) const			{ return _confidenceLevel; }
		/**
		 * \brief Sets the confidence that the sound source angle is correct.
		 * \param confidenceLevel The confidence level
		 *
		 * It is the direction the sensor believes the strongest speech signal is coming from. The value ranges from 0.0 (no confidence) to 1.0 (total confidence).
		 */
		void setConfidenceLevel(double confidenceLevel)	{ _confidenceLevel = confidenceLevel; }

	protected:
		double _angle;
		double _confidenceLevel;
};

#endif
