#include "depthImageFrame.h"

DepthImagePoint DepthImageFrame::MapFromSkeletonPoint(SkeletonPoint skeletonPoint)
{
	/* Building args */
	std::vector<std::string> args;

	args.push_back(toString<float>(skeletonPoint.getX()));
	args.push_back(toString<float>(skeletonPoint.getY()));
	args.push_back(toString<float>(skeletonPoint.getZ()));

	/* Processing the query */
	processQuery(buildQuery(__func__, args));

	/* Getting the result */
	std::vector<std::string>* res = splitString(lastMessage(), SEP);

	/* Checking the result */
	checkRet(4, res->size());

	int depth = valueOf<int>((*res)[0]);
	int playerIndex = valueOf<int>((*res)[1]);
	int x = valueOf<int>((*res)[2]);
	int y = valueOf<int>((*res)[3]);
	delete res;

	return DepthImagePoint(depth, playerIndex, x, y);
}

ColorImagePoint DepthImageFrame::MapToColorImagePoint(int depthX, int depthY, ColorImageFormat colorImageFormat)
{
	/* Building args */
	std::vector<std::string> args;

	args.push_back(toString<int>(depthX));
	args.push_back(toString<int>(depthY));
	args.push_back(toString<int>((int)colorImageFormat));

	/* Processing the query */
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

SkeletonPoint DepthImageFrame::MapToSkeletonPoint(int depthX, int depthY)
{
	/* Building args */
	std::vector<std::string> args;

	args.push_back(toString<int>(depthX));
	args.push_back(toString<int>(depthY));

	/* Processing the query */
	processQuery(buildQuery(__func__, args));

	/* Getting the result */
	std::vector<std::string>* res = splitString(lastMessage(), SEP);

	/* Checking the result */
	checkRet(2, res->size());

	int x = valueOf<float>((*res)[0]);
	int y = valueOf<float>((*res)[1]);
	int z = valueOf<float>((*res)[2]);

	delete res;

	return SkeletonPoint(x, y, z);
}
