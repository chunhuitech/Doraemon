#include "qclassificationtable.h"
#include "../dbdefine.h"

QClassificationTable::QClassificationTable()
{
    m_pSqlUtil = NULL;
}

void QClassificationTable::setSqliteUtil(QSqliteUtils *pSqlUtil)
{
    m_pSqlUtil = pSqlUtil;
}

int QClassificationTable::getChildCount(int classId)
{
    QString query_str = QString("select 1 from classification where parentId='%1' and status=0").arg(classId);
    if(m_pSqlUtil)
        return m_pSqlUtil->getCount(query_str);
    return NOT_FIND_RECORD_ID;
}

int QClassificationTable::getChildRowId(int parentId, int row)
{
    int classId = NOT_FIND_RECORD_ID;
    QString query_str = QString("Select classId From classification where parentid='%1' and status=0 order by sortnum asc limit '%2',1;").arg(parentId).arg(row);
    QSqlQuery sqlQuery(m_pSqlUtil->m_db);
    bool bSuccess = sqlQuery.exec(query_str);
    if (bSuccess)
    {
        int classIdIndex = sqlQuery.record().indexOf("classId");
        while (sqlQuery.next())
        {
            classId = sqlQuery.value(classIdIndex).toUInt();
            break;
        }
    }
    else
    {
        QSqlError err = m_pSqlUtil->m_db.lastError();
        QString info = QString("QClassificationTable::getChildRowId exec type:%1 error info:%2 sql:%3").arg(m_pSqlUtil->getErrorInfo(err.type())).arg(err.text()).arg(query_str);
        QLoggingLib::instance()->error(info, LMV_DB);
    }
    return classId;
}

TreeModelDataItemClassification QClassificationTable::getRecord(int classId)
{
    TreeModelDataItemClassification tmdic;
    tmdic.classId = NOT_FIND_RECORD_ID;
    tmdic.parentId = NOT_FIND_RECORD_ID;
    QString query_str = QString(CLASSIFICATION_TABLE_SELECT_FIELDS) + QString("classId='%1'").arg(classId);
    QSqlQuery sqlQuery(m_pSqlUtil->m_db);
    bool bSuccess = sqlQuery.exec(query_str);
    if (bSuccess)
    {
        int classIdIndex = sqlQuery.record().indexOf("classId");
        int cnNameIndex = sqlQuery.record().indexOf("cnName");
        int enNameIndex = sqlQuery.record().indexOf("enName");
        int parentIdIndex = sqlQuery.record().indexOf("parentId");
        int statusIndex = sqlQuery.record().indexOf("status");
        int sortNumIndex = sqlQuery.record().indexOf("sortNum");
        int desIndex = sqlQuery.record().indexOf("des");
        while (sqlQuery.next())
        {
            tmdic.classId = sqlQuery.value(classIdIndex).toUInt();
            tmdic.cnName = sqlQuery.value(cnNameIndex).toString();
            tmdic.enName = sqlQuery.value(enNameIndex).toString();
            tmdic.parentId = sqlQuery.value(parentIdIndex).toUInt();
            tmdic.status = sqlQuery.value(statusIndex).toUInt();
            tmdic.sortNum = sqlQuery.value(sortNumIndex).toUInt();
            tmdic.des = sqlQuery.value(desIndex).toString();
            break;
        }
    }
    else
    {
        QSqlError err = m_pSqlUtil->m_db.lastError();
        QString info = QString("QClassificationTable::getRecord exec type:%1 error info:%2 sql:%3").arg(m_pSqlUtil->getErrorInfo(err.type())).arg(err.text()).arg(query_str);
        QLoggingLib::instance()->error(info, LMV_DB);
    }
    return tmdic;
}

int QClassificationTable::getParent(int childrenId)
{
    return getRecord(childrenId).parentId;
}

