#-------------------------------------------------
#
# Project created by QtCreator 2018-06-14T16:19:26
# 平时的显示模块
#-------------------------------------------------

QT       -= gui
QT       += sql

TARGET = NormalDisPlay
TEMPLATE = lib

DEFINES += NORMALDISPLAY_LIBRARY

SOURCES += normaldisplay.cpp \
    normalmodel.cpp \
    normalcontroller.cpp \
    n_controller.cpp \
    n_model.cpp

HEADERS += normaldisplay.h\
        normaldisplay_global.h \
    normalmodel.h \
    normalcontroller.h \
    n_controller.h \
    n_model.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = ../bin

win32{
LIBS += ../bin/AppStandard.dll
}
