TEMPLATE = app

QT += qml quick

CONFIG += c++14

SOURCES += main.cpp \
    detail.cpp \
    detailsloader.cpp \
    detailsmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    test.json

HEADERS += \
    detail.h \
    detailsloader.h \
    detailsmodel.h
