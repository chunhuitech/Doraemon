#ifndef QSQLITEUTILS_H
#define QSQLITEUTILS_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMutex>
#include <QMap>
#include "qlogginglib.h"
class QSqliteUtils
{
public:
    QSqliteUtils();
    void setLog(QLoggingLib* pLog);
    QString getErrorInfo(int errorCode);
    bool createDatabase(const QString& connectionName);
    void removeDataBase(const QString& connectionName);
    bool open(const QString& dbName);
    bool Updata(const QString& qsSql);
    bool del(QString &table, QString &expression);
    bool dbExists(const QString& tableName);
    bool exec(const QString& strexec);
    int insert(const QString& qsSql);
    int getCount(const QString& strexec);
    bool transaction();
    bool commit();
    void close();
public:
     QSqlDatabase m_db;
private:
    QLoggingLib* m_pLog;
    QMutex  m_dbMutex;

    //QSqlQuery m_query; // 用时再定义，否则报 "Driver not loaded Driver not loaded"
    QMap<int, QString> m_errorInfoMap;
};

#endif // QSQLITEUTILS_H
