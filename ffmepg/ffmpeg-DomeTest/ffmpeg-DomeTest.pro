#-------------------------------------------------
#
# Project created by QtCreator 2017-10-09T08:55:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ffmpeg-DomeTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

INCLUDEPATH += $$PWD/ffmpeg32/dev/include
LIBS += -L$$PWD/ffmpeg32/dev/lib/ -lavcodec \
-L$$PWD/ffmpeg32/dev/lib/ -lavdevice \
-L$$PWD/ffmpeg32/dev/lib/ -lavfilter \
-L$$PWD/ffmpeg32/dev/lib/ -lavformat \
-L$$PWD/ffmpeg32/dev/lib/ -lavutil \
-L$$PWD/ffmpeg32/dev/lib/ -lpostproc \
-L$$PWD/ffmpeg32/dev/lib/ -lswscale
