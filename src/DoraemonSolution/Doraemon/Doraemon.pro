#-------------------------------------------------
#
# Project created by QtCreator 2018-02-23T23:12:58
#
#-------------------------------------------------
QT += axcontainer
QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Doraemon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Model/classificationtreemodel.cpp \
    Model/recordtreemodel.cpp \
    Model/classificationlistmodel.cpp

HEADERS  += mainwindow.h \
    Model/classificationtreemodel.h \
    Model/recordtreemodel.h \
    Model/classificationlistmodel.h

FORMS    += mainwindow.ui

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QControlSo/release/ -lQControlSo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QControlSo/debug/ -lQControlSo
else:unix: LIBS += -L$$OUT_PWD/../QControlSo/ -lQControlSo

INCLUDEPATH += $$PWD/../QControlSo
DEPENDPATH += $$PWD/../QControlSo

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QDatabaseSo/release/ -lQDatabaseSo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QDatabaseSo/debug/ -lQDatabaseSo
else:unix: LIBS += -L$$OUT_PWD/../QDatabaseSo/ -lQDatabaseSo

INCLUDEPATH += $$PWD/../QDatabaseSo
DEPENDPATH += $$PWD/../QDatabaseSo

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QNetSo/release/ -lQNetSo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QNetSo/debug/ -lQNetSo
else:unix: LIBS += -L$$OUT_PWD/../QNetSo/ -lQNetSo

INCLUDEPATH += $$PWD/../QNetSo
DEPENDPATH += $$PWD/../QNetSo
