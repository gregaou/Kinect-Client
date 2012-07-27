#include "libkinect.h"

void libKinect_init(std::string host, int port)
{
	KClient::instance(host, port);
}

void libKinect_quit()
{
	KClient::deleteInstance();
	KinectSensorCollection::deleteInstance();
	KTcpSocket::end();
}
