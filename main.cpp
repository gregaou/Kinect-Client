#include <iostream>
#include <fstream>
#include <exception>

#include "network/network.h"
#include "other/other.h"
#include "kObjects/kObjects.h"
#include "kExceptions/kQueryErrorException.h"

using namespace std;

void kinectProcess(void);
void elevationAngleTests(KinectSensor& sensor);
void audioTests(KinectSensor& sensor);
void beamAngleChanged(KObject* sender, BeamAngleChangedEventArgs& args);
void soundSourceAngleChanged(KObject* sender, SoundSourceAngleChangedEventArgs& args);

void statusChanged(KObject* sender, KinectStatus status)
{
	cout << "Status changed to " << status << endl;
}

void colorFrameReady(KObject* sender, ColorImageFrameReadyEventArgs& e)
{
	ColorImageFrame frame = e.openColorImageFrame();

	ostringstream name;
	name << "../image" << frame.getFrameNumber() << ".jpg";
	ofstream f(name.str().c_str(), ios::out);

	if (!f)
	{
		cout << "unable to open " << name << endl;
		return;
	}

	byte* img = new byte[frame.getPixelDataLength()];
	frame.CopyPixelDataTo(img);

	f.write((const char*)img, (streamsize)frame.getPixelDataLength());
	f.close();

	delete img;

	cout << "image saved to " << name.str().c_str() << endl;
}

void depthFrameReady(KObject* sender, DepthImageFrameReadyEventArgs& e)
{
	DepthImageFrame frame = e.openDepthImageFrame();

	ostringstream name;
	name << "../image" << frame.getFrameNumber() << ".pgm";
	ofstream f(name.str().c_str(), ios::out);
	int w = frame.getWidth(), h = frame.getHeight();

	if (!f)
	{
		cout << "unable to open " << name << endl;
		return;
	}

	/* Writing ASCII PGM header */
	f << "P2\n" << w << " " << h << "\n255\n";

	int length = frame.getPixelDataLength();
	short* pixels = new short[length];

	frame.CopyPixelDataTo((byte*)pixels);

	for (int j=0; j<h; j++)
	{
		for (int i=0; i<w; i++)
		{
			// discard the portion of the depth that contains only the player index
			short depth = (short)(pixels[j*w+i] >> frame.getPlayerIndexBitmaskWidth());

			// to convert to a byte we're looking at only the lower 8 bits
			// by discarding the most significant rather than least significant data
			// we're preserving detail, although the intensity will "wrap"
			// add 1 so that too far/unknown is mapped to black
			byte intensity = (byte)((depth + 1) & 0xff);

			f << (int)intensity;
			if (i == w-1)
				f << "\n";
			else
				f << " ";
		}
	}

	delete pixels;

	f.close();
}

int main()
{
	int r = EXIT_SUCCESS;

	try
	{
		kinectProcess();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		r =  EXIT_FAILURE;
	}

	/* Closing */
	KClient::deleteInstance();
	KinectSensorCollection::deleteInstance();
	KTcpSocket::end();

    return r;
}

void kinectProcess()
{
	/*
	KinectSensorCollection* sensors = KinectSensor::KinectSensors();
	sensors->setStatusChangeCb(kEventHandler<KinectStatus>(statusChanged));

	while (true);
	/*/
	KinectSensorCollection sensors = *(KinectSensor::KinectSensors());
	KinectSensor sensor;
	int i, nsensors = sensors.size();
	sensors.setStatusChangeCb(kEventHandler<KinectStatus>(statusChanged));

	cout << nsensors << " sensors" << endl;

	for (i=0; i<nsensors; i++)
	{
		KinectStatus status = sensors[i].getStatus();
		cout << "status " << i << " : " << status << endl;

		if (status == Connected)
		{
			sensor = sensors[i];
			sensor.start();
			break;
		}
	}

	if (i == nsensors)
		throw runtime_error("No Kinect found");

//	sensor.setColorFrameReadyCb(kEventHandler<ColorImageFrameReadyEventArgs&>(colorFrameReady));
//	sensor.setDepthFrameReadyCb(kEventHandler<DepthImageFrameReadyEventArgs&>(depthFrameReady));
//	while (true);

	audioTests(sensor);

	sensor.stop();
}

void elevationAngleTests(KinectSensor& sensor)
{
	cout << "Elevation angle : " << sensor.getElevationAngle() << endl;
	int angle = sensor.getElevationAngle(), min, max;
	int inc = 2;

	min = sensor.getMinElevationAngle();
	max = sensor.getMaxElevationAngle();

	cout << min << " <= angle <= " << max << endl;

	while (true)
	{
		if (angle + inc > max || angle + inc < min)
			inc *= -1;
		angle += inc;

		try
		{
			sensor.setElevationAngle(angle);
		}
		catch (KQueryErrorException& e)
		{
			cout << e.what() << endl;
			switch (e.code())
			{
				case InvalidOperation:
					angle -= inc;
					break;
				case BadArgument:
					cout << "invalid angle " << angle << endl;
					return;
				default:
					throw runtime_error(e.what());
			}
		}
	}
}

void audioTests(KinectSensor& sensor)
{
	KinectAudioSource& source = sensor.getAudioSource();

	source.start();
	cout << "AutomaticGainControlEnabled : " << source.getAutomaticGainControlEnabled() << endl;
	cout << "BeamAngle : " << source.getMinBeamAngle() << " <= " << source.getBeamAngle() << " <= " << source.getMaxBeamAngle() << endl;
	cout << "BeamAngleMode : " << source.getBeamAngleMode() << endl;
	cout << "EchoCancellationMode : " << source.getEchoCancellationMode() << endl;
	cout << "EchoCancellationSpeakerIndex : " << source.getEchoCancellationSpeakerIndex() << endl;
	cout << "ManualBeamAngle : " << source.getManualBeamAngle() << endl;
	cout << "SoundSourceAngle : " << source.getMinSoundSourceAngle() << " <= " << source.getSoundSourceAngle() << " <= " << source.getMaxSoundSourceAngle() << " (confidence : " << source.getSoundSourceAngleConfidence()*100 << "%)" << endl;
	cout << "NoiseSuppression : " << source.getNoiseSuppression() << endl;

	source.setBeamAngleChangedCb(beamAngleChanged);
	source.setSoundSourceAngleChangedCb(soundSourceAngleChanged);

	while (true);
}

void beamAngleChanged(KObject* sender, BeamAngleChangedEventArgs& args)
{
	cout << "beam angle changed to " << args.getAngle() << endl;
}

void soundSourceAngleChanged(KObject* sender, SoundSourceAngleChangedEventArgs& args)
{
	cout << "sound source angle changed to " << args.getAngle() << " (confidence : " << args.getConfidenceLevel()*100 << ")" << endl;
}

