#include <QDir>
#include <QtWidgets/QApplication>
#include "qdatabaseso.h"
#include "qlogginglib.h"

QMutex QDatabaseSo::m_Mutex;
QAtomicPointer<QDatabaseSo> QDatabaseSo::m_pInstance;

QDatabaseSo::QDatabaseSo()
{
}

int QDatabaseSo::getClassificationChildCount(int classId)
{
//    QWriteLocker locker(&internalMutex);
    return m_tableClassification.getChildCount(classId);
}

int QDatabaseSo::getClassificationCount(RecordQuery cq)
{
    return m_tableClassification.getCount(cq);
}

int QDatabaseSo::getClassificationChildRowId(int parentId, int row)
{
//    QWriteLocker locker(&internalMutex);
    return m_tableClassification.getChildRowId(parentId, row);
}

int QDatabaseSo::getClassificationRowId(int row, RecordQuery cq)
{
    return m_tableClassification.getRowId(row, cq);
}


int QDatabaseSo::getRecordChildRowId(int parentId, int row, RecordQuery rq)
{
//    QWriteLocker locker(&internalMutex);
    return m_tableRecord.getChildRowId(parentId, row, rq);
}

int QDatabaseSo::getRecordChildCount(RecordQuery rq, int id)
{
//    QWriteLocker locker(&internalMutex);
    return m_tableRecord.getChildCount(rq, id);
}


TreeModelDataItemClassification QDatabaseSo::getClassificationRecord(int classId)
{
//    QWriteLocker locker(&internalMutex);
    return m_tableClassification.getRecord(classId);
}


RecordStruct QDatabaseSo::getRecordRecord(int recordId)
{
//    QWriteLocker locker(&internalMutex);
    return m_tableRecord.getRecord(recordId);
}

int QDatabaseSo::getClassificationParent(int childrenId)
{
//    QWriteLocker locker(&internalMutex);
    return m_tableClassification.getParent(childrenId);
}

bool QDatabaseSo::saveClassInfo(const SyncRetClassificationStruct srcs)
{
//    QWriteLocker locker(&internalMutex);
    bool sucess = m_tableConfig.updateClassSyncTime(srcs.lastModTime);
    //保存记录
    sucess = m_tableClassification.handleRecord(srcs.classificationList);
    if(sucess){
        emit signSaveClassInfoFinished(EC_SUCCESS);
    } else {
        emit signSaveClassInfoFinished(EC_ERROR);
    }
    return sucess;
}

bool QDatabaseSo::saveRecordInfo(const SyncRetRecordStruct srrs)
{
    bool sucess = m_tableConfig.updateRecordSyncTime(srrs.lastModTime);
    //保存记录
    sucess = m_tableRecord.handleRecord(srrs.recordList);
    if(sucess){
        emit signSaveRecordInfoFinished(EC_SUCCESS);
    } else {
        emit signSaveRecordInfoFinished(EC_ERROR);
    }
    return sucess;
}


qlonglong QDatabaseSo::getClassSyncTimeConfig()
{
//    QWriteLocker locker(&internalMutex);
    return m_tableConfig.getClassSyncTime();
}

qlonglong QDatabaseSo::getRecordSyncTimeConfig()
{
    return m_tableConfig.getRecordSyncTime();
}

QString QDatabaseSo::getResourceServer()
{
//    QWriteLocker locker(&internalMutex);
    return m_tableConfig.getResourceServer();
}

bool QDatabaseSo::initDB(QLoggingLib* pLog)
{
//    QWriteLocker locker(&internalMutex);
    m_pLog = pLog;
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
            m_pLog->error("QDatabaseSo::initDB dir not exist.", LMV_DB);
            return false;
        }
    }
    if (!m_sqlite.open(dbFullName + "/" + DORAEMON_DB_NAME)) {
        m_pLog->error("QDatabaseSo::initDB db open fail.", LMV_DB);
        return false;
    }
    m_tableClassification.setSqliteUtil(&m_sqlite);
    m_tableConfig.setSqliteUtil(&m_sqlite);
    m_tableRecord.setSqliteUtil(&m_sqlite);
    m_tableRecord.setLog(m_pLog);
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
       m_pLog->error("QDatabaseSo::initTables create table classification fail.", LMV_DB);
       return bSuccess;
   }
   //同步配置信息表(上次同步时间等)
   bSuccess = m_sqlite.exec("CREATE TABLE doraemon_config(id integer PRIMARY KEY, keyName string, keyValue string)");
   if (!bSuccess)
   {
       m_pLog->error("QDatabaseSo::initTables create table doraemon_config fail.", LMV_DB);
       return bSuccess;
   }
   //createTime modifyTime 最小时间单位为秒的整数
   bSuccess = m_sqlite.exec("CREATE TABLE record(recordId integer PRIMARY KEY, classId integer, sortNum integer DEFAULT 0, "
       "title string, label string, relativePath string, fileSize integer DEFAULT 0, fileType string, "
       "contentHtml string, contentPlain string, status integer DEFAULT 0, modifyTime integer DEFAULT 0, createTime integer DEFAULT 0)");
   if (!bSuccess)
   {
       m_pLog->error("QDatabaseSo::initTables create table record fail.", LMV_DB);
       return bSuccess;
   }
   return bSuccess;
}

bool QDatabaseSo::initData()
{
    m_sqlite.insert(QString("insert into doraemon_config(id, keyName, keyValue) values('%1', '%2', '%3')").arg(1).arg(TABLE_CONFIG_CLASS_FLAG).arg(0));
    m_sqlite.insert(QString("insert into doraemon_config(id, keyName, keyValue) values('%1', '%2', '%3')").arg(2).arg(TABLE_CONFIG_SERVER_FLAG).arg("http://www.firemail.wang:8088"));
    return m_sqlite.insert(QString("insert into doraemon_config(id, keyName, keyValue) values('%1', '%2', '%3')").arg(3).arg(TABLE_CONFIG_RECORD_FLAG).arg(0));
}

