#include <QDir>
#include <QtWidgets/QApplication>
#include "qdatabaseso.h"
#include "qlogginglib.h"

QMutex QDatabaseSo::m_Mutex;
QSharedPointer<QDatabaseSo> QDatabaseSo::m_pInstance;

QDatabaseSo::QDatabaseSo()
{
}

int QDatabaseSo::getClassificationChildCount(int classId)
{
    return m_tableClassification.getChildCount(classId);
}

int QDatabaseSo::getClassificationChildRowId(int parentId, int row)
{
    return m_tableClassification.getChildRowId(parentId, row);
}

TreeModelDataItemClassification QDatabaseSo::getClassificationRecord(int classId)
{
    return m_tableClassification.getRecord(classId);
}

int QDatabaseSo::getClassificationParent(int childrenId)
{
    return m_tableClassification.getParent(childrenId);
}

bool QDatabaseSo::initDB()
{
    m_sqlite.createDatabase(DORAEMON_DB_NAME);
    QString dbPath = QApplication::applicationDirPath() + "/data";
    QDir dir(dbPath);
    QString dbFullName;
    if (dir.exists())
    {
        dbFullName = dir.absolutePath();
    }
    else
    {
        //只创建一级子目录，即必须保证上级目录存在
        if(!dir.mkdir(dbPath))
        {
            QLoggingLib::instance()->error("QDatabaseSo::initDB dir not exist.", LMV_DB);
            return false;
        }
    }
    if (!m_sqlite.open(dbFullName + "/" + DORAEMON_DB_NAME)) {
        QLoggingLib::instance()->error("QDatabaseSo::initDB db open fail.", LMV_DB);
        return false;
    }
    m_tableClassification.setSqliteUtil(&m_sqlite);
    if (m_sqlite.dbExists(TABLE_NAME_CLASSIFICATION))
    {
        return true;
    }
   initTables();
   return initData();
}


//void QDatabaseSo::removeDataBase()
//{
//    return m_sqlite.removeDataBase(DORAEMON_DB_NAME);
//}

bool QDatabaseSo::initTables()
{
   bool bSuccess = false;
   bSuccess = m_sqlite.exec("CREATE TABLE classification(classId integer PRIMARY KEY, cnName string, "
       "enName string, parentId integer DEFAULT 0,sortNum integer DEFAULT 0, status integer DEFAULT 0, des string)");
   if (!bSuccess)
   {
       QLoggingLib::instance()->error("QDatabaseSo::initTables create table classification fail.", LMV_DB);
       return bSuccess;
   }
   //同步配置信息表(上次同步时间等)
   bSuccess = m_sqlite.exec("CREATE TABLE doraemon_config(id integer PRIMARY KEY, keyName string, keyValue string)");
   if (!bSuccess)
   {
       QLoggingLib::instance()->error("QDatabaseSo::initTables create table doraemon_config fail.", LMV_DB);
       return bSuccess;
   }
   return bSuccess;
}

bool QDatabaseSo::initData()
{
    return m_sqlite.insert(QString("insert into doraemon_config(id, keyName, keyValue) values('%1', '%2', '%3')").arg(1).arg(TABLE_CONFIG_CLASS_FLAG).arg(0));
}

