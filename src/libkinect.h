#ifndef KINECT_H
#define KINECT_H

/**
 * \file libkinect.h
 * \brief header included by the user
 * \author Gaëtan Champarnaud
 * \version 0.1
 *
 * This is the only header that the users have to include.
 */

#include "enums/enums.h"
#include "kExceptions/kConnectionException.h"
#include "kExceptions/kQueryErrorException.h"
#include "kObjects/kObjects.h"
#include "other/other.h"

/**
 * \brief Initializes the library (must be called before any other function/method).
 * \param host The IP of the host. ("localhost" will not work, use "127.0.0.1" instead)
 * \param port The port listened by the host
 */
void libKinect_init(std::string host, int port);
/** \brief Quits the library and frees memory. */
void libKinect_quit(void);

#endif
