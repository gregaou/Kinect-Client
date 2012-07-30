#include <iostream>
#include <cstdio>
#include <fstream>
#include <exception>
#include <string.h>

#include <libkinect.h>
#include "wave.h"

using namespace std;

ofstream f;
bool streamAudio = true;
long int audioDataSize = 0;
const char* name;

void kinectProcess(void);
void audioCallback(KObject* sender, AudioDataReadyEventArgs& args);

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

	libKinect_init("192.168.3.23");

	try
	{
		kinectProcess();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		r = EXIT_FAILURE;
	}

	f.close();
	libKinect_quit();

	return r;
}

void kinectProcess()
{
	KinectSensorCollection sensors = *(KinectSensor::KinectSensors());
	KinectSensor sensor;
	int i, nsensors = sensors.size();

	/* Looking for a connected sensor */
	for (i=0; i<nsensors; i++)
	{
		KinectStatus status = sensors[i].getStatus();

		if (status == Connected)
		{
			sensor = sensors[i];
			sensor.start();
			break;
		}
	}

	if (i == nsensors)
		throw runtime_error("No Kinect found");

	/* Setting audio */
	f.seekp(WAVE_HEADER_SIZE, ios_base::beg);

	KinectAudioSource& audioSource = sensor.getAudioSource();
	audioSource.enable();
	audioSource.setEchoCancellationMode((EchoCancellationMode)None);
	audioSource.setNoiseSuppression(true);
	sensor.setAudioDataReadyCb(kEventHandler<AudioDataReadyEventArgs&>(audioCallback));

	std::cout << "Capturing audio and video. Press <ENTER> to stop." << std::endl;

	/* Waiting for the end of the program */
	getchar();
	streamAudio = false;

	writeWaveHeader(f, audioDataSize);

	sensor.stop();
}

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

