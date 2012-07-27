#include "depthImageFormat.h"

int getDepthImageWidth(DepthImageFormat format)
{
	switch (format)
	{
		case Resolution640x480Fps30:
			return 640;
		case Resolution320x240Fps30:
			return 320;
		case Resolution80x60Fps30:
			return 80;
		default:
			return -1;
	}
}

int getDepthImageHeight(DepthImageFormat format)
{
	switch (format)
	{
		case Resolution640x480Fps30:
			return 480;
		case Resolution320x240Fps30:
			return 240;
		case Resolution80x60Fps30:
			return 60;
		default:
			return -1;
	}
}
