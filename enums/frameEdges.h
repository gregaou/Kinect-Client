#ifndef FRAMEEDGES_H
#define FRAMEEDGES_H

typedef int FrameEdges;

#ifndef None
#define None		0
#endif

#define RIGHT		(1 << 0)
#define LEFT		(1 << 1)
#define TOP			(1 << 2)
#define BOTTOM		(1 << 3)

#endif
