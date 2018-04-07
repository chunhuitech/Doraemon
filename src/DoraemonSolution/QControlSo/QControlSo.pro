#-------------------------------------------------
#
# Project created by QtCreator 2018-02-24T00:41:17
#
#-------------------------------------------------
QT       += network sql
QT       -= gui

TARGET = QControlSo
TEMPLATE = lib

DEFINES += QCONTROLSO_LIBRARY

SOURCES += qcontrolso.cpp \
    net/classificationnetoper.cpp \
    net/qnetoperthreadentity.cpp \
    dbs/qdboper.cpp \
    dbs/qdboperthreadentity.cpp

HEADERS += qcontrolso.h\
        qcontrolso_global.h \
    net/classificationnetoper.h \
    net/qnetoperthreadentity.h \
    dbs/qdboper.h \
    dbs/qdboperthreadentity.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QNetSo/release/ -lQNetSo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QNetSo/debug/ -lQNetSo
else:unix: LIBS += -L$$OUT_PWD/../QNetSo/ -lQNetSo

INCLUDEPATH += $$PWD/../QNetSo
DEPENDPATH += $$PWD/../QNetSo

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QDatabaseSo/release/ -lQDatabaseSo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QDatabaseSo/debug/ -lQDatabaseSo
else:unix: LIBS += -L$$OUT_PWD/../QDatabaseSo/ -lQDatabaseSo

INCLUDEPATH += $$PWD/../QDatabaseSo
DEPENDPATH += $$PWD/../QDatabaseSo
