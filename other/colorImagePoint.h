#ifndef COLORIMAGEPOINT_H
#define COLORIMAGEPOINT_H

#include <math.h>

class ColorImagePoint
{
	public:
		ColorImagePoint(int x = NAN, int y = NAN):
			_x(x),
			_y(y)
		{}

		/* Properties */
		int getX(void) const	{ return _x; }
		void setX(int x)		{ _x = x;    }
		int getY(void) const	{ return _y; }
		void setY(int y)		{ _y = y;    }

		/* Methods */
		bool equals(const ColorImagePoint& imagePoint)
		{
			return _x == imagePoint.getX() && _y == imagePoint.getY();
		}

	protected:
		int _x, _y;
};

#endif
