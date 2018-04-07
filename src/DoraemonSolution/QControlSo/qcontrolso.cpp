#include "qcontrolso.h"
#include "qdatabaseso.h"
QMutex QControlSo::m_Mutex;
QAtomicPointer<QControlSo> QControlSo::m_pInstance;
QControlSo::QControlSo()
{
    QObject::connect(&classAPI, SIGNAL(signSyncClassFinished(int, QString, const QVariant&)),
            this, SLOT(OnSignSyncClassFinished(int, QString, const QVariant&)), Qt::QueuedConnection);
    QObject::connect(&QDatabaseSo::instance(), SIGNAL(signSaveClassInfoFinished(int)),
            this, SLOT(OnSignSaveClassInfoFinished(int)), Qt::QueuedConnection);

    QObject::connect(&recordAPI, SIGNAL(signSyncRecordFinished(int, QString, const QVariant&)),
            this, SLOT(OnSignSyncRecordFinished(int, QString, const QVariant&)), Qt::QueuedConnection);
    QObject::connect(&QDatabaseSo::instance(), SIGNAL(signSaveRecordInfoFinished(int)),
            this, SLOT(OnSignSaveRecordInfoFinished(int)), Qt::QueuedConnection);
}

void QControlSo::syncClassification()
{
//    classNetOper.syncNetClass(1);
    qlonglong syncTime = QDatabaseSo::instance().getClassSyncTimeConfig();
    classAPI.syncData(syncTime);
}

void QControlSo::syncRecord()
{
    qlonglong syncTime = QDatabaseSo::instance().getRecordSyncTimeConfig();
    recordAPI.syncData(syncTime);
}

void QControlSo::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
    recordAPI.setLog(m_pLog);

}

void QControlSo::exitHandler()
{
    //     classNetOper.exitHandler();
}

void QControlSo::OnSignSyncClassFinished(int code, QString msg, const QVariant &mark)
{
    Q_UNUSED(code);
    Q_UNUSED(msg);
    if(mark.canConvert<SyncRetClassificationStruct>())
    {
        SyncRetClassificationStruct sRCS = mark.value<SyncRetClassificationStruct>();
         m_pLog->info("QControlSo::OnSignSyncClassFinished");
        dbOper.saveClassInfo(sRCS);
    }
}

void QControlSo::OnSignSaveClassInfoFinished(int code)
{
    emit signSaveClassInfoFinished2UI(code);
}

void QControlSo::OnSignSaveRecordInfoFinished(int code)
{
    emit signSaveRecordInfoFinished2UI(code);
}

void QControlSo::OnSignSyncRecordFinished(int code, QString msg, const QVariant &mark)
{
    Q_UNUSED(code);
    Q_UNUSED(msg);
    if(mark.canConvert<SyncRetRecordStruct>())
    {
        SyncRetRecordStruct sRRS = mark.value<SyncRetRecordStruct>();
//         m_pLog->info("QControlSo::OnSignSyncRecordFinished");
        dbOper.saveRecordInfo(sRRS);
    }
}
