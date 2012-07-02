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
    kActions/kAction.cpp \
    kObjects/kObject.cpp \
    kObjects/kinectSensorCollection.cpp \
    kObjects/kinectSensor.cpp

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
    kActions/kActions.h \
    kActions/kMessageAction.h \
    kActions/kKinectSensorCollectionStatusChangedAction.h \
    kActions/kAction.h \
    kExceptions.h/kQueryErrorException.h \
    kExceptions/kQueryErrorException.h \
    kExceptions/kConnectionException.h \
    kObjects/skeletonPoint.h \
    kObjects/kObjects.h \
    kObjects/kObject.h \
    kObjects/kinectSensorCollection.h \
    kObjects/kinectSensor.h \
    kObjects/kEventHander.h \
    kObjects/depthImagePoint.h \
    kObjects/colorImagePoint.h

