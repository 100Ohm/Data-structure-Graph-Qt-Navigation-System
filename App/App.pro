#-------------------------------------------------
#
# Project created by QtCreator 2018-06-14T16:00:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RC_ICONS += mainico.ico \

DESTDIR = ../bin

win32{
LIBS += ../bin/AppStandard.dll \
    ../bin/NormalDisPlay.dll \
    ../bin/FindRoadDisplay.dll
}
