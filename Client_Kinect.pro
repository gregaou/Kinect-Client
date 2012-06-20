TEMPLATE = app
CONFIG += console
CONFIG -= qt
LIBS += -lws2_32 -lpthread

SOURCES += main.cpp \
    kPaquet.cpp \
    kClientPaquet.cpp \
    kServerPaquet.cpp \
    kTcpSocket.cpp \
    kVerboseTcpSocket.cpp \
    kClient.cpp

HEADERS += \
    kPaquet.h \
    kClientPaquet.h \
    kServerPaquet.h \
    kTcpSocket.h \
    byte.h \
    kVerboseTcpSocket.h \
    kClient.h

