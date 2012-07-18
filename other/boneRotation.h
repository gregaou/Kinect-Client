#ifndef BONEROTATION_H
#define BONEROTATION_H

#include "matrix4.h"
#include "vector4.h"
#include "serializable.h"

class BoneRotation : implements Serializable<BoneRotation>
{
	public:
		BoneRotation() :
			_matrix(),
			_quaternion()
		{}

		BoneRotation(Matrix4& matrix, Vector4& quaternion):
			_matrix(matrix),
			_quaternion(quaternion)
		{}

		BoneRotation(const BoneRotation& copy) :
			_matrix(copy.getMatrix()),
			_quaternion(copy.getQuaternion())
		{}

		/* Serializable */
		virtual void serialize(byte* buffer)
		{
			_matrix.serialize(buffer);
			buffer += _matrix.serializedSize();
			_quaternion.serialize(buffer);
		}

		virtual const BoneRotation& unserialize(byte* buffer)
		{
			_matrix.unserialize(buffer);
			buffer += _matrix.serializedSize();
			_quaternion.unserialize(buffer);

			return *this;
		}

		virtual int serializedSize(void)		{ return _matrix.serializedSize() + _quaternion.serializedSize(); }

		/* Properties */
		const Matrix4& getMatrix(void) const		{ return _matrix; }
		void setMatrix(Matrix4& matrix)				{ _matrix = matrix; }
		const Vector4& getQuaternion(void) const	{ return _quaternion; }
		void setQuaternion(Vector4& quaternion)		{ _quaternion = quaternion; }

	protected:
		Matrix4 _matrix;
		Vector4 _quaternion;
};

#endif
