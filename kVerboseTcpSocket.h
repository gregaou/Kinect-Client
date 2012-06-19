#ifndef KVERBOSETCPSOCKET_H
#define KVERBOSETCPSOCKET_H

#include "kTcpSocket.h"

class KVerboseTcpSocket : public KTcpSocket
{
    public:
        KVerboseTcpSocket(int port, std::string host = "127.0.0.1");
        virtual ~KVerboseTcpSocket();
        static void end(void);
        virtual void writeBuffer(const byte* buffer, size_t len);
        virtual void readBuffer(byte* buffer, size_t len);
        virtual void buildAddr(void);
        virtual void connectToHost(void);
};

#endif // KVERBOSETCPSOCKET_H
