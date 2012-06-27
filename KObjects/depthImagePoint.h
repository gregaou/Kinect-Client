#ifndef DEPTHIMAGEPOINT_H
#define DEPTHIMAGEPOINT_H

#include "kObject.h"

class DepthImagePoint : public KObject
{
	public:
		DepthImagePoint(int depth, int playerIndex = -1, int x = 0, int y = 0, int id = -1):
			KObject("DepthImagePoint", id),
			_depth(depth),
			_playerIndex(playerIndex),
			_x(x),
			_y(y)
		{}

		/* Properties */
		int getX(void) const			{ return _x; }
		void setX(int x)				{ _x = x;    }
		int getY(void) const			{ return _y; }
		void setY(int y)				{ _y = y;    }
		int getDepth(void) const		{ return _depth; }
		int getPalyerIndex(void) const	{ return _playerIndex; }

		/* Methods */
		bool equals(const DepthImagePoint& imagePoint)
		{
			return _x == imagePoint.getX() && _y == imagePoint.getY();
		}

	protected:
		int _depth, _playerIndex, _x, _y;
};

#endif
