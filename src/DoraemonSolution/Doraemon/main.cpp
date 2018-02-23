#include "mainwindow.h"
#include <QApplication>
#include "qcommlib.h"
#include "qcontrolso.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    stTest stTest;
    stTest.itemType = 233;
    QControlSo controlSo;
    qDebug("test stTest: %d", stTest.itemType);
    return a.exec();
}
