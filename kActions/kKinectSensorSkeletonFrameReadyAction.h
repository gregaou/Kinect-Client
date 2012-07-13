#ifndef KKINECTSENSORSKELETONFRAMEREADY_H
#define KKINECTSENSORSKELETONFRAMEREADY_H

#include <list>
#include "../enums/enums.h"
#include "../network/kServerPaquet.h"
#include "../kObjects/kObjects.h"
#include "kAction.h"

class KKinectSensorSkeletonFrameReadyAction: public KAction
{
	public:
		KKinectSensorSkeletonFrameReadyAction(KServerPaquet* paquet, const std::list<KinectSensor*>& sensors) :
			_paquet(paquet),
			_sensors(sensors)
		{}

		virtual void exec(void)
		{
			int start = 0,id, frameNumber, skeletonArrayLength, timestamp;
			float floorClipPlane[4];
			SkeletonTrackingMode trackingMode;
			Skeleton* skeletonData;

			/* Size of the paquet = 25 + <skeletonsSize> bytes */

			/*
			 *	The first byte contains :
			 *		- 1 bit for the tracking mode
			 *		- 3 bits for the sensor id
			 *		- 4 bits for the length of the skeleton array
			 */
			byte firstByte = (_paquet->data())[start++];
			trackingMode = (SkeletonTrackingMode)(firstByte >> 7);
			id = (firstByte << 1) >> 5;
			skeletonArrayLength = firstByte & 0xf;

			frameNumber = KPaquet::getUint32(_paquet->data(), (start+=4));
			timestamp =KPaquet::getUint32(_paquet->data(), (start+=4));
			for (int i=0; i<4; i++)
				floorClipPlane[i] = (float)KPaquet::getUint32(_paquet->data(), (start+=4));

			/* Building the skeletons (25 + <jointsSize> bytes/skeleton) */
			skeletonData = new Skeleton[skeletonArrayLength];
			for (int i=0; i<skeletonArrayLength; i++)
			{
				FrameEdges clippedEdges = KPaquet::getUint32(_paquet->data(), (start+=4));
				int jointsLength = KPaquet::getUint32(_paquet->data(), (start+=4));
				std::vector<Joint> joints;

				/* Building the joints (13 bytes/joint) */
				for (int j=0; j<jointsLength; j++)
				{
					/*
					 *	The first byte contains :
					 *		- 2 bits for the tracking state
					 *		- 6 bits for the joint type (0x3f = 00111111(2))
					 */
					byte b = (_paquet->data())[start++];
					JointType jointType = (JointType)(b & 0x3f);
					JointTrackingState trackingState = (JointTrackingState)(b >> 6);

					float x = (float)KPaquet::getUint32(_paquet->data(), (start+=4));
					float y = (float)KPaquet::getUint32(_paquet->data(), (start+=4));
					float z = (float)KPaquet::getUint32(_paquet->data(), (start+=4));

					joints.push_back(Joint(jointType, SkeletonPoint(x, y, z), trackingState));
				}

				float x = (float)KPaquet::getUint32(_paquet->data(), (start+=4));
				float y = (float)KPaquet::getUint32(_paquet->data(), (start+=4));
				float z = (float)KPaquet::getUint32(_paquet->data(), (start+=4));

				int trackingId = KPaquet::getUint32(_paquet->data(), (start+=4));
				SkeletonTrackingState trackingState = (SkeletonTrackingState)((_paquet->data())[start++]);

				skeletonData[i] = Skeleton(clippedEdges, joints, SkeletonPoint(x, y, z), trackingId, trackingState);
			}

			std::list<KinectSensor*>::const_iterator it;
			for (it = _sensors.begin(); it != _sensors.end(); it++)
			{
				KinectSensor* sensor = *it;
				if (sensor->sensorId() == id)
				{
					kEventHandler<SkeletonFrameReadyEventArgs&> handler = sensor->skeletonFrameReadyCb();
					SkeletonFrameReadyEventArgs args(floorClipPlane, frameNumber, skeletonArrayLength, timestamp, trackingMode, skeletonData);
					handler(sensor, args);
				}
			}

			delete skeletonData;
		}

	protected:
		KServerPaquet* _paquet;
		const std::list<KinectSensor*>& _sensors;
};

#endif
