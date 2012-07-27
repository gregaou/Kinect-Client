#include "kClientPaquet.h"

KClientPaquet::KClientPaquet(std::string query) :
    KPaquet(headerSize()),
	_query(query)
{
    //std::cout << "End of constructor" << std::endl;
    build();
}

unsigned int KClientPaquet::headerSize() const
{
	return _headerSize;
}

void KClientPaquet::buildHeader()
{
    setBodySize(_query.size());

	/* body size */
    setUint32(_data.data(), _query.size());
	/* timestamp */
    setUint32(_data.data(), 0, 4);
}

void KClientPaquet::builBody()
{
	if (_query.copy((char*)(_data.data() + headerSize()), _query.size()) != _query.size())
        throw std::runtime_error("The query couldn't be copied entirely into the paquet");
}

void KClientPaquet::send(KTcpSocket* sock)
{
    sock->writeBuffer(_data.data(), totalSize());
}
