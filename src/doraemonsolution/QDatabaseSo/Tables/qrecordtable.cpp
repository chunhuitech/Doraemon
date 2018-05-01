#include "qrecordtable.h"
QRecordTable::QRecordTable()
{
    m_pSqlUtil = NULL;
    m_pLog = NULL;
}


void QRecordTable::setSqliteUtil(QSqliteUtils *pSqlUtil)
{
    m_pSqlUtil = pSqlUtil;
}

void QRecordTable::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
    if(m_pSqlUtil){
        m_pSqlUtil->setLog(m_pLog);
    }
}

int QRecordTable::insert(RecordStruct rs)
{
    QString sql = QString("insert into record(recordId,classId,sortNum,title,label,relativePath,fileSize,fileType,contentHtml,contentPlain,status,modifyTime,createTime) values (") + QString::number(rs.recordId) + QString(",") \
            + QString::number(rs.classId) + QString(",")+ QString::number(rs.sortNum) + QString(",'") + rs.title + QString("','") + rs.label + QString("','") \
            + rs.relativePath + QString("',")+ QString::number(rs.fileSize) + QString(",'") + rs.fileType + QString("','") + rs.contentHtml + QString("','") \
            + rs.contentPlain + QString("',") + QString::number(rs.status) + QString(",")+ QString::number(rs.modifyTime) + QString(",") + QString::number(rs.createTime) +  QString(")");
    if(m_pSqlUtil)
        return m_pSqlUtil->insert(sql);
    return NOT_FIND_RECORD_ID;
}

bool QRecordTable::addRecords(QVector<RecordStruct> &vecRecord)
{
    if(m_pSqlUtil){
        m_pSqlUtil->transaction();
        for (int i = 0; i < vecRecord.size(); ++i) {
            insert(vecRecord[i]);
        }
        return m_pSqlUtil->commit();
    }
    return false;
}

bool QRecordTable::importRecords(QVector<QString> &vecRecord)
{
    if(m_pSqlUtil){
        m_pSqlUtil->transaction();
        for (int i = 0; i < vecRecord.size(); ++i) {
            m_pSqlUtil->insert(vecRecord[i]);
        }
        return m_pSqlUtil->commit();
    }
    return false;
}

bool QRecordTable::importRecords(QVector<RecordStruct> &vecRecord)
{
    if(m_pSqlUtil){
        m_pSqlUtil->transaction();
        for (int i = 0; i < vecRecord.size(); ++i) {
            if(exist(vecRecord[i].recordId)){
                update(vecRecord[i]);
            } else {
                insert(vecRecord[i]);
            }
        }
        return m_pSqlUtil->commit();
    }
    return false;
}

int QRecordTable::exist(int id)
{
    QString query_str = QString("select recordId from record where ") + QString("recordId='%1'").arg(id);
    int rowId = NOT_FIND_RECORD_ID;
    QSqlQuery sqlQuery(m_pSqlUtil->m_db);
    bool bSuccess = sqlQuery.exec(query_str);
    if (bSuccess)
    {
       int idIndex = sqlQuery.record().indexOf("recordId");
       while (sqlQuery.next())
       {
           rowId = sqlQuery.value(idIndex).toInt();
           break;
       }
    }
    else
    {
       QSqlError err = m_pSqlUtil->m_db.lastError();
       QString info = QString("QRecordTable::exist error type:%1 error info:%2 sql:%3").arg(m_pSqlUtil->getErrorInfo(err.type())).arg(err.text()).arg(query_str);
       m_pLog->error(info, LMV_DB);
    }
    return rowId;
}

bool QRecordTable::update(RecordStruct rs)
{
    QString sql = QString("update record set classId = %1,sortNum = %2,title = '%3',label = '%4',relativePath = '%5', \
            fileSize = %6,fileType = '%7',contentHtml = '%8',contentPlain = '%9',status = %10,modifyTime = %11,createTime = %12 where recordId = %13").arg(rs.classId).arg(rs.sortNum).arg(rs.title) \
            .arg(rs.label).arg(rs.relativePath).arg(rs.fileSize).arg(rs.fileType).arg(rs.contentHtml).arg(rs.contentPlain).arg(rs.status).arg(rs.modifyTime).arg(rs.createTime).arg(rs.recordId);
    return m_pSqlUtil->Updata(sql);
}

bool QRecordTable::deleteRecord(int id)
{
    QString expression = "recordId = " + QString::number(id);
    QString tableName = "record";
    return m_pSqlUtil->del(tableName, expression);
}

int QRecordTable::handleRecord(QList<RecordStruct> recordList)
{
    for(int i = 0; i < recordList.size(); i++){
        if( exist(recordList.at(i).recordId) > 0){
            if(recordList.at(i).status == RSV_DELETE) {
                deleteRecord(recordList.at(i).recordId);
            } else {
                update(recordList.at(i));
            }
        } else {
            insert(recordList.at(i));
        }
    }
    return 1;
}

int QRecordTable::getChildCount(RecordQuery rq, int id)
{
    Q_UNUSED(id);
//    QString query_str = QString("select 1 from record where classId='%1' ").arg(rq.classId);
    QString query_str = QString("select 1 from record where 1=1 ");
    if(rq.classId != 1){
        query_str += " and classId=" + QString::number(rq.classId);
    }
    if(!rq.queryKey.isEmpty() && !rq.queryKey.isNull()){
         query_str += " and (title like '%" + rq.queryKey + "%' or label like '%" + rq.queryKey + "%' or contentPlain like '%"  + rq.queryKey + "%')";
    }
//    m_pLog->info(query_str, LMV_DB);
    query_str += " Limit " + QString::number(rq.maxCountShow);
    if(m_pSqlUtil)
        return m_pSqlUtil->getCount(query_str);
    return NOT_FIND_RECORD_ID;
}

