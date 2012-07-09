#ifndef DEPTHIMAGEFORMAT_H
#define DEPTHIMAGEFORMAT_H

#ifndef Undefined
#define Undefined	0
#endif

typedef enum DepthImageFormat
{
	Resolution640x480Fps30 = 1,
	Resolution320x240Fps30,
	Resolution80x60Fps30
} DepthImageFormat;

int getDepthImageWidth(DepthImageFormat format);
int getDepthImageHeight(DepthImageFormat format);

#endif
