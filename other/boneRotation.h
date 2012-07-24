#ifndef BONEROTATION_H
#define BONEROTATION_H

#include "matrix4.h"
#include "vector4.h"
#include "unserializable.h"

class BoneRotation : public Unserializable
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

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			_matrix.unserialize(buffer);
			buffer += _matrix.serializedSize();
			_quaternion.unserialize(buffer);
		}

		virtual int serializedSize(void) const		{ return _matrix.serializedSize() + _quaternion.serializedSize(); }

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
