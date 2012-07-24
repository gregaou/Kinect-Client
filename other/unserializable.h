#ifndef UNSERIALIZABLE_H
#define UNSERIALIZABLE_H

#include "../network/byte.h"

class Unserializable
{
	public:
		virtual ~Unserializable() {}
		virtual void unserialize(byte* buffer) = 0;
		virtual int serializedSize(void) const = 0;
};

#endif
