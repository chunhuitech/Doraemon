#include "qdboper.h"
#include <QVariant>
QDBOper::QDBOper()
{
    connect(&m_dbThread, SIGNAL(finished()), this, SLOT(onThreadFinished()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(signalPrintDbThreadId()),
            &m_threadDbEntity, SLOT(onPrintDbThreadId()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(signSaveClassInfo(const QVariant&)),
            &m_threadDbEntity, SLOT(OnSaveClassInfo(const QVariant&)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(signSaveRecordInfo(const QVariant&)),
            &m_threadDbEntity, SLOT(OnSaveRecordInfo(const QVariant&)), Qt::QueuedConnection);
    m_threadDbEntity.moveToThread(&m_dbThread);
    m_dbThread.start();
}

void QDBOper::saveClassInfo(const SyncRetClassificationStruct srcs)
{
    QVariant dataVar;
    dataVar.setValue(srcs);
    emit signSaveClassInfo(dataVar);
}

void QDBOper::saveRecordInfo(const SyncRetRecordStruct srrs)
{
    QVariant dataVar;
    dataVar.setValue(srrs);
    emit signSaveRecordInfo(dataVar);
}

void QDBOper::onThreadFinished()
{
    qDebug() <<"on db ThreadFinished";
}

