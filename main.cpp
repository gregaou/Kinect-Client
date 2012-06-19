#include <iostream>
#include <exception>

#include "kVerboseTcpSocket.h"
#include "kPaquet.h"
#include "kClientPaquet.h"
#include "kServerPaquet.h"

using namespace std;

int main()
{
    int r = EXIT_SUCCESS;
    KTcpSocket* sock = 0;

    try
    {
        sock = new KVerboseTcpSocket(1337);
        sock->buildAddr();
        sock->connectToHost();

        while (true)
        {
            string msg;

            cout << "Message : ";
            cin >> msg;
            if (msg.size() <= 1)
                break;

            KClientPaquet cp(msg);
            cp.send(sock);

            KServerPaquet sp(sock);
            string answer((const char*)sp.data(), sp.bodySize());
            answer.push_back('\0');

            cout << "Server : " << answer << " (" << (int)sp.id() << ")" <<  endl;
        }
    }
    catch (exception& e)
    {
        cout << "Exception : " << e.what() << endl;
        r = EXIT_FAILURE;
    }

    if (sock)
        delete sock;

    KTcpSocket::end();

    return r;
}

