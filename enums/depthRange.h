#ifndef DEPTHRANGE_H
#define DEPTHRANGE_H

/**
 * \file depthRange.h
 * \brief C++ version of C# enum DepthRange
 * \author Gaëtan Champarnaud
 *
 * Options for the range of the depth data, which determine how close a person can be to the Kinect and still be trackable.
 */

#ifndef Default
#define Default 0
#endif

/**
 * \enum DepthRange
 *
 * Due to conflicts, the value 'Default' is not in the enumeration but is still defined
 */
typedef enum
{
	Near = 1	/*!< */
} DepthRange;

#endif
