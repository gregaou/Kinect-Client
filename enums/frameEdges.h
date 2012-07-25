#ifndef FRAMEEDGES_H
#define FRAMEEDGES_H

/**
 * \file frameEdges.h
 * \brief C++ version of C# enum FrameEdges
 * \author Gaëtan Champarnaud
 *
 * Specifies how much of the user's body is visible to the Kinect.
 * N.B : this values are used as flags, so they have been defined with #define instead of a classical enumeration.
 * Due to conflicts on Windows, the defines are uppercase.
 */

typedef int FrameEdges;

#ifndef None
#define None		0
#endif

#define RIGHT		(1 << 0)
#define LEFT		(1 << 1)
#define TOP			(1 << 2)
#define BOTTOM		(1 << 3)

#endif
