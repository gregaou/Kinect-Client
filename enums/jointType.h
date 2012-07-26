#ifndef JOINTTYPE_H
#define JOINTTYPE_H

/**
 * \file jointType.h
 * \brief C++ version of C# enum JointType
 * \author Gaëtan Champarnaud
 *
 * The joint types that make up a skeleton.
 */

/** \enum JointType */
typedef enum
{
	HipCenter,		/*!< */
	Spine,			/*!< */
	ShoulderCenter,	/*!< */
	Head,			/*!< */
	ShoulderLeft,	/*!< */
	ElbowLeft,		/*!< */
	WristLeft,		/*!< */
	HandLeft,		/*!< */
	ShoulderRight,	/*!< */
	ElbowRight,		/*!< */
	WristRight,		/*!< */
	HandRight,		/*!< */
	HipLeft,		/*!< */
	KneeLeft,		/*!< */
	AnkleLeft,		/*!< */
	FootLeft,		/*!< */
	HipRight,		/*!< */
	KneeRight,		/*!< */
	AnkleRight,		/*!< */
	FootRight		/*!< */
} JointType;

#endif
