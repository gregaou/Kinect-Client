#ifndef BONEORIENTATION_H
#define BONEORIENTATION_H

/**
 * \file boneOrientation.h
 * \brief C++ version of C# BoneOrientation
 * \author Gaëtan Champarnaud
 *
 * Contains orientation information for an individual bone in a skeleton.
 */

#include "unserializable.h"
#include "boneRotation.h"
#include "../enums/jointType.h"

class BoneOrientation : public Unserializable
{
	public:
		BoneOrientation() :
			_absoluteRotation(),
			_hierarchicalRotation()
		{}

		/**
		 * \param absoluteRotation The rotation of the bone relative to camera coordinates
		 * \param endJoint The skeleton joint where the bone ends
		 * \param hierarchicalRotation The rotation of the bone relative to the parent bone
		 * \param startJoint The skeleton joint where the bone starts
		 */
		BoneOrientation(BoneRotation& absoluteRotation, JointType endJoint, BoneRotation& hierarchicalRotation, JointType startJoint) :
			_absoluteRotation(absoluteRotation),
			_endJoint(endJoint),
			_hierarchicalRotation(hierarchicalRotation),
			_startJoint(startJoint)
		{}

		/* Unserializable */
		virtual void unserialize(byte* buffer)
		{
			_absoluteRotation.unserialize(buffer);
			buffer += _absoluteRotation.serializedSize();

			_endJoint = (JointType)(*buffer);
			buffer++;

			_hierarchicalRotation.unserialize(buffer);
			buffer += _hierarchicalRotation.serializedSize();

			_startJoint = (JointType)(*buffer);
			buffer++;
		}

		virtual int serializedSize(void) const
		{
			return 2 * _absoluteRotation.serializedSize() + 2;
		}

		/* Properties */
		/** \brief Gets the rotation of the bone relative to camera coordinates
		 *  \return The AbsoluteRotation of the BoneOrientation */
		const BoneRotation& getAbsoluteRotation(void) const						{ return _absoluteRotation; }
		/** \brief Sets the rotation of the bone relative to camera coordinates
		 *  \param The absoluteRotation AbsoluteRotation of the BoneOrientation */
		void setAbsoluteRotation(BoneRotation& absoluteRotation)				{ _absoluteRotation = absoluteRotation; }
		/** \brief Gets the skeleton joint where the bone ends.
		 *  \return The EndJoint of the BoneOrientation */
		JointType getEndJoint(void) const										{ return _endJoint; }
		/** \brief Gets the rotation of the bone relative to the parent bone.
		 *  \return The HierarchicalRotation of the BoneOrientation */
		const BoneRotation& getHierarchicalRotation(void) const					{ return _hierarchicalRotation; }
		/** \brief Sets the rotation of the bone relative to the parent bone.
		 *  \param hierarchicalRotation The HierarchicalRotation of the BoneOrientation */
		void setHierarchicalRotation(BoneRotation& hierarchicalRotation)		{ _hierarchicalRotation = hierarchicalRotation; }
		/** \brief Gets the skeleton joint where the bone starts.
		 *  \return The StartJoint of the BoneOrientation */
		JointType getStartJoint(void) const										{ return _startJoint; }

	protected:
		BoneRotation _absoluteRotation;
		JointType _endJoint;
		BoneRotation _hierarchicalRotation;
		JointType _startJoint;
};

#endif
