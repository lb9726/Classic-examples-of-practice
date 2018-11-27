TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Factory.cpp \
    Product.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Factory.h \
    Product.h

