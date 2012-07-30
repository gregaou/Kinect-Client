#ifndef AUDIODATAREADYEVENTARGS_H
#define AUDIODATAREADYEVENTARGS_H

/**
 * \file audioDataReadyEventArgs.h
 * \brief C++ version of C# AudioDataReadyEventArgs
 * \author Gaëtan Champarnaud
 *
 * These event arguments provide information about a AudioDataReady Event.
 */

#include <string.h>
#include "../network/byte.h"
#include "audioData.h"

class AudioDataReadyEventArgs
{
	public:
		/**
		 * \param data The buffer containing new audio data
		 * \param length The length of the buffer (in bytes)
		 *
		 * For internal use \e only
		 */
		AudioDataReadyEventArgs(byte* data, int length) :
			_audioData(data, length)
		{}

		/* Methods */
		/** \brief Gets the most recent audio data.
		 *  \return Audio data */
		const AudioData& getAudioData(void) const			{ return _audioData; }

	protected:
		AudioData _audioData;
};

#endif
