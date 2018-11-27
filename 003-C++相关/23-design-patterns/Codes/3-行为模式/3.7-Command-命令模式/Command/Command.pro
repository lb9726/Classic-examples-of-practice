TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    reciever.cpp \
    command.cpp \
    invoker.cpp

HEADERS += \
    reciever.h \
    command.h \
    invoker.h
