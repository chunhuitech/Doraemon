#-------------------------------------------------
#
# Project created by QtCreator 2018-03-10T10:48:13
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = QNetSo
TEMPLATE = lib

DEFINES += QNETSO_LIBRARY

SOURCES += qnetso.cpp \
    http/basehttp.cpp \
    http/classificatonapi.cpp \
    http/recordapi.cpp

HEADERS += qnetso.h\
        qnetso_global.h \
    http/basehttp.h \
    http/classificatonapi.h \
    http/recordapi.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QLoggingLib/release/ -lQLoggingLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QLoggingLib/debug/ -lQLoggingLib
else:unix: LIBS += -L$$OUT_PWD/../QLoggingLib/ -lQLoggingLib

INCLUDEPATH += $$PWD/../QLoggingLib
DEPENDPATH += $$PWD/../QLoggingLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QLoggingLib/release/libQLoggingLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QLoggingLib/debug/libQLoggingLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QLoggingLib/release/QLoggingLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QLoggingLib/debug/QLoggingLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QLoggingLib/libQLoggingLib.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QCommLib/release/ -lQCommLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QCommLib/debug/ -lQCommLib
else:unix: LIBS += -L$$OUT_PWD/../QCommLib/ -lQCommLib

INCLUDEPATH += $$PWD/../QCommLib
DEPENDPATH += $$PWD/../QCommLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QCommLib/release/libQCommLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QCommLib/debug/libQCommLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QCommLib/release/QCommLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QCommLib/debug/QCommLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QCommLib/libQCommLib.a
