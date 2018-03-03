#include "mainwindow.h"
#include <QApplication>
#include "qcommlib.h"
#include "qcontrolso.h"
#include "qlogginglib.h"
#include "qdatabaseso.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QLoggingLib::instance()->initLogConfig(a.applicationDirPath());
    QLoggingLib::instance()->info("start up...");
    if( !QDatabaseSo::instance()->initDB()){
        return 0;
    }
    int row =1;
    qDebug("test: %d", QDatabaseSo::instance()->getClassificationChildRowId(2,row-1));
    qDebug() << QDatabaseSo::instance()->getClassificationRecord(2).cnName;
    return a.exec();
}
