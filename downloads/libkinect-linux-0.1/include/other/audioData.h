#ifndef AUDIODATA_H
#define AUDIODATA_H

/**
 * \file audioData.h
 * \brief C++ version of C# AudioData
 * \author Gaëtan Champarnaud
 *
 * Contains buffered audio data from the Kinect.
 */

#include <string.h>
#include "../network/byte.h"

class AudioData
{
	public:
		/**
		 * \param data A buffer that contains audio data
		 * \param length The length of the buffer (in bytes)
		 * \see KinectSensor::getAudioSource()
		 *
		 * For internal use \e only
		 */
		AudioData(byte* data, int length) :
			_data(data),
			_length(length)
		{}

		/* Properties */
		/** \brief Gets the length of the buffer
		 *  \return The Length of the buffer */
		int getLength(void) const				{ return _length; }

		/* Methods */
		/**
		 * \brief Copies the audio data to a pre-allocated array of bytes.
		 * \param pixelData An array of bytes to receive the audio data
		 *
		 * When creating the array, the array size must be equal to the Length property.
		 */
		void CopyPixelDataTo(byte* pixelData) const	{ memcpy(pixelData, _data, _length); }

	protected:
		byte* _data;
		int _length;
};

#endif
