#ifndef MATRIX4_H
#define MATRIX4_H

/**
 * \file matrix4.h
 * \brief C++ version of C# Matrix4
 * \author Gaëtan Champarnaud
 *
 * Contains a 4x4 matrix.
 */

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

		/** \param matrix A float 2D-array */
		Matrix4(float matrix[4][4])
		{
			for (int i=0; i<4; i++)
				for (int j=0; j<4; j++)
					_m[i][j] = matrix[i][j];
		}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			for (int i=0; i<4; i++)
			{
				for (int j=0; j<4; j++)
				{
					_m[i][j] = (float)KPaquet::getUint32(buffer);
					buffer += 4;
				}
			}
		}

		virtual int serializedSize(void) const		{ return 4*4*4; }

		/* Properties */
		/** \brief Gets the identity matrix.
		 *  \return The 4x4 identity matrix */
		static Matrix4 Identity(void)
		{
			return Matrix4((float[4][4])
			{
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			});
		}

		/** \brief Gets the value in M11.
		 *  \return The M11 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM11(void) const	{ return (*this)(1, 1);	}
		/** \brief Sets the value in M11.
		 *  \param v The M11 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM11(float v)		{ ref(1, 1) = v;		}
		/** \brief Gets the value in M12.
		 *  \return The M12 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM12(void) const	{ return (*this)(1, 2);	}
		/** \brief Sets the value in M12.
		 *  \param v The M12 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM12(float v)		{ ref(1, 2) = v;		}
		/** \brief Gets the value in M13.
		 *  \return The M13 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM13(void) const	{ return (*this)(1, 3);	}
		/** \brief Sets the value in M13.
		 *  \param v The M13 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM13(float v)		{ ref(1, 3) = v;		}
		/** \brief Gets the value in M14.
		 *  \return The M14 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM14(void) const	{ return (*this)(1, 4);	}
		/** \brief Sets the value in M14.
		 *  \param v The M14 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM14(float v)		{ ref(1, 4) = v;		}

		/** \brief Gets the value in M21.
		 *  \return The M21 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM21(void) const	{ return (*this)(2, 1);	}
		/** \brief Sets the value in M21.
		 *  \param v The M21 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM21(float v)		{ ref(2, 1) = v;		}
		/** \brief Gets the value in M22.
		 *  \return The M22 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM22(void) const	{ return (*this)(2, 2);	}
		/** \brief Sets the value in M22.
		 *  \param v The M22 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM22(float v)		{ ref(2, 2) = v;		}
		/** \brief Gets the value in M23.
		 *  \return The M23 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM23(void) const	{ return (*this)(2, 3);	}
		/** \brief Sets the value in M23.
		 *  \param v The M23 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM23(float v)		{ ref(2, 3) = v;		}
		/** \brief Gets the value in M24.
		 *  \return The M24 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM24(void) const	{ return (*this)(2, 4);	}
		/** \brief Sets the value in M24.
		 *  \param v The M24 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM24(float v)		{ ref(2, 4) = v;		}

		/** \brief Gets the value in M31.
		 *  \return The M31 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM31(void) const	{ return (*this)(3, 1);	}
		/** \brief Sets the value in M31.
		 *  \param v The M31 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM31(float v)		{ ref(3, 1) = v;		}
		/** \brief Gets the value in M32.
		 *  \return The M32 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM32(void) const	{ return (*this)(3,	2);	}
		/** \brief Sets the value in M32.
		 *  \param v The M32 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM32(float v)		{ ref(3, 2) = v;		}
		/** \brief Gets the value in M33.
		 *  \return The M33 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM33(void) const	{ return (*this)(3, 3);	}
		/** \brief Sets the value in M33.
		 *  \param v The M33 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM33(float v)		{ ref(3, 3) = v;		}
		/** \brief Gets the value in M34.
		 *  \return The M34 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM34(void) const	{ return (*this)(3, 4);	}
		/** \brief Sets the value in M34.
		 *  \param v The M34 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM34(float v)		{ ref(3, 4) = v;		}

		/** \brief Gets the value in M41.
		 *  \return The M41 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM41(void) const	{ return (*this)(4, 1);	}
		/** \brief Sets the value in M41.
		 *  \param v The M41 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM41(float v)		{ ref(4, 1) = v;		}
		/** \brief Gets the value in M42.
		 *  \return The M42 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM42(void) const	{ return (*this)(4, 2);	}
		/** \brief Sets the value in M42.
		 *  \param v The M42 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM42(float v)		{ ref(4, 2) = v;		}
		/** \brief Gets the value in M43.
		 *  \return The M43 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM43(void) const	{ return (*this)(4, 3);	}
		/** \brief Sets the value in M43.
		 *  \param v The M43 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM43(float v)		{ ref(4, 3) = v;		}
		/** \brief Gets the value in M44.
		 *  \return The M44 value of the Matrix4
		 *  \see operator()(int i, int j) const
		 */
		float getM44(void) const	{ return (*this)(4, 4);	}
		/** \brief Sets the value in M44.
		 *  \param v The M44 value of the Matrix4
		 *  \see ref(int i, int j)
		 */
		void setM44(float v)		{ ref(4, 4) = v;		}

		/* Methods */
		/**
		 * \brief Compares two Matrix4 to see if they contain the same data.
		 * \param m The second object
		 * \return \e true if the second Matrix4 contains the same data as this instance; otherwise, \e false.
		 */
		bool equals(const Matrix4& m) const
		{
			for (int i=0; i<4; i++)
				for (int j=0; j<4; j++)
					if (_m[i][j] != m._m[i][j])
						return false;
			return true;
		}

		/* Operators */
		/**
		 * \brief Call operator
		 * \param i The i coordinate int the matrix (in [1..4])
		 * \param j The j coordinate int the matrix (in [1..4])
		 * \return The m(i, j) value
		 *
		 * Can be used to get values as well as any specific getter (like getM11()).
		 */
		float operator()(int i, int j) const		{ return _m[i-1][j-1];	}
		/**
		 * \param i The i coordinate int the matrix (in [1..4])
		 * \param j The j coordinate int the matrix (in [1..4])
		 * \return A reference on the m(i, j) value
		 *
		 * Can be used to set values as well as any specific setter (like setM11()).
		 */
		float& ref(int i, int j)					{ return _m[i-1][j-1];	}

	protected:
		float _m[4][4];
};

#endif
