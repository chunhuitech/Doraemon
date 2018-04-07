#-------------------------------------------------
#
# Project created by QtCreator 2018-02-25T17:27:38
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = QDatabaseSo
TEMPLATE = lib

DEFINES += QDATABASESO_LIBRARY

SOURCES += qdatabaseso.cpp \
    qsqliteutils.cpp \
    Tables/qclassificationtable.cpp \
    dbdefine.cpp \
    ModelData/dbtreemodeldataclassificationimpl.cpp \
    Tables/qdoraemonconfigtable.cpp \
    Tables/qrecordtable.cpp \
    ModelData/dbtreemodeldatarecordimpl.cpp \
    ModelData/dblistmodeldataclassificationimpl.cpp

HEADERS += qdatabaseso.h\
        qdatabaseso_global.h \
    qsqliteutils.h \
    Tables/qclassificationtable.h \
    dbdefine.h \
    ModelData/dbtreemodeldataclassificationimpl.h \
    Tables/qdoraemonconfigtable.h \
    Tables/qrecordtable.h \
    ModelData/dbtreemodeldatarecordimpl.h \
    ModelData/dblistmodeldataclassificationimpl.h

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

DISTFILES += \
    db.sql
