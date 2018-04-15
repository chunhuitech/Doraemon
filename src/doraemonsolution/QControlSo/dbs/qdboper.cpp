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
    QObject::connect(this, SIGNAL(signImportRecords()),
            &m_threadDbEntity, SLOT(OnImportRecords()), Qt::QueuedConnection);


    m_threadDbEntity.moveToThread(&m_dbThread);
    emit signalPrintDbThreadId();
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

void QDBOper::importRecords()
{
    emit signImportRecords();
}

void QDBOper::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
    m_threadDbEntity.setLog(pLog);
}

void QDBOper::exitHandler()
{
    m_dbThread.quit();
    m_dbThread.wait();
}

void QDBOper::onThreadFinished()
{
    if(m_pLog)
        m_pLog->info("on QDBOper ThreadFinished");
}

