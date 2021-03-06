#include "kinectSensor.h"
#include "../network/kPaquet.h"

KinectSensor::KinectSensor(int id) :
	KObject("KinectSensor", id),
	_audioSource(id),
	_colorStream(id),
	_depthStream(id),
	_skeletonStream(id),
	_colorFrameReadyCb(0),
	_depthFrameReadyCb(0),
	_skeletonFrameReadyCb(0),
	_audioDataReadyCb(0)
{
	_client->addSensor(this);
}

KinectSensor::~KinectSensor()
{
	_client->removeSensor(this);
}

KinectSensorCollection* KinectSensor::KinectSensors(void)
{
	return KinectSensorCollection::instance();
}

void KinectSensor::MapDepthFrameToColorFrame
(
	DepthImageFormat depthImageFormat,
	std::vector<short>& depthPixelData,
	ColorImageFormat colorImageFormat,
	std::vector<ColorImagePoint>* colorCoordinates
)
{
	/* Building args */
	std::vector<std::string> args;

	args.push_back(toString<int>(3 + depthPixelData.size()));
	args.push_back(toString<int>((int)depthImageFormat));
	for (unsigned int i=0; i<depthPixelData.size(); i++)
		args.push_back(toString<short>(depthPixelData[i]));
	args.push_back(toString<int>((int)colorImageFormat));

	/* Processing the query */
	processQuery(buildQuery(__func__, args), 10000);

	std::vector<std::string>* res = splitString(lastMessage(), SEP);

	/* Checking the result */
	checkRet(depthPixelData.size() * 2, res->size());

	for (unsigned int i=0; i<res->size(); i+=2)
	{
		int x = valueOf<int>((*res)[i]);
		int y = valueOf<int>((*res)[i+1]);
		colorCoordinates->push_back(ColorImagePoint(x, y));
	}

	delete res;
}

ColorImagePoint KinectSensor::MapDepthToColorImagePoint
(
		 DepthImageFormat depthImageFormat,
		 int depthX,
		 int depthY,
		 short depthPixelValue,
		 ColorImageFormat colorImageFormat
)
{
	/* Building args */
	std::vector<std::string> args;

	args.push_back(toString<int>((int)depthImageFormat));
	args.push_back(toString<int>(depthX));
	args.push_back(toString<int>(depthY));
	args.push_back(toString<short>(depthPixelValue));
	args.push_back(toString<int>((int)colorImageFormat));

	/* Processign the query */
	processQuery(buildQuery(__func__, args));

	/* Getting the result */
	std::vector<std::string>* res = splitString(lastMessage(), SEP);

	/* Checking the result */
	checkRet(2, res->size());

	int x = valueOf<int>((*res)[0]);
	int y = valueOf<int>((*res)[1]);
	delete res;

	return ColorImagePoint(x, y);
}

SkeletonPoint KinectSensor::MapDepthToSkeletonPoint
(
		 DepthImageFormat depthImageFormat,
		 int depthX,
		 int depthY,
		 short depthPixelValue
)
{
	/* Building args */
	std::vector<std::string> args;

	args.push_back(toString<int>((int)depthImageFormat));
	args.push_back(toString<int>(depthX));
	args.push_back(toString<int>(depthY));
	args.push_back(toString<short>(depthPixelValue));

	/* Processign the query */
	processQuery(buildQuery(__func__, args));

	/* Getting the result */
	std::vector<std::string>* res = splitString(lastMessage(), SEP);

	/* Checking the result */
	checkRet(3, res->size());

	float x = valueOf<float>((*res)[0]);
	float y = valueOf<float>((*res)[1]);
	float z = valueOf<float>((*res)[2]);
	delete res;

	return SkeletonPoint(x, y, z);
}

ColorImagePoint KinectSensor::MapSkeletonPointToColor
(
	SkeletonPoint skeletonPoint,
	ColorImageFormat colorImageFormat
)
{
	/* Building args */
	std::vector<std::string> args;

	args.push_back(toString<float>(skeletonPoint.getX()));
	args.push_back(toString<float>(skeletonPoint.getY()));
	args.push_back(toString<float>(skeletonPoint.getZ()));
	args.push_back(toString<int>((int)colorImageFormat));

	/* Processign the query */
	processQuery(buildQuery(__func__, args));

	/* Getting the result */
	std::vector<std::string>* res = splitString(lastMessage(), SEP);

	/* Checking the result */
	checkRet(2, res->size());

	int x = valueOf<int>((*res)[0]);
	int y = valueOf<int>((*res)[1]);
	delete res;

	return ColorImagePoint(x, y);
}

DepthImagePoint KinectSensor::MapSkeletonPointToDepth
(
	SkeletonPoint skeletonPoint,
	DepthImageFormat depthImageFormat
)
{
	/* Building args */
	std::vector<std::string> args;

	args.push_back(toString<float>(skeletonPoint.getX()));
	args.push_back(toString<float>(skeletonPoint.getY()));
	args.push_back(toString<float>(skeletonPoint.getZ()));
	args.push_back(toString<int>((int)depthImageFormat));

	/* Processign the query */
	processQuery(buildQuery(__func__, args));

	/* Getting the result */
	std::vector<std::string>* res = splitString(lastMessage(), SEP);

	/* Checking the result */
	checkRet(4, res->size());

	int x = valueOf<int>((*res)[0]);
	int y = valueOf<int>((*res)[1]);
	int depth = valueOf<int>((*res)[2]);
	int playerIndex = valueOf<int>((*res)[3]);
	delete res;

	return DepthImagePoint(depth, playerIndex, x, y);
}

KEventHandler<ColorImageFrameReadyEventArgs&> KinectSensor::colorFrameReadyCb() const
{
	return _colorFrameReadyCb;
}

void KinectSensor::setColorFrameReadyCb(KEventHandler<ColorImageFrameReadyEventArgs&> cb)
{
	if (!_colorFrameReadyCb)
		processQuery(buildQuery("ColorFrameReady"));
	_colorFrameReadyCb = cb;
}

KEventHandler<DepthImageFrameReadyEventArgs&> KinectSensor::depthFrameReadyCb() const
{
	return _depthFrameReadyCb;
}

void KinectSensor::setDepthFrameReadyCb(KEventHandler<DepthImageFrameReadyEventArgs&> cb)
{
	if (!_depthFrameReadyCb)
		processQuery(buildQuery("DepthFrameReady"));
	_depthFrameReadyCb = cb;
}

KEventHandler<SkeletonFrameReadyEventArgs&> KinectSensor::skeletonFrameReadyCb(void) const
{
	return _skeletonFrameReadyCb;
}

void KinectSensor::setSkeletonFrameReadyCb(KEventHandler<SkeletonFrameReadyEventArgs&> cb)
{
	if (!_skeletonFrameReadyCb)
		processQuery(buildQuery("SkeletonFrameReady"));
	_skeletonFrameReadyCb = cb;
}

KEventHandler<AudioDataReadyEventArgs&> KinectSensor::audioDataReadyCb(void) const
{
	return _audioDataReadyCb;
}

void KinectSensor::setAudioDataReadyCb(KEventHandler<AudioDataReadyEventArgs&> cb)
{
	if (!_audioDataReadyCb)
		processQuery(buildQuery("AudioDataReady"));
	_audioDataReadyCb = cb;
}

