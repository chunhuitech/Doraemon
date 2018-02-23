#-------------------------------------------------
#
# Project created by QtCreator 2018-02-23T23:34:59
#
#-------------------------------------------------

QT       -= gui

TARGET = QCommLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qcommlib.cpp

HEADERS += qcommlib.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
