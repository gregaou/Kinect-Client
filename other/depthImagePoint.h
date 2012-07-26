#ifndef DEPTHIMAGEPOINT_H
#define DEPTHIMAGEPOINT_H

/**
 * \file depthImagePoint.h
 * \brief C++ version of C# DepthImagePoint
 * \author Gaëtan Champarnaud
 *
 * Contains a single point in a DepthImageFrame.
 */

class DepthImagePoint
{
	public:
		/**
		 * \param depth The depth value
		 * \param playerIndex The player index
		 * \param x The X coordinate of a DepthImagePoint
		 * \param y The Y coordinate of a DepthImagePoint
		 */
		DepthImagePoint(int depth, int playerIndex = -1, int x = 0, int y = 0):
			_depth(depth),
			_playerIndex(playerIndex),
			_x(x),
			_y(y)
		{}

		/* Properties */
		/** \brief Gets the X coordinate of the DepthImagePoint.
		 *  \return The X coordinate of the DepthImagePoint */
		int getX(void) const			{ return _x; }
		/** \brief Sets the X coordinate of the DepthImagePoint.
		 *  \param x The X coordinate of the DepthImagePoint */
		void setX(int x)				{ _x = x;    }
		/** \brief Gets the Y coordinate of the DepthImagePoint.
		 *  \return The Y coordinate of the DepthImagePoint */
		int getY(void) const			{ return _y; }
		/** \brief Sets the Y coordinate of the DepthImagePoint.
		 *  \param y The Y coordinate of the DepthImagePoint */
		void setY(int y)				{ _y = y;    }
		/** \brief Gets the depth value.
		 *  \return The Depth of the DepthImagePoint */
		int getDepth(void) const		{ return _depth; }
		/** \brief Gets the player index.
		 *  \return The PlayerIndex of the DepthImagePoint */
		int getPlayerIndex(void) const	{ return _playerIndex; }

		/* Methods */
		/**
		 * \brief Compares two DepthImagePoint to see if they contain the same data.
		 * \param imagePoint The second DepthImagePoint
		 * \return \e true if the second object DepthImagePoint the same data as this instance; otherwise, \e false.
		 */
		bool equals(const DepthImagePoint& imagePoint)
		{
			return _x == imagePoint.getX() && _y == imagePoint.getY();
		}

	protected:
		int _depth, _playerIndex, _x, _y;
};

#endif
