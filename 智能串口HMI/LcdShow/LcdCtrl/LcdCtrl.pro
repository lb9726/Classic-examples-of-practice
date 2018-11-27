QT       += core
QT       -= gui

TARGET    = LcdCtrl
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += debug_and_release

TEMPLATE  = app

SOURCES  += main.cpp \
            LcdCtrl.cpp \
            Calc.cpp

HEADERS  += LcdCtrl.h \
            Calc.h

INCLUDEPATH     += ../Common/
QMAKE_CXXFLAGS  += -Wno-write-strings
