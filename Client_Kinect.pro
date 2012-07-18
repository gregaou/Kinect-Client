TEMPLATE = app
CONFIG += console
CONFIG -= qt
LIBS += -lpthread

SOURCES += main.cpp \
    network/kVerboseTcpSocket.cpp \
    network/kTcpSocket.cpp \
    network/kServerPaquet.cpp \
    network/kPaquet.cpp \
    network/kClientPaquet.cpp \
    network/kClient.cpp \
    enums/colorImageFormat.cpp \
    enums/depthImageFormat.cpp \
    kActions/kAction.cpp \
    kObjects/kObject.cpp \
    kObjects/kinectSensor.cpp \
    kObjects/depthImageFrame.cpp \
    other/skeletonFrameReadyEventArgs.cpp \
    other/kinectSensorCollection.cpp \
    other/depthImageFrameReadyEventArgs.cpp \
    other/colorImageFrameReadyEventArgs.cpp \
    other/colorImageFrame.cpp \
    wave.cpp

HEADERS += \
    network/kVerboseTcpSocket.h \
    network/kTcpSocket.h \
    network/kServerPaquet.h \
    network/kServerListener.h \
    network/kPaquet.h \
    network/kClientPaquet.h \
    network/kClient.h \
    network/codes.h \
    network/byte.h \
    network/network.h \
    enums/kinectStatus.h \
    enums/depthImageFormat.h \
    enums/enums.h \
    enums/skeletonTrackingState.h \
    enums/jointTrackingState.h \
    enums/colorImageFormat.h \
    enums/skeletonTrackingMode.h \
    enums/jointType.h \
    enums/frameEdges.h \
    enums/beamAngleMode.h \
    enums/echoCancellationMode.h \
    kActions/kActions.h \
    kActions/kAction.h \
    kActions/kMessageAction.h \
    kActions/kKinectSensorCollectionStatusChangedAction.h \
    kActions/kKinectSensorDepthFrameReadyAction.h \
    kActions/kKinectSensorSkeletonFrameReadyAction.h \
    kActions/kKinectAudioSourceBeamAngleChangedAction.h \
    kActions/kKinectAudioSourceSoundSourceAngleChangedAction.h \
    kExceptions/kQueryErrorException.h \
    kExceptions/kConnectionException.h \
    kObjects/kObjects.h \
    kObjects/kObject.h \
    kObjects/kinectAudioSource.h \
    kObjects/kinectSensor.h \
    kObjects/depthImageFrame.h \
    other/vector4.h \
    other/soundSourceAngleChangedEventArgs.h \
    other/skeletonPoint.h \
    other/skeletonFrameReadyEventArgs.h \
    other/skeletonFrame.h \
    other/skeleton.h \
    other/matrix4.h \
    other/kObjects.h \
    other/kinectSensorCollection.h \
    other/kEventHandler.h \
    other/joint.h \
    other/imageFrame.h \
    other/depthImagePoint.h \
    other/depthImageFrameReadyEventArgs.h \
    other/colorImagePoint.h \
    other/colorImageFrameReadyEventArgs.h \
    other/colorImageframe.h \
    other/beamAngleChangedEventArgs.h \
    other/audioDataReadyEventArgs.h \
    other/other.h \
    other/audioData.h \
    kActions/kKinectSensorAudioDataReadyAction.h \
    wave.h \
    kObjects/colorImageStream.h \
    kObjects/depthImageStream.h \
    enums/depthRange.h \
    kObjects/skeletonStream.h \
    other/transformSmoothParameters.h \
    other/boneRotation.h \
    other/boneOrientation.h \
    other/interface.h \
    other/serializable.h

