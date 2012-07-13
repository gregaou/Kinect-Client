#ifndef AUDIODATAREADYEVENTARGS_H
#define AUDIODATAREADYEVENTARGS_H

#include <string.h>
#include "../network/byte.h"

class AudioDataReadyEventArgs
{
	public:
		AudioDataReadyEventArgs(byte* data, int length) :
			_data(data),
			_length(length)
		{}

		void CopyPixelDataTo(byte* pixelData)
		{
			memcpy(pixelData, _data, _length);
		}

	protected:
		byte* _data;
		int _length;
};

#endif
