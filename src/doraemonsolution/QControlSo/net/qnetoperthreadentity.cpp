#include <QThread>
#include "qnetoperthreadentity.h"
#include "qlogginglib.h"
QNetOperThreadEntity::QNetOperThreadEntity(QObject *parent) : QObject(parent)
{

}


void QNetOperThreadEntity::OnSignSyncClassStart(int lastTime)
{
    qDebug() << "QNetOperThreadEntity thread Id:" << QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
    //The inferior stopped because it received a signal from the Operating System.
    //QLoggingLib::instance().info("QNetOperThreadEntity thread Id:" + QString::number((uint64_t)QThread::currentThreadId()), LMV_NET);
//    QLoggingLib::instance().info("QNetOperThreadEntity thread: + " + QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')));
    classAPI.syncData(lastTime);
}

void QNetOperThreadEntity::onPrintNetThreadId()
{
    QLoggingLib::instance().info("net thread Id:" + QString::number((uint64_t)QThread::currentThreadId()), LMV_NET);
}

