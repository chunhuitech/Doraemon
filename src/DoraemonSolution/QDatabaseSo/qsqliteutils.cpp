#include "qsqliteutils.h"
#include "qlogginglib.h"
#include "dbdefine.h"
#include <QSqlDriver>
#include <QException>
QSqliteUtils::QSqliteUtils()
{
    m_errorInfoMap[QSqlError::NoError] = "No Error";
    m_errorInfoMap[QSqlError::ConnectionError] = "Connection Error";
    m_errorInfoMap[QSqlError::StatementError] = "Statement Error";
    m_errorInfoMap[QSqlError::TransactionError] = "Transaction Error";
    m_errorInfoMap[QSqlError::UnknownError] = "Unknown Error";
}

void QSqliteUtils::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
}

QString QSqliteUtils::getErrorInfo(int errorCode)
{
    QString info;
    QMap<int, QString>::iterator it = m_errorInfoMap.find(errorCode);
    if (it != m_errorInfoMap.end())
    {
        info = it.value();
    }
    if (info.isEmpty())
    {
        info = QString("QSqliteUtils::getErrorInfo  not find error type:%1").arg(errorCode);
    }
    return info;
}

bool QSqliteUtils::createDatabase(const QString &connectionName)
{
    QMutexLocker locker(&m_dbMutex);
    QString info;
    try {
        m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    } catch(QSqlError err){
        info = QString("CSqliteUtils::createDatabase QSqlError error type:%1 error info:%2 connectionName:%3").arg(getErrorInfo(err.type())).arg(err.text()).arg(connectionName);
        m_pLog->error(info, LMV_DB);
        return false;
    }
    catch(QException err) {
        info = QString("CSqliteUtils::createDatabase QException error what:%1 connectionName:%2").arg(err.what()).arg(connectionName);
        m_pLog->error(info, LMV_DB);
        return false;
    }
    return true;
}

void QSqliteUtils::removeDataBase(const QString &connectionName)
{
    QMutexLocker locker(&m_dbMutex);
    return QSqlDatabase::removeDatabase(connectionName);
}

bool QSqliteUtils::open(const QString &dbName)
{
    QMutexLocker locker(&m_dbMutex);
    bool bOpen =false;
    QString info;
    try {
        m_db.setDatabaseName(dbName);
        bOpen = m_db.open();
    } catch(QSqlError err){
        info = QString("CSqliteUtils::open QSqlError error type:%1 error info:%2 dbName:%3").arg(getErrorInfo(err.type())).arg(err.text()).arg(dbName);
        m_pLog->error(info, LMV_DB);
        return bOpen;
    }
    catch(QException err) {
        info = QString("CSqliteUtils::open QException error what:%1 dbName:%2").arg(err.what()).arg(dbName);
        m_pLog->error(info, LMV_DB);
        return bOpen;
    }
    if (!bOpen) {
        QSqlError err;
        err = m_db.lastError();
        QString info = QString("QSqliteUtils::open error type:%1 error info:%2 ").arg(getErrorInfo(err.type())).arg(err.text());
        m_pLog->error(info, LMV_DB);
        return false;
    }
    return bOpen;
//    QString connection;
//    connection = m_db.connectionName();
}

bool QSqliteUtils::Updata(const QString &qsSql)
{
    QMutexLocker locker(&m_dbMutex);
    QSqlQuery sqlQuery(m_db);
    if (sqlQuery.exec(qsSql))
    {
        return true;
    }
    else
    {
        QSqlError err = sqlQuery.lastError();
        QString info = QString("CSqliteUtils::Updata error type:%1 error info:%2  sql:%3").arg(getErrorInfo(err.type())).arg(err.text()).arg(qsSql);
        m_pLog->error(info, LMV_DB);
        return false;
    }
}

