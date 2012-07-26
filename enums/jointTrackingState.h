#ifndef JOINTTRACKINGSTATE_H
#define JOINTTRACKINGSTATE_H

/**
 * \file jointTrackingState.h
 * \brief C++ version of C# enum JointTrackingState
 * \author Gaëtan Champarnaud
 *
 * Indicates the state of a joint in a tracked skeleton. Depending on the data available in the depth stream, the skeleton stream may produce joints that are fully tracked, inferred, or not tracked.
 */

#ifndef NotTracked
#define NotTracked 0
#endif

#ifndef Tracked
#define Tracked 2
#endif

/**
 * \enum JointTrackingState
 *
 * Due to conflicts, the values 'NotTracked' and 'Tracked' are not in the enumeration but is still defined
 */
typedef enum
{
	Inferred = 1	/*!< */
} JointTrackingState;

#endif
