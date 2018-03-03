#-------------------------------------------------
#
# Project created by QtCreator 2018-02-23T23:34:59
#
#-------------------------------------------------

QT       -= gui

TARGET = QCommLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qcommlib.cpp \
    ModelData/itreemodeldata.cpp \
    ModelData/treemodeldataitemclassification.cpp

HEADERS += qcommlib.h \
    ModelData/itreemodeldata.h \
    ModelData/itreemodeldataitem.h \
    ModelData/treemodeldataitemclassification.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    readme_tech.txt
