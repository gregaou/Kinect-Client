#include <iostream>
#include <cstdio>
#include <fstream>
#include <exception>
#include <string.h>

#include "kinect.h"
#include "wave.h"

using namespace std;

ofstream f;
bool streamAudio = true;
long int audioDataSize = 0;
const char* name;

void audioCallback(KObject* sender, AudioDataReadyEventArgs& args)
{
	if (!streamAudio)
		return;

	AudioData& audio = args.getAudioData();

	int size = audio.getLength();
	byte* buffer = new byte[size];
	audio.CopyPixelDataTo(buffer);
	f.write((const char*)buffer, size);

	delete buffer;

	audioDataSize += size;
}

void videoCallback(KObject* sender, ColorImageFrameReadyEventArgs& args)
{
	ColorImageFrame frame = args.openColorImageFrame();
	static int frameCount = 0;

	frameCount++;
	if (frameCount < 150)
		return;
	frameCount = 0;

	ostringstream fileName;
	fileName << name << "/" << name << frame.getFrameNumber() << ".jpg";
	ofstream f(fileName.str().c_str(), ios::out);

	if (!f)
	{
		cout << "unable to open " << fileName << endl;
		return;
	}

	byte* img = new byte[frame.getPixelDataLength()];
	frame.CopyPixelDataTo(img);

	f.write((const char*)img, (streamsize)frame.getPixelDataLength());
	f.close();

	delete img;

	cout << "image saved to " << fileName.str().c_str() << endl;
}

void kinectProcess(void)
{
	KinectSensorCollection sensors = *(KinectSensor::KinectSensors());
	KinectSensor sensor;
	int i, nsensors = sensors.size();

	for (i=0; i<nsensors; i++)
	{
		KinectStatus status = sensors[i].getStatus();

		if (status == Connected)
		{
			sensor = sensors[i];
			sensor.start();
			sensor.getColorStream().enable();
			break;
		}
	}

	if (i == nsensors)
		throw runtime_error("No Kinect found");

	sensor.setColorFrameReadyCb(kEventHandler<ColorImageFrameReadyEventArgs&>(videoCallback));
	sensor.setAudioDataReadyCb(kEventHandler<AudioDataReadyEventArgs&>(audioCallback));

	KinectAudioSource& source = sensor.getAudioSource();
	source.setEchoCancellationMode((EchoCancellationMode)None);
	source.setNoiseSuppression(true);

	f.seekp(WAVE_HEADER_SIZE, ios_base::beg);

	std::cout << "Capturing audio and video. Press <ENTER> to stop." << std::endl;

	getchar();
	streamAudio = false;

	writeWaveHeader(f, audioDataSize);

	sensor.stop();
}

int main(int argc, char* argv[])
{
	int r = EXIT_SUCCESS;

	name = (argc < 2 ? "unknown" : argv[1]);

	ostringstream cmd;
	cmd << "mkdir " << name;
	system(cmd.str().c_str());

	ostringstream filename;
	filename << name << "/" << name << ".wav";
	f.open(filename.str().c_str(), ios::out);

	try
	{
		kinectProcess();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		r =  EXIT_FAILURE;
	}

	f.close();

	/* Closing */
	KClient::deleteInstance();
	KinectSensorCollection::deleteInstance();
	KTcpSocket::end();

	return r;
}

