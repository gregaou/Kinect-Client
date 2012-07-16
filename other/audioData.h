#ifndef AUDIODATA_H
#define AUDIODATA_H

#include <string.h>
#include "../network/byte.h"

class AudioData
{
	public:
		AudioData(byte* data, int length) :
			_data(data),
			_length(length)
		{}

		int getLength(void) const				{ return _length; }
		void CopyPixelDataTo(byte* pixelData)	{ memcpy(pixelData, _data, _length); }

	protected:
		byte* _data;
		int _length;
};

#endif
