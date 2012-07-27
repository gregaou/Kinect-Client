#include "kVerboseTcpSocket.h"

using namespace std;

KVerboseTcpSocket::KVerboseTcpSocket(int port, std::string host) :
    KTcpSocket(port, host)
{
    cout << "New verbose socket (" << _host << ":" << _port << ")" << endl;
}

KVerboseTcpSocket::~KVerboseTcpSocket()
{
    cout << "Deleting socket ..." << endl;
}

void KVerboseTcpSocket::writeBuffer(const byte* buffer, size_t len)
{
    cout << "Writting " << len << " bytes ..." << endl;

    try
    {
        KTcpSocket::writeBuffer(buffer, len);
    }
    catch (exception& e)
    {
        throw std::runtime_error(e.what());
    }

    cout << "Complete" << endl;
}

void KVerboseTcpSocket::readBuffer(byte* buffer, size_t len)
{
    cout << "Reading " << len << " bytes ..." << endl;

    try
    {
        KTcpSocket::readBuffer(buffer, len);
    }
    catch (exception& e)
    {
        throw std::runtime_error(e.what());
    }

    cout << "Complete" << endl;
}

void KVerboseTcpSocket::buildAddr()
{
    cout << "Resolving host name \"" << _host << "\" ..." << endl;

    KTcpSocket::buildAddr();

    cout << "Host name resolved" << endl;
}

void KVerboseTcpSocket::connectToHost()
{
    cout << "Connecting to " << _host << ":" << _port << " ..." << endl;

    try
    {
        KTcpSocket::connectToHost();
    }
    catch (exception& e)
    {
        throw std::runtime_error(e.what());
    }

    cout << "Connexion established" << endl;
}
