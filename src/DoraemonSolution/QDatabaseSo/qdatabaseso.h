#ifndef QDATABASESO_H
#define QDATABASESO_H

#include <QSharedPointer>
#include <QMutexLocker>
#include <QReadWriteLock>

#include "qdatabaseso_global.h"
#include "qsqliteutils.h"
#include "Tables/qclassificationtable.h"
#include "Tables/qdoraemonconfigtable.h"
#include "Tables/qrecordtable.h"
#include "dbdefine.h"

class QDATABASESOSHARED_EXPORT QDatabaseSo : public QObject
{
    Q_OBJECT
public:
    static QDatabaseSo &instance(void)
        {
    #ifdef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
            if(!QAtomicPointer<QDatabaseSo>::isTestAndSetNative())
                qDebug() << "Error: don's support TestAndSetNative!!!!!!";
    #endif
            if(m_pInstance.testAndSetOrdered(0,0)){
                QMutexLocker locker(&m_Mutex);
                m_pInstance.testAndSetOrdered(0, new QDatabaseSo);
            }
            return * m_pInstance;
        }

    bool initDB(QLoggingLib* pLog);
    bool initTables();
    bool initData();
//    void removeDataBase();


public:
    /////////////classification table////////////
    int getClassificationChildCount(int classId);
    int getClassificationCount(RecordQuery cq);
    int getClassificationChildRowId(int parentId, int row);
    int getClassificationRowId(int row, RecordQuery cq);
    TreeModelDataItemClassification getClassificationRecord(int classId);
    int getClassificationParent(int childrenId);
    bool saveClassInfo(const SyncRetClassificationStruct srcs);


    //////////////record table/////////////
    int getRecordChildRowId(int parentId, int row, RecordQuery rq);
    int getRecordChildCount(RecordQuery rq, int id);
    int getRealCount(RecordQuery rq);
    RecordStruct getRecordRecord(int recordId);
    bool saveRecordInfo(const SyncRetRecordStruct srrs);
    bool importRecords(QVector<QString> & vecRecord);
    bool importRecords();
    /////doraemon_config table//////////
    qlonglong getClassSyncTimeConfig();
    qlonglong getRecordSyncTimeConfig();
    QString getResourceServer();

private:
    QSqliteUtils m_sqlite;
    QClassificationTable m_tableClassification;
    QDoraemonConfigTable m_tableConfig;
    QRecordTable m_tableRecord;
    QLoggingLib* m_pLog;
private:
    QDatabaseSo();
    QDatabaseSo(const QDatabaseSo &);
    QDatabaseSo & operator=(const QDatabaseSo &);
    QReadWriteLock internalMutex;
//    QWriteLocker internalMutex;
    static QMutex m_Mutex;
    static QAtomicPointer<QDatabaseSo> m_pInstance;

signals:
    void signSaveClassInfoFinished(int code, int count);
    void signSaveRecordInfoFinished(int code, int count);
    void signImportDBDataFinished(int code, int count);
};


#endif // QDATABASESO_H
