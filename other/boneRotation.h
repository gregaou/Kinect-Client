#ifndef BONEROTATION_H
#define BONEROTATION_H

/**
 * \file boneRotation.h
 * \brief C++ version of C# BoneRotation
 * \author Gaëtan Champarnaud
 *
 * Contains rotation data for a single bone.
 */

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

		/**
		 * \param matrix Bone rotation matrix
		 * \param quaternion Bone rotation quaternion
		 */
		BoneRotation(Matrix4& matrix, Vector4& quaternion):
			_matrix(matrix),
			_quaternion(quaternion)
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
		/** \brief Gets a bone rotation matrix.
		 *  \return The Matrix of the BoneRotation */
		const Matrix4& getMatrix(void) const		{ return _matrix; }
		/** \brief Sets a bone rotation matrix.
		 *  \param matrix The Matrix of the BoneRotation */
		void setMatrix(Matrix4& matrix)				{ _matrix = matrix; }
		/** \brief Gets a bone rotation quaternion.
		 *  \return The Quaternion of the BoneRotation */
		const Vector4& getQuaternion(void) const	{ return _quaternion; }
		/** \brief Sets a bone rotation quaternion.
		 *  \param quaternion The Quaternion of the BoneRotation */
		void setQuaternion(Vector4& quaternion)		{ _quaternion = quaternion; }

	protected:
		Matrix4 _matrix;
		Vector4 _quaternion;
};

#endif
