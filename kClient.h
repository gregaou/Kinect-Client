#ifndef KCLIENT_H
#define KCLIENT_H

#include <iostream>
#include <exception>
#include <vector>
#include <pthread.h>
#include "byte.h"
#include "kTcpSocket.h"

typedef void (*kCallback)(const std::vector<byte>& frame);

class KClient
{
	public:
		KClient(void);
		~KClient(void);
		KTcpSocket* socket(void) const;
		std::string KinectError(void) const;

	protected:
		static void* streamListenerRoutine(void* p);

		KTcpSocket* _socket;
		pthread_t _streamListener;
		std::string _lastError;
		kCallback _videoCb, _skeletonCb, _depthCb, _audioCb;
};

#endif // KCLIENT_H
