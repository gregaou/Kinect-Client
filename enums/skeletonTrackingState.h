#ifndef SKELETONTRACKINGSTATE_H
#define SKELETONTRACKINGSTATE_H

/**
 * \file skeletonTrackingState.h
 * \brief C++ version of C# enum SkeletonTrackingState
 * \author Gaëtan Champarnaud
 *
 * Options for tracking (collecting and streaming) skeleton data.
 */

#ifndef NotTracked
#define NotTracked 0
#endif

#ifndef Tracked
#define Tracked 2
#endif

typedef enum
{
	PositionOnly = 1
} SkeletonTrackingState;

#endif
