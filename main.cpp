#include <iostream>
#include <exception>

#include "kClient.h"
#include "kVerboseTcpSocket.h"
#include "kPaquet.h"
#include "kClientPaquet.h"
#include "kServerPaquet.h"

using namespace std;

int main()
{
    int r = EXIT_SUCCESS;
    KClient* c = 0;

	try
	{
        c = new KClient();
	}
	catch (exception& e)
	{
		delete c;
		cout << e.what() << endl;
		KTcpSocket::end();
		return EXIT_FAILURE;
    }

	while (true)
	{
		string msg;

		cout << "Message : ";
		cin >> msg;
        if (msg == "close" || msg == "exit" || msg == "quit")
            break;

        if (!c->sendQuery(msg))
            break;
	}

    KTcpSocket::end();

    return r;
}

