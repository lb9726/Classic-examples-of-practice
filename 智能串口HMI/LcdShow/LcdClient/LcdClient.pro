QT       += core
QT       += network
QT       -= gui

TARGET    = LcdClient
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += debug_and_release

TEMPLATE  = app

SOURCES  += main.cpp \
            LcdClient.cpp

HEADERS  += LcdClient.h

INCLUDEPATH     += ../Common/
QMAKE_CXXFLAGS  += -Wno-write-strings
