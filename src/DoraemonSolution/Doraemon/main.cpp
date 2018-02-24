#include "mainwindow.h"
#include <QApplication>
#include "qcommlib.h"
#include "qcontrolso.h"
#include "qlogginglib.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QLoggingLib::instance()->initLogConfig(a.applicationDirPath());
    QLoggingLib::instance()->info("start up...");
    QLoggingLib::instance()->error("db test", LMV_DB);
//    qDebug("test stTest: %d", stTest.itemType);
    return a.exec();
}
