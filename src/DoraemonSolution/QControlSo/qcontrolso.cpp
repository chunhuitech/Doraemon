#include "qcontrolso.h"
#include "qdatabaseso.h"
QMutex QControlSo::m_Mutex;
QAtomicPointer<QControlSo> QControlSo::m_pInstance;
QControlSo::QControlSo()
{
    QObject::connect(&classAPI, SIGNAL(signSyncClassFinished(int, QString, const QVariant&)),
            this, SLOT(OnSignSyncClassFinished(int, QString, const QVariant&)), Qt::QueuedConnection);
    QObject::connect(&QDatabaseSo::instance(), SIGNAL(signSaveClassInfoFinished(int, int)),
            this, SLOT(OnSignSaveClassInfoFinished(int, int)), Qt::QueuedConnection);

    QObject::connect(&recordAPI, SIGNAL(signSyncRecordFinished(int, QString, const QVariant&)),
            this, SLOT(OnSignSyncRecordFinished(int, QString, const QVariant&)), Qt::QueuedConnection);
    QObject::connect(&productInfoApi, SIGNAL(signCheckVersionFinished(int, QString, const QVariant&)),
            this, SLOT(OnSignCheckVersionFinished(int, QString, const QVariant&)), Qt::QueuedConnection);
    QObject::connect(&configApi, SIGNAL(signGetDorDataVersionFinished(int, QString, const QVariant&)),
            this, SLOT(OnSignGetDorDataVersionFinished(int, QString, const QVariant&)), Qt::QueuedConnection);
    QObject::connect(&manager, SIGNAL(finished()), this, SLOT(downFinished()), Qt::QueuedConnection);
    QObject::connect(&QDatabaseSo::instance(), SIGNAL(signSaveRecordInfoFinished(int, int)),
            this, SLOT(OnSignSaveRecordInfoFinished(int, int)), Qt::QueuedConnection);
    QObject::connect(&QDatabaseSo::instance(), SIGNAL(signImportDBDataFinished(int, int)),
            this, SLOT(OnSignImportDBDataFinished(int, int)), Qt::QueuedConnection);


}

void QControlSo::getDorDataVersion()
{
    configApi.getDorDataVersion();
}

void QControlSo::downDorDataFile(QString downAddr)
{
    manager.append(QUrl(downAddr));
}

void QControlSo::pushActiveInfo(ProductActivityStruct pas)
{
    productActivityApi.pushActivityInfo(pas);
}

void QControlSo::checkVersion(VersionInfoStruct vis)
{
    productInfoApi.checkVersion(vis);
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

void QControlSo::importRecords()
{
    dbOper.importRecords();
}

void QControlSo::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
    recordAPI.setLog(m_pLog);
    classAPI.setLog(m_pLog);
    dbOper.setLog(m_pLog);
    productInfoApi.setLog(m_pLog);
    productActivityApi.setLog(m_pLog);
    configApi.setLog(m_pLog);
}

void QControlSo::exitHandler()
{
         //classNetOper.exitHandler();
    dbOper.exitHandler();
}

void QControlSo::OnSignSyncClassFinished(int code, QString msg, const QVariant &mark)
{
    Q_UNUSED(code);
    Q_UNUSED(msg);
    if(mark.canConvert<SyncRetClassificationStruct>())
    {
        SyncRetClassificationStruct sRCS = mark.value<SyncRetClassificationStruct>();
//         m_pLog->info("QControlSo::OnSignSyncClassFinished");
        dbOper.saveClassInfo(sRCS);
    }
}

void QControlSo::OnSignSaveClassInfoFinished(int code, int count)
{
    emit signSaveClassInfoFinished2UI(code, count);
}

void QControlSo::OnSignSaveRecordInfoFinished(int code, int count)
{
    emit signSaveRecordInfoFinished2UI(code, count);
}

void QControlSo::OnSignImportDBDataFinished(int code, int count)
{
    emit signImportDBDataFinished2UI(code, count);
}

void QControlSo::downFinished()
{
    emit signDownDorFileFinished2UI(EC_SUCCESS, 1);
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

void QControlSo::OnSignCheckVersionFinished(int code, QString msg, const QVariant &mark)
{
    emit signCheckVersionFinished2UI(code, msg, mark);
}

void QControlSo::OnSignGetDorDataVersionFinished(int code, QString msg, const QVariant &mark)
{
    emit signGetDorDataVersionFinished2UI(code, msg, mark);
}
