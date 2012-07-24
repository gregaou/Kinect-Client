#ifndef MATRIX4_H
#define MATRIX4_H

#include <math.h>
#include "../network/kPaquet.h"
#include "unserializable.h"

class Matrix4 : public Unserializable
{
	public:
		Matrix4()
		{
			for (int i=0; i<4; i++)
				for (int j=0; j<4; j++)
					_m[i][j] = NAN;
		}

		Matrix4(float matrix[4][4])
		{
			for (int i=0; i<4; i++)
				for (int j=0; j<4; j++)
					_m[i][j] = matrix[i][j];
		}

		Matrix4(const Matrix4& copy)
		{
			for (int i=0; i<4; i++)
				for (int j=0; j<4; j++)
					_m[i][j] = copy._m[i][j];
		}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			int pos = 0;

			for (int i=0; i<4; i++)
			{
				for (int j=0; j<4; j++)
				{
					_m[i][j] = (float)KPaquet::getUint32(buffer, pos);
					pos += 4;
				}
			}
		}

		virtual int serializedSize(void) const		{ return 4*4*4; }

		/* Properties */
		float getM11(void) const	{ return (*this)(1, 1);	}
		void setM11(float v)		{ ref(1, 1) = v;		}
		float getM12(void) const	{ return (*this)(1, 2);	}
		void setM12(float v)		{ ref(1, 2) = v;		}
		float getM13(void) const	{ return (*this)(1, 3);	}
		void setM13(float v)		{ ref(1, 3) = v;		}
		float getM14(void) const	{ return (*this)(1, 4);	}
		void setM14(float v)		{ ref(1, 4) = v;		}

		float getM21(void) const	{ return (*this)(2, 1);	}
		void setM21(float v)		{ ref(2, 1) = v;		}
		float getM22(void) const	{ return (*this)(2, 2);	}
		void setM22(float v)		{ ref(2, 2) = v;		}
		float getM23(void) const	{ return (*this)(2, 3);	}
		void setM23(float v)		{ ref(2, 3) = v;		}
		float getM24(void) const	{ return (*this)(2, 4);	}
		void setM24(float v)		{ ref(2, 4) = v;		}

		float getM31(void) const	{ return (*this)(3, 1);	}
		void setM31(float v)		{ ref(3, 1) = v;		}
		float getM32(void) const	{ return (*this)(3,	2);	}
		void setM32(float v)		{ ref(3, 2) = v;		}
		float getM33(void) const	{ return (*this)(3, 3);	}
		void setM33(float v)		{ ref(3, 3) = v;		}
		float getM34(void) const	{ return (*this)(3, 4);	}
		void setM34(float v)		{ ref(3, 4) = v;		}

		float getM41(void) const	{ return (*this)(4, 1);	}
		void setM41(float v)		{ ref(4, 1) = v;		}
		float getM42(void) const	{ return (*this)(4, 2);	}
		void setM42(float v)		{ ref(4, 2) = v;		}
		float getM43(void) const	{ return (*this)(4, 3);	}
		void setM43(float v)		{ ref(4, 3) = v;		}
		float getM44(void) const	{ return (*this)(4, 4);	}
		void setM44(float v)		{ ref(4, 4) = v;		}

		/* Methods */
		bool equals(const Matrix4& m) const
		{
			for (int i=0; i<4; i++)
				for (int j=0; j<4; j++)
					if (_m[i][j] != m._m[i][j])
						return false;
			return true;
		}

	protected:
		float operator()(int i, int j) const		{ return _m[i-1][j-1];	}
		float& ref(int i, int j)					{ return _m[i-1][j-1];	}

		float _m[4][4];
};

#endif
