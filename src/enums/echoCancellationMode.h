#ifndef ECHOCANCELLATIONMODE_H
#define ECHOCANCELLATIONMODE_H

/**
 * \file echoCancellationMode.h
 * \brief C++ version of C# enum EchoCancellationMode
 * \author Gaëtan Champarnaud
 *
 * Options for applying echo cancellation and noise suppression to the audio data.
 */

#ifndef None
#define None		0
#endif

/**
 * \enum EchoCancellationMode
 *
 * Due to conflicts, the value 'None' is not in the enumeration but is still defined
 */
typedef enum
{
	CancellationOnly = 1,		/*!< */
	CancellationAndSuppression	/*!< */
} EchoCancellationMode;

#endif
