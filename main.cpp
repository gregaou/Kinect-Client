//#include <iostream>
//#include <exception>

//#include "kClient.h"
//#include "kVerboseTcpSocket.h"
//#include "kPaquet.h"
//#include "kClientPaquet.h"
//#include "kServerPaquet.h"

using namespace std;

int main()
{
	int r = 42;
	/*
	int r = EXIT_SUCCESS;
	KClient* c = 0;
    KTcpSocket* sock = 0;

	cout << "Debut du programme" << endl;

	try
	{
		c = new KClient();
		sock = c->socket();
	}
	catch (exception& e)
	{
		delete c;
		cout << e.what() << endl;
		KTcpSocket::end();
		return EXIT_FAILURE;
	}

	cout << "client connected" << endl;

	while (true)
	{
		string msg;

		cout << "Message : ";
		cin >> msg;
		if (msg.size() <= 1)
			break;

		try
		{
			KClientPaquet cp(msg);
			cp.send(sock);

			KServerPaquet sp(sock);
			string answer((const char*)sp.data(), sp.bodySize());
			answer.push_back('\0');

			cout << "Server : " << answer << " (" << (int)sp.id() << ")" <<  endl;
		}
		catch (exception& e)
		{
			cout << "Exception : " << e.what() << endl;
			r = EXIT_FAILURE;
			break;
		}
	}

	KTcpSocket::end();
	*/

//	cout << "rerzer" << endl;

    return r;
}

