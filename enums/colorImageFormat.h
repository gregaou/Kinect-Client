#ifndef COLORIMAGEFORMAT_H
#define COLORIMAGEFORMAT_H

#ifndef Undefined
#define Undefined	0
#endif

typedef enum ColorImageFormat
{
	RgbResolution640x480Fps30 = 1,
	RgbResolution1280x960Fps12,
	YuvResolution640x480Fps15,
	RawYuvResolution640x480Fps15
} ColorImageFormat;

#endif
