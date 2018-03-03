#ifndef QSQLITEUTILS_H
#define QSQLITEUTILS_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMutex>
#include <QMap>

class QSqliteUtils
{
public:
    QSqliteUtils();
    QString getErrorInfo(int errorCode);
    bool createDatabase(const QString& connectionName);
    void removeDataBase(const QString& connectionName);
    bool open(const QString& dbName);
    bool dbExists(const QString& tableName);
    bool exec(const QString& strexec);
    int getCount(const QString& strexec);
    bool transaction();
    bool commit();
    void close();
public:
     QSqlDatabase m_db;
private:
    QMutex  m_dbMutex;

    //QSqlQuery m_query; // 用时再定义，否则报 "Driver not loaded Driver not loaded"
    QMap<int, QString> m_errorInfoMap;
};

#endif // QSQLITEUTILS_H
