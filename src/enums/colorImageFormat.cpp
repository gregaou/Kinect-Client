#include <exception>
#include <stdexcept>
#include "colorImageFormat.h"

int getColorImageWidth(ColorImageFormat format)
{
	switch (format)
	{
		case RgbResolution640x480Fps30:
		case YuvResolution640x480Fps15:
		case RawYuvResolution640x480Fps15:
			return 640;
		case RgbResolution1280x960Fps12:
			return 1280;
		default:
			throw std::runtime_error("Unknown color mage format");
	}
}

int getColorImageHeight(ColorImageFormat format)
{
	switch (format)
	{
		case RgbResolution640x480Fps30:
		case YuvResolution640x480Fps15:
		case RawYuvResolution640x480Fps15:
			return 480;
		case RgbResolution1280x960Fps12:
			return 960;
		default:
			throw std::runtime_error("Unknown depth image format");
	}
}

int getColorImageFPS(ColorImageFormat format)
{
    switch (format)
    {
        case RgbResolution640x480Fps30:
            return 30;
        case YuvResolution640x480Fps15:
        case RawYuvResolution640x480Fps15:
            return 15;
        case RgbResolution1280x960Fps12:
            return 12;
        default:
			throw std::runtime_error("Unknown depth image format");
    }
}
