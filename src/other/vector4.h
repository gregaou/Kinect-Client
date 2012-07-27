#ifndef VECTOR4_H
#define VECTOR4_H

/**
 * \file vector4.h
 * \brief C++ version of C# Vector4
 * \author Gaëtan Champarnaud
 *
 * Contains a 4D position (X, Y, Z, W).
 */

#include <math.h>
#include "unserializable.h"

class Vector4 : public Unserializable
{
	public:
		/**
		 * \param x The X coordinate of the (X, Y, Z, W) position
		 * \param y The Y coordinate of the (X, Y, Z, W) position
		 * \param z The Z coordinate of the (X, Y, Z, W) position
		 * \param w The W coordinate of the (X, Y, Z, W) position
		 */
		Vector4(float x = NAN, float y = NAN, float z = NAN, float w = NAN) :
			_x(x),
			_y(y),
			_z(z),
			_w(w)
		{}

		/** \param vector A float array containing the (X, Y, Z, W) coordinates */
		Vector4(float vector[4]) :
			_x(vector[0]),
			_y(vector[1]),
			_z(vector[2]),
			_w(vector[3])
		{}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			_x = (float)KPaquet::getUint32(buffer);		buffer += 4;
			_y = (float)KPaquet::getUint32(buffer);		buffer += 4;
			_z = (float)KPaquet::getUint32(buffer);		buffer += 4;
			_w = (float)KPaquet::getUint32(buffer);		buffer += 4;
		}

		virtual int serializedSize(void) const		{ return 4*4; }

		/* Properties */
		/** \brief Gets the X coordinate of the (X, Y, Z, W) position.
		 *  \return The X coordinate */
		float getX(void) const		{ return _x;	}
		/** \brief Sets the X coordinate of the (X, Y, Z, W) position.
		 *  \param x The X coordinate */
		void setX(float x)			{ _x = x;		}
		/** \brief Gets the Y coordinate of the (X, Y, Z, W) position.
		 *  \return The Y coordinate */
		float getY(void) const		{ return _y;	}
		/** \brief Sets the Y coordinate of the (X, Y, Z, W) position.
		 *  \param y The Y coordinate */
		void setY(float y)			{ _y = y;		}
		/** \brief Gets the Z coordinate of the (X, Y, Z, W) position.
		 *  \return The Z coordinate */
		float getZ(void) const		{ return _z;	}
		/** \brief Sets the Z coordinate of the (X, Y, Z, W) position.
		 *  \param z The Z coordinate */
		void setZ(float z)			{ _z = z;		}
		/** \brief Gets the W coordinate of the (X, Y, Z, W) position.
		 *  \return The W coordinate */
		float getW(void) const		{ return _w;	}
		/** \brief Sets the W coordinate of the (X, Y, Z, W) position.
		 *  \param w The W coordinate */
		void setW(float w)			{ _w = w;		}

		/* Methods */
		/**
		 * \brief Compares two Vector4 to see if they contain the same data.
		 * \param v The second Vector4
		 * \return \e true if the second Vector4 contains the same data as this instance; otherwise, \e false.
		 */
		bool equals(const Vector4& v) const
		{
			return _x == v.getX() &&
				   _y == v.getY() &&
				   _z == v.getZ() &&
				   _w == v.getW();
		}

	protected:
		float _x, _y, _z, _w;
};

#endif
