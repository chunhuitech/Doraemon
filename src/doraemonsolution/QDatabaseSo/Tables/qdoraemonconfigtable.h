#ifndef QDORAEMONCONFIGTABLE_H
#define QDORAEMONCONFIGTABLE_H
#include "../dbdefine.h"
#include "qlogginglib.h"
#include "../qsqliteutils.h"
#include "qcommlib.h"
class QDoraemonConfigTable
{
public:
    QDoraemonConfigTable();

public:
    void setSqliteUtil(QSqliteUtils * pSqlUtil);
    DoraemonConfigTable getRecord(const QString& query_str);
    qlonglong getClassSyncTime();
    qlonglong getRecordSyncTime();
    QString getResourceServer();
    bool updateClassSyncTime(qlonglong lastModTime);
    bool updateRecordSyncTime(qlonglong lastModTime);

private:
    QSqliteUtils * m_pSqlUtil;
};

#endif // QDORAEMONCONFIGTABLE_H
