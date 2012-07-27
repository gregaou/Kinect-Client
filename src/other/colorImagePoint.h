#ifndef COLORIMAGEPOINT_H
#define COLORIMAGEPOINT_H

/**
 * \file colorImagePoint.h
 * \brief C++ version of C# ColorImagePoint
 * \author Gaëtan Champarnaud
 *
 * Contains a single point in a ColorImageFrame.
 */

#include <math.h>

class ColorImagePoint
{
	public:
		/**
		 * \param x The X coordinate of a ColorImagePoint
		 * \param y The Y coordinate of a ColorImagePoint
		 */
		ColorImagePoint(int x = NAN, int y = NAN):
			_x(x),
			_y(y)
		{}

		/* Properties */
		/** \brief Gets the X coordinate of a ColorImagePoint.
		 *  \return The X coordinate of the ColorImagePoint */
		int getX(void) const	{ return _x; }
		/** \brief Sets the X coordinate of a ColorImagePoint.
		 *  \param x The X coordinate of the ColorImagePoint */
		void setX(int x)		{ _x = x;    }
		/** \brief Gets the Y coordinate of a ColorImagePoint.
		 *  \return The Y coordinate of the ColorImagePoint */
		int getY(void) const	{ return _y; }
		/** \brief Sets the Y coordinate of a ColorImagePoint.
		 *  \param y The Y coordinate of the ColorImagePoint */
		void setY(int y)		{ _y = y;    }

		/* Methods */
		/**
		 * \brief Compares two ColorImagePoint to see if they contain the same data.
		 * \param imagePoint The second ColorImagePoint
		 * \return \e true if the second object ColorImagePoint the same data as this instance; otherwise, \e false.
		 */
		bool equals(const ColorImagePoint& imagePoint)
		{
			return _x == imagePoint.getX() && _y == imagePoint.getY();
		}

	protected:
		int _x, _y;
};

#endif
