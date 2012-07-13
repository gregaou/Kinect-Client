#ifndef SKELETONPOINT_H
#define SKELETONPOINT_H

class SkeletonPoint
{
	public:
		SkeletonPoint (float x = 0, float y = 0, float z = 0) :
			_x(x),
			_y(y),
			_z(z)
		{}

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
