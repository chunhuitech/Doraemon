#ifndef QRECORDTABLE_H
#define QRECORDTABLE_H
#include "qrecordtable.h"
#include <QSqlRecord>
#include <QVariant>
#include "../qsqliteutils.h"
#include "qlogginglib.h"
#include "../dbdefine.h"
#include "qcommlib.h"

class QRecordTable
{
public:
    QRecordTable();


public:
    void setSqliteUtil(QSqliteUtils * pSqlUtil);
    void setLog(QLoggingLib* pLog);
    int insert(RecordStruct rs);
    int exist(int id);
    bool update(RecordStruct rs);
    bool deleteRecord(int id);
    int handleRecord(QList<RecordStruct> recordList);
    int getChildRowId(int parentId, int row, RecordQuery rq);
    int getChildCount(RecordQuery rq, int id);
    RecordStruct getRecord(int recordId);
private:
    QSqliteUtils * m_pSqlUtil;
    QLoggingLib* m_pLog;
};

#endif // QRECORDTABLE_H
