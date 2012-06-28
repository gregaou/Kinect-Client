TEMPLATE = app
CONFIG += console
CONFIG -= qt
LIBS += -lpthread

SOURCES += main.cpp \
    kAction.cpp \
    KObjects/kObject.cpp \
    KObjects/kinectSensor.cpp \
    KObjects/kinectSensorCollection.cpp \
    network/kVerboseTcpSocket.cpp \
    network/kTcpSocket.cpp \
    network/kServerPaquet.cpp \
    network/kPaquet.cpp \
    network/kClientPaquet.cpp \
    network/kClient.cpp

HEADERS += \
    kAction.h \
    kMessageAction.h \
    KObjects/kObject.h \
    KObjects/kinectSensor.h \
    KObjects/kinectSensorCollection.h \
    KObjects/kObjects.h \
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
    kConnectionException.h \
    kQueryErrorException.h \
    enums/colorImageFormat.h \
    KObjects/colorImagePoint.h \
    KObjects/skeletonPoint.h \
    KObjects/depthImagePoint.h

