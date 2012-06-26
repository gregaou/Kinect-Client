#include "kServerPaquet.h"

KServerPaquet::KServerPaquet(KTcpSocket* sock) :
    KPaquet(headerSize()),
    _sock(sock)
{
    build();
}

unsigned int KServerPaquet::headerSize() const
{
	return _headerSize;
}

void KServerPaquet::buildHeader()
{
    _sock->readBuffer(_data.data(), headerSize());
    setBodySize(bodySize());
}

void KServerPaquet::builBody()
{
	int size = bodySize();

	if (size > 0)
		_sock->readBuffer(_data.data() + headerSize(), size);
}

byte KServerPaquet::id() const
{
    return _data[8];
}

byte* KServerPaquet::data()
{
	return _data.data() + headerSize();
}

std::vector<byte> KServerPaquet::vectorData()
{
	std::vector<byte> array;
	byte* d = data();
	unsigned int size = bodySize();

	for (unsigned int i=0; i<size; i++)
		array[i] = d[i];

	return array;
}
