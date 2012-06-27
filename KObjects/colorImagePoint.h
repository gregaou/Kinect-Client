#ifndef COLORIMAGEPOINT_H
#define COLORIMAGEPOINT_H

#include "kObject.h"

class ColorImagePoint : public KObject
{
	public:
		ColorImagePoint(int x = 0, int y = 0, int id = -1):
			KObject("ColorImagePoint", id),
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



#endif // COLORIMAGEPOINT_H
