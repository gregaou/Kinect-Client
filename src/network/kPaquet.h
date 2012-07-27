#ifndef KPAQUET_H
#define KPAQUET_H

#include <vector>
#include "byte.h"

class KPaquet
{
	public:
		KPaquet(unsigned int headerSize);
		~KPaquet() {}
		unsigned int bodySize(void) const;
		unsigned int totalSize(void);
		unsigned int timestamp(void);

        static unsigned int getUint32(const byte* data, int start = 0);
        static void setUint32(byte* data, unsigned int v, int start = 0);

	protected:
		void setBodySize(unsigned int size);
		void build(void);

		virtual unsigned int headerSize(void) const = 0;
		virtual void buildHeader(void) = 0;
		virtual void builBody(void) = 0;

		std::vector<byte> _data;
};

#endif
