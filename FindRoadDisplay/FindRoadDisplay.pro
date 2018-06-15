#-------------------------------------------------
#
# Project created by QtCreator 2018-06-14T21:19:30
#
#-------------------------------------------------

QT       -= gui
QT       += sql

TARGET = FindRoadDisplay
TEMPLATE = lib

DEFINES += FINDROADDISPLAY_LIBRARY

SOURCES += findroaddisplay.cpp \
    findroadcontroller.cpp \
    findroadmodel.cpp \
    f_controller.cpp \
    f_model.cpp \
    graph.cpp \
    f_edge.cpp

HEADERS += findroaddisplay.h\
        findroaddisplay_global.h \
    findroadcontroller.h \
    findroadmodel.h \
    f_controller.h \
    f_model.h \
    graph.h \
    f_edge.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = ../bin

win32{
LIBS += ../bin/AppStandard.dll
}
