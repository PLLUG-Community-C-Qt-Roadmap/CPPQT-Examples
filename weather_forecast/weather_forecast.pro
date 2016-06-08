#-------------------------------------------------
#
# Project created by QtCreator 2015-06-22T23:25:58
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = weather_forecast
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS += -std=gnu++11

TEMPLATE = app


SOURCES += main.cpp \
    weatherforecastrequest.cpp \
    weatherdata.cpp

HEADERS += \
    weatherforecastrequest.h \
    weatherdata.h
