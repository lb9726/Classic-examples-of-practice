TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    observer.cpp \
    subject.cpp

HEADERS += \
    observer.h \
    subject.h