bool QSqliteUtils::del(QString &table, QString &expression)
{
    QMutexLocker locker(&m_dbMutex);
    //DELETE FROM tablename WHERE colname = value
    QString sql = QString("delete from ") + table + QString(" where ") + expression;
    QSqlQuery sqlQuery(m_db);
    if (sqlQuery.exec(sql))
    {
        return true;
    }
    else
    {
        QSqlError err = m_db.lastError();
        QString info = QString("CSqliteUtils::del error type:%1 error info:%2 sql:%3").arg(getErrorInfo(err.type())).arg(err.text()).arg(sql);
        m_pLog->error(info, LMV_DB);
        return false;
    }
}

bool QSqliteUtils::dbExists(const QString &tableName)
{
    QMutexLocker locker(&m_dbMutex);
    QStringList tables = m_db.tables();
    if (tables.contains(tableName, Qt::CaseInsensitive)){
        return true;
    }
    return false;
}

bool QSqliteUtils::exec(const QString &strexec)
{
    QMutexLocker locker(&m_dbMutex);
    QSqlQuery query(m_db);
    bool bSuccess = query.exec(strexec);
    if (!bSuccess){
        QSqlError err = query.lastError();
        QString info = QString("QSqliteUtils::transaction exec type:%1 error info:%2 sql:%3").arg(getErrorInfo(err.type())).arg(err.text()).arg(strexec);
        m_pLog->error(info, LMV_DB);
    }
    return bSuccess;
}

int QSqliteUtils::insert(const QString &qsSql)
{
    QMutexLocker locker(&m_dbMutex);
    int rowId = NOT_FIND_RECORD_ID;
    QSqlQuery sqlQuery(m_db);

    if (sqlQuery.exec(qsSql))
    {
        if (m_db.driver()->hasFeature(QSqlDriver::LastInsertId)) {
            rowId = sqlQuery.lastInsertId().toUInt();
        }
    }
    else
    {
        QSqlError err = m_db.lastError();
        QString info = QString("CSqliteUtils::insert error type:%1 error info:%2 sql:%3 ").arg(getErrorInfo(err.type())).arg(err.text()).arg(qsSql);
        //m_pLog->error(info, LMV_DB);
        qDebug() << info;
    }
    return rowId;
}

int QSqliteUtils::getCount(const QString &strexec)
{
    QMutexLocker locker(&m_dbMutex);
    uint32_t count = NOT_FIND_RECORD_ID;
    QSqlQuery query(m_db);
    bool bSuccess = query.exec(strexec);
    if(bSuccess){
        if (m_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
            count = query.size();
        }
        else {
            if (query.last())
            {
                count = query.at() + 1;
            }
        }
    }
    else
    {
        QSqlError err = query.lastError();
        QString info = QString("QSqliteUtils::getCount exec type:%1 error info:%2 sql:%3").arg(getErrorInfo(err.type())).arg(err.text()).arg(strexec);
        m_pLog->error(info, LMV_DB);
    }
    return count;
}

bool QSqliteUtils::transaction()
{
    QMutexLocker locker(&m_dbMutex);
    bool bSuccess = m_db.transaction();
    if (!bSuccess)
    {
        QSqlError err = m_db.lastError();
        QString info = QString("QSqliteUtils::transaction error type:%1 error info:%2 ").arg(getErrorInfo(err.type())).arg(err.text());
        m_pLog->error(info, LMV_DB);
    }
    return bSuccess;
}

bool QSqliteUtils::commit()
{
    QMutexLocker locker(&m_dbMutex);
    bool bSuccess = m_db.commit();
    if (!bSuccess)
    {
        QSqlError err = m_db.lastError();
        QString info = QString("QSqliteUtils::commit error type:%1 error info:%2 ").arg(getErrorInfo(err.type())).arg(err.text());
        m_pLog->error(info, LMV_DB);
    }
    return bSuccess;
}

void QSqliteUtils::close()
{
    QMutexLocker locker(&m_dbMutex);
    return m_db.close();
}

