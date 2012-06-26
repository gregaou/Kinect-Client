#include "kPaquet.h"
#include <iostream>

KPaquet::KPaquet(unsigned int headerSize) : _data(headerSize, 0)
{
}

unsigned int KPaquet::bodySize() const
{
    return getUint32(_data.data());
}

unsigned int KPaquet::totalSize()
{
	return headerSize() + bodySize();
}

unsigned int KPaquet::timestamp(void)
{
    return getUint32(_data.data(), 4);
}

unsigned int KPaquet::getUint32(const byte* data, int start)
{
	return (unsigned int)((data[start]   << 24) |
						  (data[start+1] << 16) |
						  (data[start+2] << 8 ) |
						  (data[start+3]      ));
}

void KPaquet::setUint32(byte* data, unsigned int v, int start)
{
	data[start]   = (v & 0xff000000) >> 24;
	data[start+1] = (v & 0x00ff0000) >> 16;
	data[start+2] = (v & 0x0000ff00) >> 8 ;
    data[start+3] = (v & 0x000000ff)      ;
}

void KPaquet::setBodySize(unsigned int size)
{
    _data.resize(headerSize() + size);
}

void KPaquet::build()
{
    buildHeader();
    builBody();
}
