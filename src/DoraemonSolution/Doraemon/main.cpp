#include "mainwindow.h"
#include <QApplication>
#include "qcommlib.h"
#include "qcontrolso.h"
#include "qlogginglib.h"
#include "qdatabaseso.h"
#include "qnetso.h"
#include <QDebug>
#include "qcontrolso.h"
#include <QSharedMemory>
int main(int argc, char *argv[])
{
    QSharedMemory shared("doraemon");
    if (shared.attach())
    {
            return 0;
    }
    shared.create(1);
    QApplication a(argc, argv);
    QLoggingLib::instance().initLogConfig(a.applicationDirPath());
    QLoggingLib::instance().info("main thread Id:" + QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')));
    QControlSo::instance().setLog(&QLoggingLib::instance());
    QNetSo::instance().setLog(&QLoggingLib::instance());
    if( !QDatabaseSo::instance().initDB(&QLoggingLib::instance())){
        return 0;
    }
    MainWindow w;
    w.show();

//    int row =1;
//    qDebug("test: %d", QDatabaseSo::instance().getClassificationChildRowId(2,row-1));
//    qDebug() << QDatabaseSo::instance().getClassificationRecord(2).cnName;
    return a.exec();
}
