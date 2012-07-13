#ifndef VECTOR4_H
#define VECTOR4_H

class Vector4
{
	public:
		Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

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
