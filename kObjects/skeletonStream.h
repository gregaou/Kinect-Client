#ifndef SKELETONSTREAM_H
#define SKELETONSTREAM_H

#include "kObject.h"
#include "../enums/skeletonTrackingMode.h"
#include "../other/transformSmoothParameters.h"

class SkeletonStream : public KObject
{
	public:
		SkeletonStream(int id = -1) : KObject("SkeletonStream", id)
		{}

		/* Properties */
		bool getAppChoosesSkeletons(void) const								{ return (bool)getQuery<int>(__func__); }
		void setAppChoosesSkeletons(bool appChoosesSkeletons)				{ setQuery<int>(__func__, (int)appChoosesSkeletons); }
		bool getEnableTrackingInNearRange(void) const						{ return (bool)getQuery<int>(__func__); }
		void setEnableTrackingInNearRange(bool enableTrackingInNearRange)	{ setQuery<int>(__func__, (int)enableTrackingInNearRange); }
		int getFrameSkeletonArrayLength(void) const							{ return getQuery<int>(__func__); }
		bool isEnabled(void) const											{ return (bool)getQuery<int>(__func__); }
		bool IsSmoothingEnabled(void) const									{ return (bool)getQuery<int>(__func__); }
		TransformSmoothParameters getSmoothParameters(void) const
		{
			/* Processign the query */
			processQuery(buildQuery(__func__));

			/* Getting the result */
			std::vector<std::string>* res = splitString(lastMessage(), SEP);

			/* Checking the result */
			checkRet(5, res->size());

			/* Building the resulting TransformSmoothParameters */
			float correction = valueOf<float>((*res)[0]);
			float jitterRadius = valueOf<float>((*res)[1]);
			float maxDeviationRadius = valueOf<float>((*res)[2]);
			float prediction = valueOf<float>((*res)[3]);
			float smoothing = valueOf<float>((*res)[4]);

			delete res;

			return TransformSmoothParameters(correction, jitterRadius, maxDeviationRadius, prediction, smoothing);
		}

		SkeletonTrackingMode getTrackingMode(void) const					{ return (SkeletonTrackingMode)getQuery<int>(__func__);	}
		void setTrackingMode(SkeletonTrackingMode trackingMode)(void) const	{ setQuery<int>(__func__, (int)trackingMode); }

};

#endif
