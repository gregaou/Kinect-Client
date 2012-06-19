#ifndef KCLIENTPAQUET_H
#define KCLIENTPAQUET_H

#include <string>
#include <stdexcept>
#include "kPaquet.h"
#include "kTcpSocket.h"

class KClientPaquet : public KPaquet
{
	public:
        KClientPaquet(std::string query);
        void send(KTcpSocket* sock);

    protected:
        virtual unsigned int headerSize(void) const;
        virtual void buildHeader(void);
        virtual void builBody(void);

		static const unsigned int _headerSize = 8;
		std::string _query;
};

#endif // KCLIENTPAQUET_H
