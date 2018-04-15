#include "qdboperthreadentity.h"
#include "qdatabaseso.h"
#include <QThread>
QDBOperThreadEntity::QDBOperThreadEntity()
{
    m_pLog = NULL;
}

void QDBOperThreadEntity::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
}


void QDBOperThreadEntity::OnSaveClassInfo(const QVariant &mark)
{
    if(mark.canConvert<SyncRetClassificationStruct>())
    {
        SyncRetClassificationStruct sRCS = mark.value<SyncRetClassificationStruct>();
//        qDebug() << sRCS.lastModTime;
        QDatabaseSo::instance().saveClassInfo(sRCS);
    }
}

void QDBOperThreadEntity::OnSaveRecordInfo(const QVariant &mark)
{
    if(mark.canConvert<SyncRetRecordStruct>())
    {
        SyncRetRecordStruct sRRS = mark.value<SyncRetRecordStruct>();
//        qDebug() << sRRS.lastModTime;
        QDatabaseSo::instance().saveRecordInfo(sRRS);
    }
}

void QDBOperThreadEntity::OnImportRecords()
{
    QDatabaseSo::instance().importRecords();
}

void QDBOperThreadEntity::onPrintDbThreadId()
{
    if(m_pLog)
        m_pLog->info("QDBOper thread Id:" + QStringLiteral("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0')), LMV_DB);
}

