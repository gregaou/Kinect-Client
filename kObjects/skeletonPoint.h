#ifndef SKELETONPOINT_H
#define SKELETONPOINT_H

#include "kObject.h"

class SkeletonPoint : public KObject
{
	public:
		SkeletonPoint (int x = 0, int y = 0, int z = 0, int id = -1) :
			KObject("SkeletonPoint", id),
			_x(x),
			_y(y),
			_z(z)
		{}

		/* Properties */
		int getX(void) const	{ return _x; }
		void setX(int x)		{ _x = x;    }
		int getY(void) const	{ return _y; }
		void setY(int y)		{ _y = y;    }
		int getZ(void) const	{ return _z; }
		void setZ(int z)		{ _z = z;	 }

		/* Methods */
		bool equals(const SkeletonPoint& skeletonPoint)
		{
			return _x == skeletonPoint.getX() &&
				   _y == skeletonPoint.getY() &&
				   _z == skeletonPoint.getZ();
		}

	protected:
		int _x, _y, _z;
};

#endif
