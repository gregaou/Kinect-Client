#ifndef KSERVERPAQUET_H
#define KSERVERPAQUET_H

#include "kPaquet.h"
#include "kTcpSocket.h"

class KServerPaquet : public KPaquet
{
	public:
        KServerPaquet(KTcpSocket* sock);
        byte id(void) const;
		byte* data(void);
		std::vector<byte> vectorData(void);
		std::string stringData(void);

	protected:
        virtual unsigned int headerSize(void) const;
        virtual void buildHeader(void);
        virtual void builBody(void);

        KTcpSocket* _sock;
        static const int _headerSize = 9;
};

#endif
