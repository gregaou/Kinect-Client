#ifndef BONEORIENTATION_H
#define BONEORIENTATION_H

#include "serializable.h"
#include "boneRotation.h"
#include "../enums/jointType.h"

class BoneOrientation : implements Serializable<BoneOrientation>
{
	public:
		BoneOrientation() :
			_absoluteRotation(),
			_hierarchicalRotation()
		{}

		BoneOrientation(BoneRotation& absoluteRotation, JointType endJoint, BoneRotation hierarchicalRotation, JointType startJoint) :
			_absoluteRotation(absoluteRotation),
			_endJoint(endJoint),
			_hierarchicalRotation(hierarchicalRotation),
			_startJoint(startJoint)
		{}

		BoneOrientation(const BoneOrientation& copy) :
			_absoluteRotation(copy.getAbsoluteRotation()),
			_endJoint(copy.getEndJoint()),
			_hierarchicalRotation(copy.getHierarchicalRotation()),
			_startJoint(copy.getStartJoint())
		{}

		/* Serializable */
		virtual void serialize(byte* buffer)
		{
			int pos = 0;

			_absoluteRotation.serialize(buffer);
			pos += _absoluteRotation.serializedSize();

			buffer[pos++] = (byte)_endJoint;

			_hierarchicalRotation.unserialize(buffer + pos);
			pos += _hierarchicalRotation.serializedSize();

			buffer[pos++] = (byte)_startJoint;
		}

		virtual const BoneOrientation& unserialize(byte* buffer)
		{
			int pos = 0;

			_absoluteRotation.unserialize(buffer);
			pos += _absoluteRotation.serializedSize();

			_endJoint = (JointType)(buffer[pos++]);

			_hierarchicalRotation.unserialize(buffer + pos);
			pos += _hierarchicalRotation.serializedSize();

			_startJoint = (JointType)(buffer[pos++]);

			return *this;
		}

		virtual int serializedSize(void)
		{
			return 2 * _absoluteRotation.serializedSize() + 2;
		}

		const BoneRotation& getAbsoluteRotation(void) const						{ return _absoluteRotation; }
		void setAbsoluteRotation(BoneRotation& absoluteRotation)				{ _absoluteRotation = absoluteRotation; }
		JointType getEndJoint(void) const										{ return _endJoint; }
		const BoneRotation& getHierarchicalRotation(void) const					{ return _hierarchicalRotation; }
		void setHierarchicalRotation(BoneRotation& hierarchicalRotation)		{ _hierarchicalRotation = hierarchicalRotation; }
		JointType getStartJoint(void) const										{ return _startJoint; }


	protected:
		BoneRotation _absoluteRotation;
		JointType _endJoint;
		BoneRotation _hierarchicalRotation;
		JointType _startJoint;
};

#endif
