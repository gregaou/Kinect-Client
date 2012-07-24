#include <string.h>
#include <iostream>
#include "wave.h"

char firstHeaderBloc[WAVE_FIRST_BLOC_SIZE] =
{
	'R', 'I', 'F', 'F',
	0, 0, 0, 0,				// File size - 8
	'W', 'A', 'V', 'E',
};

char secondHeaderBloc[WAVE_SECOND_BLOC_SIZE] =
{
	'f', 'm', 't', ' ',
	0, 0, 0, 0,				// Block size
	0, 0,					// PCM Format
	0, 0,					// Chanels number
	0, 0, 0, 0,				// Frequency
	0, 0, 0, 0,				// Bytes per sec
	0, 0,					// Bytes per bloc
	0, 0,					// Bits per sample
	0, 0					// ???
};

char thirdHeaderBloc[WAVE_THIRD_BLOC_SIZE] =
{
	'd','a', 't', 'a',
	0, 0, 0, 0				// Data size (file size - WAVE_HEADER_SIZE)
};

void writeWaveValue(char* src, int value, size_t size)
{
	int masks[4] = {0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000};

	for (unsigned int i=0; i<size; i++)
		src[i] = (value & masks[i]) >> (i*8);
}

void writeWaveHeader(std::ofstream& f, int audioDataSize)
{
	std::streampos p = f.tellp();

	f.seekp(0, std::ios_base::beg);

	/* First bloc */
	writeWaveValue((char*)&firstHeaderBloc[4], audioDataSize + WAVE_HEADER_SIZE - 8, 4);

	/* Second bloc */
	writeWaveValue((char*)&secondHeaderBloc[4], WAVE_SECOND_BLOC_SIZE - 8, 4);
	writeWaveValue((char*)&secondHeaderBloc[8], WAVE_PCM_FORMAT, 2);
	writeWaveValue((char*)&secondHeaderBloc[10], KINECT_CHANNELS, 2);
	writeWaveValue((char*)&secondHeaderBloc[12], KINECT_FREQUENCY, 4);
	writeWaveValue((char*)&secondHeaderBloc[16], KINECT_BYTES_PER_SEC, 4);
	writeWaveValue((char*)&secondHeaderBloc[20], KINECT_BYTES_PER_BLOC, 2);
	writeWaveValue((char*)&secondHeaderBloc[22], KINECT_BITS_PER_SAMPLE, 2);

	/* Third bloc */
	writeWaveValue((char*)&thirdHeaderBloc[4], audioDataSize, 4);

	f.write(firstHeaderBloc, WAVE_FIRST_BLOC_SIZE);
	f.write(secondHeaderBloc, WAVE_SECOND_BLOC_SIZE);
	f.write(thirdHeaderBloc, WAVE_THIRD_BLOC_SIZE);

	f.seekp(p);
}
