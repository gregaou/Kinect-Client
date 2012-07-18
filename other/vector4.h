#ifndef VECTOR4_H
#define VECTOR4_H

#include <math.h>
#include "serializable.h"

class Vector4 : implements Serializable<Vector4>
{
	public:
		Vector4(float x = NAN, float y = NAN, float z = NAN, float w = NAN) :
			_x(x),
			_y(y),
			_z(z),
			_w(w)
		{}

		Vector4(float vector[4]) :
			_x(vector[0]),
			_y(vector[1]),
			_z(vector[2]),
			_w(vector[3])
		{}

		Vector4(const Vector4& copy) :
			_x(copy.getX()),
			_y(copy.getY()),
			_z(copy.getZ()),
			_w(copy.getW())
		{}

		/* Serializable */
		virtual void serialize(byte* buffer)
		{
			int pos = 0;

			KPaquet::setUint32(buffer, *(int*)&_x, (pos+=4));
			KPaquet::setUint32(buffer, *(int*)&_y, (pos+=4));
			KPaquet::setUint32(buffer, *(int*)&_z, (pos+=4));
			KPaquet::setUint32(buffer, *(int*)&_w, (pos+=4));
		}

		virtual const Vector4& unserialize(byte* buffer)
		{
			int pos = 0;

			_x = (float)KPaquet::getUint32(buffer, (pos+=4));
			_y = (float)KPaquet::getUint32(buffer, (pos+=4));
			_z = (float)KPaquet::getUint32(buffer, (pos+=4));
			_w = (float)KPaquet::getUint32(buffer, (pos+=4));

			return *this;
		}

		virtual int serializedSize(void)		{ return 4*4; }

		/* Properties */
		float getX(void) const		{ return _x;	}
		void setX(float x)			{ _x = x;		}
		float getY(void) const		{ return _y;	}
		void setY(float y)			{ _y = y;		}
		float getZ(void) const		{ return _z;	}
		void setZ(float z)			{ _z = z;		}
		float getW(void) const		{ return _w;	}
		void setW(float w)			{ _w = w;		}

		/* Methods */
		bool equals(const Vector4& vec) const
		{
			return _x == vec.getX() &&
				   _y == vec.getY() &&
				   _z == vec.getZ() &&
				   _w == vec.getW();
		}

	protected:
		float _x, _y, _z, _w;
};

#endif
