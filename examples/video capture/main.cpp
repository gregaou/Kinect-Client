#include <stdlib.h>
#include <libkinect.h>

using namespace std;

void kinectProcess(void);
void videoCallback(KObject* sender, ColorImageFrameReadyEventArgs& args);

int main()
{
	int r = EXIT_SUCCESS;

	try
	{
		libKinect_init("192.168.56.1", 1337);
		kinectProcess();
		libKinect_quit();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		r = EXIT_FAILURE;
	}

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

	/* Setting video */
	sensor.getColorStream().enable();
	sensor.setColorFrameReadyCb(KEventHandler<ColorImageFrameReadyEventArgs&>(videoCallback));

	cout << "Capturing video ..." << endl;
	getchar();
	sensor.stop();
}

void videoCallback(KObject* sender, ColorImageFrameReadyEventArgs& args)
{
	ColorImageFrame frame = args.openColorImageFrame();

	ostringstream fileName;
	fileName << "frame" <<  frame.getFrameNumber() << ".jpg";
	ofstream file(fileName.str().c_str(), ios::out);

	if (!file)
	{
		cout << "unable to open " << fileName.str().c_str() << endl;
		return;
	}

	byte* img = new byte[frame.getPixelDataLength()];

	frame.CopyPixelDataTo(img);
	file.write((const char*)img, (streamsize)frame.getPixelDataLength());
	file.close();
	delete img;

	cout << "image saved to " << fileName.str().c_str() << endl;
}
