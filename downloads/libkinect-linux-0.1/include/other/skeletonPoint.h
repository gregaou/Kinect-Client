#ifndef SKELETONPOINT_H
#define SKELETONPOINT_H

/**
 * \file skeletonPoint.h
 * \brief C++ version of C# SkeletonPoint
 * \author Gaëtan Champarnaud
 *
 * Contains a 3D position (or point) in skeleton space.
 */

#include <math.h>
#include "unserializable.h"
#include "../network/kPaquet.h"

class SkeletonPoint : public Unserializable
{
	public:
		/**
		 * \param x The X coordinate of a SkeletonPoint
		 * \param y The Y coordinate of a SkeletonPoint
		 * \param z The Z coordinate of a SkeletonPoint
		 */
		SkeletonPoint (float x = NAN, float y = NAN, float z = NAN) :
			_x(x),
			_y(y),
			_z(z)
		{}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			_x = (float)KPaquet::getUint32(buffer);		buffer += 4;
			_y = (float)KPaquet::getUint32(buffer);		buffer += 4;
			_z = (float)KPaquet::getUint32(buffer);		buffer += 4;
		}

		virtual int serializedSize(void) const		{ return 3*4; }

		/* Properties */
		/** \brief Gets the X coordinate of a SkeletonPoint.
		 *  \return The X coordinate of the SkeletonPoint */
		float getX(void) const	{ return _x; }
		/** \brief Sets the X coordinate of a SkeletonPoint.
		 *  \param x The X coordinate of the SkeletonPoint */
		void setX(float x)		{ _x = x;    }
		/** \brief Gets the Y coordinate of a SkeletonPoint.
		 *  \return The Y coordinate of the SkeletonPoint */
		float getY(void) const	{ return _y; }
		/** \brief Sets the Y coordinate of a SkeletonPoint.
		 *  \param y The Y coordinate of the SkeletonPoint */
		void setY(float y)		{ _y = y;    }
		/** \brief Gets the Z coordinate of a SkeletonPoint.
		 *  \return The Z coordinate of the SkeletonPoint */
		float getZ(void) const	{ return _z; }
		/** \brief Sets the Z coordinate of a SkeletonPoint.
		 *  \param z The Z coordinate of the SkeletonPoint */
		void setZ(float z)		{ _z = z;	 }

		/* Methods */
		/**
		 * \brief Compares two SkeletonPoint to see if they contain the same data.
		 * \param imagePoint The second SkeletonPoint
		 * \return \e true if the second object SkeletonPoint the same data as this instance; otherwise, \e false.
		 */
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
