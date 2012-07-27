#include <iostream>
#include <string.h>
#include "kPaquet.h"
#include "kTcpSocket.h"

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
	return (unsigned int)ntohl(*(int*)(data + start));
}

void KPaquet::setUint32(byte* data, unsigned int v, int start)
{
	v = htonl(v);
	memcpy(data + start, (byte*)&v, 4);
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
