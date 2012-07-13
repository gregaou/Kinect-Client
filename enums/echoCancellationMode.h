#ifndef ECHOCANCELLATIONMODE_H
#define ECHOCANCELLATIONMODE_H

#ifndef None
#define None		0
#endif

typedef enum
{
	CancellationOnly = 1,
	CancellationAndSuppression
} EchoCancellationMode;

#endif
