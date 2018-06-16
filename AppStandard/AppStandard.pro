#-------------------------------------------------
#
# Project created by QtCreator 2018-06-14T17:07:38
# 这个模块作为标准只包含了一些常量
#-------------------------------------------------

QT       -= gui
QT       += sql

TARGET = AppStandard
TEMPLATE = lib

DEFINES += APPSTANDARD_LIBRARY

SOURCES += appstandard.cpp \
    displayvex.cpp \
    displayedge.cpp

HEADERS += appstandard.h\
        appstandard_global.h \
    displayvex.h \
    displayedge.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = ../bin

