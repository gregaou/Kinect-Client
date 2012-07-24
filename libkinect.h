#ifndef KINECT_H
#define KINECT_H

#include "enums/enums.h"
#include "kExceptions/kConnectionException.h"
#include "kExceptions/kQueryErrorException.h"
#include "kObjects/kObjects.h"
#include "other/other.h"

void libKinect_init(std::string host);
void libKinect_quit(void);

#endif
