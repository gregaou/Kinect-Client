#include "kClient.h"

static const int PORT = 1337;
static const std::string HOST = "127.0.0.1";

KClient::KClient() :
	_socket(0),
	_lastError(),
	_videoCb(0),
	_skeletonCb(0),
	_depthCb(0),
	_audioCb(0)
{
	try
	{
		_socket = new KTcpSocket(PORT, HOST);
		_socket->buildAddr();
		_socket->connectToHost();
	}
	catch (std::exception& e)
	{
		if (_socket)
			delete _socket;
		_socket = 0;

		std::string err("couldn't initialize kinect client : ");
		throw std::runtime_error(err + e.what());
	}

	if (pthread_create(&_streamListener, 0, &streamListenerRoutine, 0))
	{
		if (_socket)
			delete _socket;
		_socket = 0;
		throw std::runtime_error("couldn't start stream listener thread");
	}
}

KClient::~KClient()
{
	if (pthread_cancel(_streamListener))
		std::cout << "pthread_cancel failed" << std::endl;
	delete _socket;
}

void* KClient::streamListenerRoutine(void* p)
{
	std::cout << "Stream listener" << std::endl;
	return NULL;
}

KTcpSocket* KClient::socket() const
{
	return _socket;
}

std::string KClient::KinectError() const
{
	return _lastError;
}
