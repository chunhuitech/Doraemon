#include "qdoraemonconfigtable.h"
#include <QSqlRecord>
QDoraemonConfigTable::QDoraemonConfigTable()
{
    m_pSqlUtil = NULL;
}

void QDoraemonConfigTable::setSqliteUtil(QSqliteUtils *pSqlUtil)
{
    m_pSqlUtil = pSqlUtil;
}

DoraemonConfigTable QDoraemonConfigTable::getRecord(const QString &query_str)
{
//    QLoggingLib::instance().info("dd", LMV_DB);
    DoraemonConfigTable dct;
    dct.id = NOT_FIND_RECORD_ID;
    QSqlQuery sqlQuery(m_pSqlUtil->m_db);
    bool bSuccess = sqlQuery.exec(query_str);
    if (bSuccess)
    {
        int idIndex = sqlQuery.record().indexOf("id");
        int keyNameIndex = sqlQuery.record().indexOf("keyName");
        int keyValueIndex = sqlQuery.record().indexOf("keyValue");
        while (sqlQuery.next())
        {
            dct.id = sqlQuery.value(idIndex).toUInt();
            dct.keyName = sqlQuery.value(keyNameIndex).toString();
            dct.keyValue = sqlQuery.value(keyValueIndex).toString();
            break;
        }
    }
    else
    {
        QSqlError err = m_pSqlUtil->m_db.lastError();
        QString info = QString("QDoraemonConfigTable::getRecord exec type:%1 error info:%2 sql:%3").arg(m_pSqlUtil->getErrorInfo(err.type())).arg(err.text()).arg(query_str);
        QLoggingLib::instance().error(info, LMV_DB);
    }
    return dct;
}

qlonglong QDoraemonConfigTable::getClassSyncTime()
{
    QString query_str = QString("Select id, keyName, keyValue From doraemon_config where keyname='classSyncTime'");
    DoraemonConfigTable dct = getRecord(query_str);
    if(dct.id == NOT_FIND_RECORD_ID) {
        return NOT_FIND_RECORD_ID;
    }
    return dct.keyValue.toLongLong();
}

qlonglong QDoraemonConfigTable::getRecordSyncTime()
{
    QString query_str = QString("Select id, keyName, keyValue From doraemon_config where keyname='recordSyncTime'");
    DoraemonConfigTable dct = getRecord(query_str);
    if(dct.id == NOT_FIND_RECORD_ID) {
        return NOT_FIND_RECORD_ID;
    }
    return dct.keyValue.toLongLong();
}

QString QDoraemonConfigTable::getResourceServer()
{
    QString query_str = QString("Select id, keyName, keyValue From doraemon_config where keyname='resourceServer'");
    DoraemonConfigTable dct = getRecord(query_str);
    if(dct.id == NOT_FIND_RECORD_ID) {
        return "";
    }
    return QString::fromStdWString(dct.keyValue.toStdWString());
}

bool QDoraemonConfigTable::updateClassSyncTime(qlonglong lastModTime)
{
    QString sql = QString("update doraemon_config set keyValue = '%1' where keyname = 'classSyncTime'").arg(lastModTime);
    return m_pSqlUtil->Updata(sql);
}

bool QDoraemonConfigTable::updateRecordSyncTime(qlonglong lastModTime)
{
    QString sql = QString("update doraemon_config set keyValue = '%1' where keyname = 'recordSyncTime'").arg(lastModTime);
    return m_pSqlUtil->Updata(sql);
}

