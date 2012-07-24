#include "libkinect.h"

void libKinect_init(std::string host)
{
	KClient::instance(host);
}

void libKinect_quit()
{
	KClient::deleteInstance();
	KinectSensorCollection::deleteInstance();
	KTcpSocket::end();
}
