#include "kinectSensor.h"
#include "../network/kPaquet.h"

KinectSensor::KinectSensor(int id) :
	KObject("KinectSensor", id),
	_colorFrameReadyCb(0),
	_uniqueKinectId("")
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

std::string KinectSensor::getUniqueKinectId(void)
{
	if (_uniqueKinectId == "")
		_uniqueKinectId = getQuery<std::string>(__func__);
	return _uniqueKinectId;
}

void KinectSensor::MapDepthFrameToColorFrame
(
	DepthImageFormat depthImageFormat,
	std::vector<short> depthPixelData,
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

//	std::vector<std::string>* res = splitString(lastMessage(), SEP);

	/* Checking the result */
//	std::cout << lastMessage() << std::endl;
//	std::cout << lastMessage().size() << std::endl;
//	std::cout << "wait for " << (depthPixelData.size() * 2) << " args" << std::endl;
//	std::cout << res->size() << std::endl;
//	for (unsigned int i=0; i<res->size(); i++)
//		std::cout << (*res)[i] << " ";
//	checkRet(depthPixelData.size() * 2, res->size());

//	for (unsigned int i=0; i<res->size(); i+=2)
//	{
//		int x = valueOf<int>((*res)[i]);
//		int y = valueOf<int>((*res)[i+1]);
//		std::cout << "(" << x << ", " << y << ") ";
//		colorCoordinates->push_back(ColorImagePoint(x, y, _sensorId));
//	}

	byte* data = lastData();

	for (unsigned int i=0; i<2/*DepthPixelData.size()*/; i++)
	{
		int x, y;
		x = ntohl(KPaquet::getUint32(data, 4*i*2));
		y = ntohl(KPaquet::getUint32(data, 4*(i*2+1)));
		std::cout << "(" << x << ", " << y << ") ";
		colorCoordinates->push_back(ColorImagePoint(x, y, _sensorId));
	}

	std::cout << std::endl;

//	delete res;
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

	return ColorImagePoint(x, y, _sensorId);
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

	return SkeletonPoint(x, y, z, _sensorId);
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

	return ColorImagePoint(x, y, _sensorId);
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

	return DepthImagePoint(depth, playerIndex, x, y, _sensorId);
}

kEventHandler<ColorImageFrameReadyEventArgs&> KinectSensor::colorFrameReadyCb() const
{
	return _colorFrameReadyCb;
}

void KinectSensor::setColorFrameReadyCb(kEventHandler<ColorImageFrameReadyEventArgs&> cb)
{
	processQuery(buildQuery("ColorFrameReady"));
	_colorFrameReadyCb = cb;
}
