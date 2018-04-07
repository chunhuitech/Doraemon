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

int QClassificationTable::getCount(RecordQuery cq)
{
    QString query_str = QString("select 1 from classification where status=0");
    if(!cq.queryKey.isEmpty() && !cq.queryKey.isNull()){
         query_str += " and (cnName like '%" + cq.queryKey + "%' or enName like '%" + cq.queryKey + "%' or des like '%"  + cq.queryKey + "%')";
    }
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
        QLoggingLib::instance().error(info, LMV_DB);
    }
    return classId;
}

int QClassificationTable::getRowId(int row,  RecordQuery cq)
{
    int classId = NOT_FIND_RECORD_ID;
    QString query_str = QString("Select classId From classification where status=0");
    if(!cq.queryKey.isEmpty() && !cq.queryKey.isNull()){
         query_str += " and (cnName like '%" + cq.queryKey + "%' or enName like '%" + cq.queryKey + "%' or des like '%"  + cq.queryKey + "%')";
    }
    query_str += " order by sortnum asc limit " + QString::number(row) + ",1;";
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
        QLoggingLib::instance().error(info, LMV_DB);
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
        QLoggingLib::instance().error(info, LMV_DB);
    }
    return tmdic;
}

int QClassificationTable::getParent(int childrenId)
{
    return getRecord(childrenId).parentId;
}

int QClassificationTable::handleRecord(QList<ClassificationStruct> classificationList)
{
    for(int i = 0; i < classificationList.size(); i++){
        if( exist(classificationList.at(i).id) > 0){
            if(classificationList.at(i).status == RSV_DELETE) {
                deleteRecord(classificationList.at(i).id);
            } else {
                update(classificationList.at(i));
            }
        } else {
            insert(classificationList.at(i));
        }
    }
    return 1;
}

int QClassificationTable::insert(ClassificationStruct cfs)
{
    QString sql = QString("insert into classification(classId, cnName, enName, parentId, sortNum, status, des) values (") + QString::number(cfs.id) + QString(",'") \
            + cfs.cnName + QString("','")+ cfs.enName + QString("',") + QString::number(cfs.parentId) + QString(",") + QString::number(cfs.sortNum) + QString(",") \
            + QString::number(cfs.status) + QString(",'") + cfs.des +  QString("')");
    if(m_pSqlUtil)
        return m_pSqlUtil->insert(sql);
    return NOT_FIND_RECORD_ID;
}

int QClassificationTable::exist(int classId)
{
    QString query_str = QString("select classId from classification where ") + QString("classId='%1'").arg(classId);
    int rowId = NOT_FIND_RECORD_ID;
    QSqlQuery sqlQuery(m_pSqlUtil->m_db);
    bool bSuccess = sqlQuery.exec(query_str);
    if (bSuccess)
    {
       int classIdIndex = sqlQuery.record().indexOf("classId");
       while (sqlQuery.next())
       {
           rowId = sqlQuery.value(classIdIndex).toInt();
           break;
       }
    }
    else
    {
       QSqlError err = m_pSqlUtil->m_db.lastError();
       QString info = QString("CSqliteUtils::existRecord error type:%1 error info:%2 sql:%3").arg(m_pSqlUtil->getErrorInfo(err.type())).arg(err.text()).arg(query_str);
       QLoggingLib::instance().error(info, LMV_DB);
    }
    return rowId;
}

bool QClassificationTable::update(ClassificationStruct cfs)
{
    QString sql = QString("update classification set cnName = '%1',enName = '%2',parentId = '%3',sortNum = '%4',status = '%5', \
            des = '%6' where classId = '%7'").arg(cfs.cnName).arg(cfs.enName).arg(cfs.parentId) \
            .arg(cfs.sortNum).arg(cfs.status).arg(cfs.des).arg(cfs.id);
    return m_pSqlUtil->Updata(sql);
}

bool QClassificationTable::deleteRecord(int classId)
{
    QString expression = "classId = " + QString::number(classId);
    QString tableName = "classification";
    return m_pSqlUtil->del(tableName, expression);
}

