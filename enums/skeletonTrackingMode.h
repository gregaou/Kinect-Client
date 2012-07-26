#ifndef SKELETONTRACKINGMODE_H
#define SKELETONTRACKINGMODE_H

/**
 * \file skeletonTrackingMode.h
 * \brief C++ version of C# enum SkeletonTrackingMode
 * \author Gaëtan Champarnaud
 *
 * Options for the number of joints that are tracked when skeleton tracking is enabled.
 */

#ifndef Default
#define Default 0
#endif

/**
 * \enum SkeletonTrackingMode
 *
 * Due to conflicts, the value 'Default' is not in the enumeration but is still defined
 */
typedef enum
{
	Seated = 1	/*!< */
} SkeletonTrackingMode;

#endif
