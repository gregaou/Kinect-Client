#include <string.h>
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
	unsigned int size = bodySize();

	array.resize(size);
	memcpy(array.data(), this->data(), size);

	return array;
}

std::string KServerPaquet::stringData()
{
	std::string str = std::string((const char*)data(), bodySize());
	str.push_back('\0');

	return str;
}
