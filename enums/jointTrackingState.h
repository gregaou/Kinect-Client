#ifndef JOINTTRACKINGSTATE_H
#define JOINTTRACKINGSTATE_H

#ifndef NotTracked
#define NotTracked 0
#endif

#ifndef Tracked
#define Tracked 2
#endif

typedef enum JointTrackingState
{
	Inferred = 1
} JointTrackingState;

#endif
