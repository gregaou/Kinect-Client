#ifndef SKELETONPOINT_H
#define SKELETONPOINT_H

#include <math.h>
#include "unserializable.h"
#include "../network/kPaquet.h"

class SkeletonPoint : public Unserializable
{
	public:
		SkeletonPoint (float x = NAN, float y = NAN, float z = NAN) :
			_x(x),
			_y(y),
			_z(z)
		{}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			int pos = 0;

			_x = (float)KPaquet::getUint32(buffer, pos);	pos += 4;
			_y = (float)KPaquet::getUint32(buffer, pos);	pos += 4;
			_z = (float)KPaquet::getUint32(buffer, pos);	pos += 4;
		}

		virtual int serializedSize(void) const		{ return 3*4; }

		/* Properties */
		float getX(void) const	{ return _x; }
		void setX(float x)		{ _x = x;    }
		float getY(void) const	{ return _y; }
		void setY(float y)		{ _y = y;    }
		float getZ(void) const	{ return _z; }
		void setZ(float z)		{ _z = z;	 }

		/* Methods */
		bool equals(const SkeletonPoint& skeletonPoint)
		{
			return _x == skeletonPoint.getX() &&
				   _y == skeletonPoint.getY() &&
				   _z == skeletonPoint.getZ();
		}

	protected:
		float _x, _y, _z;
};

#endif
