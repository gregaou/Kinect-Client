#ifndef AUDIODATAREADYEVENTARGS_H
#define AUDIODATAREADYEVENTARGS_H

#include <string.h>
#include "../network/byte.h"
#include "audioData.h"

class AudioDataReadyEventArgs
{
	public:
		AudioDataReadyEventArgs(byte* data, int length)		{ _audioData = new AudioData(data, length); }
		~AudioDataReadyEventArgs()							{ delete _audioData; }

		AudioData& getAudioData(void) const					{ return *_audioData; }

	protected:
		AudioData* _audioData;
};

#endif