int QRecordTable::getRealCount(RecordQuery rq)
{
    QString query_str = QString("select 1 from record where 1=1 ");
    if(rq.classId != 1){
        query_str += " and classId=" + QString::number(rq.classId);
    }
    if(!rq.queryKey.isEmpty() && !rq.queryKey.isNull()){
         query_str += " and (title like '%" + rq.queryKey + "%' or label like '%" + rq.queryKey + "%' or contentPlain like '%"  + rq.queryKey + "%')";
    }
    if(m_pSqlUtil)
        return m_pSqlUtil->getCount(query_str);
    return NOT_FIND_RECORD_ID;
}

RecordStruct QRecordTable::getRecord(int recordId)
{
    RecordStruct rs;
    rs.recordId = NOT_FIND_RECORD_ID;
    QString query_str = QString(RECORD_TABLE_SELECT_FIELDS) + QString("recordId='%1'").arg(recordId);
    QSqlQuery sqlQuery(m_pSqlUtil->m_db);
    bool bSuccess = sqlQuery.exec(query_str);
    if (bSuccess)
    {
        int recordIdIndex = sqlQuery.record().indexOf("recordId");
        int classIdIndex = sqlQuery.record().indexOf("classId");
        int titleIndex = sqlQuery.record().indexOf("title");
        int relativePathIndex = sqlQuery.record().indexOf("relativePath");
        int fileSizeIndex = sqlQuery.record().indexOf("fileSize");
        int fileTypeIndex = sqlQuery.record().indexOf("fileType");
        int contentHtmlIndex = sqlQuery.record().indexOf("contentHtml");
        int contentPlainIndex = sqlQuery.record().indexOf("contentPlain");
        int modifyTimeIndex = sqlQuery.record().indexOf("modifyTime");
        int createTimeIndex = sqlQuery.record().indexOf("createTime");
        while (sqlQuery.next())
        {
            rs.recordId = sqlQuery.value(recordIdIndex).toInt();
            rs.classId = sqlQuery.value(classIdIndex).toInt();
            rs.title = sqlQuery.value(titleIndex).toString();
            rs.relativePath = sqlQuery.value(relativePathIndex).toString();
            rs.fileSize = sqlQuery.value(fileSizeIndex).toInt();
            rs.fileType = sqlQuery.value(fileTypeIndex).toString();
            rs.contentHtml = sqlQuery.value(contentHtmlIndex).toString();
            rs.contentPlain = sqlQuery.value(contentPlainIndex).toString();
            rs.modifyTime = sqlQuery.value(modifyTimeIndex).toInt();
            rs.createTime = sqlQuery.value(createTimeIndex).toInt();
            break;
        }
    }
    else
    {
        QSqlError err = m_pSqlUtil->m_db.lastError();
        QString info = QString("QClassificationTable::getRecord exec type:%1 error info:%2 sql:%3").arg(m_pSqlUtil->getErrorInfo(err.type())).arg(err.text()).arg(query_str);
        m_pLog->error(info, LMV_DB);
    }
    return rs;
}

qlonglong QRecordTable::getMaxSyncTime()
{
    qlonglong maxSyncTime = NOT_FIND_RECORD_ID;
    QString query_str = QString("Select max(modifyTime) as modifyTime From record ");

    QSqlQuery sqlQuery(m_pSqlUtil->m_db);
    bool bSuccess = sqlQuery.exec(query_str);
    if (bSuccess)
    {
        int modifyTimeIndex = sqlQuery.record().indexOf("modifyTime");
        while (sqlQuery.next())
        {
            maxSyncTime = sqlQuery.value(modifyTimeIndex).toLongLong();
            break;
        }
    }
    else
    {
        QSqlError err = m_pSqlUtil->m_db.lastError();
        QString info = QString("QRecordTable::getMaxSyncTime exec type:%1 error info:%2 sql:%3").arg(m_pSqlUtil->getErrorInfo(err.type())).arg(err.text()).arg(query_str);
        m_pLog->error(info, LMV_DB);
    }
    return maxSyncTime;
}

int QRecordTable::getChildRowId(int parentId, int row, RecordQuery rq)
{
    Q_UNUSED(parentId);
    int recordId = NOT_FIND_RECORD_ID;
//    QString query_str = QString("Select recordId From record where classId = '%1' order by sortnum asc limit '%2',1;").arg(rq.classId).arg(row);
    QString query_str = QString("select recordId from record where 1=1 ");
    if(rq.classId != 1){
        query_str += " and classId=" + QString::number(rq.classId);
    }
    if(!rq.queryKey.isEmpty() && !rq.queryKey.isNull()){
         query_str += " and (title like '%" + rq.queryKey + "%' or label like '%" + rq.queryKey + "%' or contentPlain like '%"  + rq.queryKey + "%')";
    }
    query_str +=" order by sortnum asc limit " + QString::number(row) + ",1";
//    m_pLog->info(query_str, LMV_DB);
    QSqlQuery sqlQuery(m_pSqlUtil->m_db);
    bool bSuccess = sqlQuery.exec(query_str);
    if (bSuccess)
    {
        int recordIdIndex = sqlQuery.record().indexOf("recordId");
        while (sqlQuery.next())
        {
            recordId = sqlQuery.value(recordIdIndex).toInt();
            break;
        }
    }
    else
    {
        QSqlError err = m_pSqlUtil->m_db.lastError();
        QString info = QString("QRecordTable::getChildRowId exec type:%1 error info:%2 sql:%3").arg(m_pSqlUtil->getErrorInfo(err.type())).arg(err.text()).arg(query_str);
        m_pLog->error(info, LMV_DB);
    }
    return recordId;
}
