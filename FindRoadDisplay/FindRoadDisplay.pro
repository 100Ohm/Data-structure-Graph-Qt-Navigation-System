#-------------------------------------------------
#
# Project created by QtCreator 2018-06-14T21:19:30
#
#-------------------------------------------------

QT       -= gui

TARGET = FindRoadDisplay
TEMPLATE = lib

DEFINES += FINDROADDISPLAY_LIBRARY

SOURCES += findroaddisplay.cpp

HEADERS += findroaddisplay.h\
        findroaddisplay_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
