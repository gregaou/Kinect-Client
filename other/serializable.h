#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "interface.h"
#include "../network/byte.h"

//template<typename T>
//beginInterface(Serializable)
//	interfaceMethod(void serialize(byte* buffer))
//	interfaceMethod(const T& unserialize(byte* buffer))
//endInterface()

template<typename T>
class Serializable
{
	public:
		virtual ~Serializable() {}
		virtual void serialize(byte* buffer) = 0;
		virtual const T& unserialize(byte* buffer) = 0;
		virtual int serializedSize(void) = 0;
};

#endif
