#-------------------------------------------------
#
# Project created by QtCreator 2018-02-24T00:41:17
#
#-------------------------------------------------

QT       -= gui

TARGET = QControlSo
TEMPLATE = lib

DEFINES += QCONTROLSO_LIBRARY

SOURCES += qcontrolso.cpp

HEADERS += qcontrolso.h\
        qcontrolso_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
