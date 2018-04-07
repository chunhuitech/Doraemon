#include "qdboperthreadentity.h"
#include "qlogginglib.h"
#include "qdatabaseso.h"
#include <QThread>
QDBOperThreadEntity::QDBOperThreadEntity()
{

}


void QDBOperThreadEntity::OnSaveClassInfo(const QVariant &mark)
{
    if(mark.canConvert<SyncRetClassificationStruct>())
    {
        SyncRetClassificationStruct sRCS = mark.value<SyncRetClassificationStruct>();
        qDebug() << sRCS.lastModTime;
        QDatabaseSo::instance().saveClassInfo(sRCS);
    }
}

void QDBOperThreadEntity::OnSaveRecordInfo(const QVariant &mark)
{
    if(mark.canConvert<SyncRetRecordStruct>())
    {
        SyncRetRecordStruct sRRS = mark.value<SyncRetRecordStruct>();
        qDebug() << sRRS.lastModTime;
        QDatabaseSo::instance().saveRecordInfo(sRRS);
    }
}

void QDBOperThreadEntity::onPrintDbThreadId()
{
    QLoggingLib::instance().info("db thread Id:" + QString::number((uint64_t)QThread::currentThreadId()), LMV_DB);
}

