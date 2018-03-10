#ifndef QDATABASESO_H
#define QDATABASESO_H

#include <QSharedPointer>
#include <QMutexLocker>

#include "qdatabaseso_global.h"
#include "qsqliteutils.h"
#include "Tables/qclassificationtable.h"
#include "dbdefine.h"
/*
 * 对一个指定数据库的操作都放在这，故做为一个单例
 */

class QDATABASESOSHARED_EXPORT QDatabaseSo
{
public:
    static QSharedPointer<QDatabaseSo>& instance()
    {

        if (m_pInstance.isNull())
        {
            QMutexLocker mutexLocker(&m_Mutex);
            if (m_pInstance.isNull())
                m_pInstance = QSharedPointer<QDatabaseSo>(new QDatabaseSo());
        }
        return m_pInstance;
    }

    bool initDB();
    bool initTables();
    bool initData();
//    void removeDataBase();
private:
    QDatabaseSo();

public:
    /////////////classification table////////////
    int getClassificationChildCount(int classId);
    int getClassificationChildRowId(int parentId, int row);
    TreeModelDataItemClassification getClassificationRecord(int classId);
    int getClassificationParent(int childrenId);

private:
    static QMutex m_Mutex;
    static QSharedPointer<QDatabaseSo> m_pInstance;

    QSqliteUtils m_sqlite;
    QClassificationTable m_tableClassification;
};


#endif // QDATABASESO_H
