#ifndef QCONTROLSO_H
#define QCONTROLSO_H
#include <QMutexLocker>
#include <QAtomicPointer>
#include <QReadWriteLock>
#include "qcontrolso_global.h"
#include "net/classificationnetoper.h"
#include "http/classificatonapi.h"
#include "http/recordapi.h"
#include "http/productinoapi.h"
#include "http/productactivityapi.h"
#include "http/configapi.h"
#include "downloadmanager.h"
#include "dbs/qdboper.h"
#include "qlogginglib.h"
class QCONTROLSOSHARED_EXPORT QControlSo : public QObject
{
    Q_OBJECT
public:

    // check dor ver
    void getDorDataVersion();
    //down dor data file
    void downDorDataFile(QString downAddr);
    //push Active
    void pushActiveInfo(ProductActivityStruct pas);
    //checkVersion
    void checkVersion(VersionInfoStruct vis);
    /////class data handle/////
    void syncClassification();

    ////record data handle////
    void syncRecord();
    void importRecords();

public:

    static QControlSo &instance(void)
        {
    #ifdef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
            if(!QAtomicPointer<QControlSo>::isTestAndSetNative())
                qDebug() << "Error: don's support TestAndSetNative!!!!!!";
    #endif
            if(m_pInstance.testAndSetOrdered(0,0)){
                QMutexLocker locker(&m_Mutex);
                m_pInstance.testAndSetOrdered(0, new QControlSo);
            }
            return * m_pInstance;
        }
    void setLog(QLoggingLib* pLog);
    void exitHandler();

public slots :
    void OnSignSyncClassFinished(int code, QString msg, const QVariant& mark);
    void OnSignSaveClassInfoFinished(int code, int count);
    void OnSignSaveRecordInfoFinished(int code, int count);
    void OnSignImportDBDataFinished(int code, int count);
    void downFinished();

    void OnSignSyncRecordFinished(int code, QString msg, const QVariant& mark);
    void OnSignCheckVersionFinished(int code, QString msg, const QVariant& mark);
    void OnSignGetDorDataVersionFinished(int code, QString msg, const QVariant& mark);
signals:
    void signSaveClassInfoFinished2UI(int code, int count);
    void signSaveRecordInfoFinished2UI(int code, int count);
    void signImportDBDataFinished2UI(int code, int count);
    void signCheckVersionFinished2UI(int code, QString msg, const QVariant& mark);
    void signDownDorFileFinished2UI(int code, int count);
    void signGetDorDataVersionFinished2UI(int code, QString msg, const QVariant& mark);

private:
//   not push to thread or "Cannot create children for a parent that is in a different thread"
//    ClassificationNetOper classNetOper;
    ClassificatonAPI classAPI;
    RecordAPI recordAPI;
    QDBOper dbOper;
    ProductInoAPI productInfoApi;
    ProductActivityAPI productActivityApi;
    DownloadManager manager;
    ConfigApi configApi;

private:
    QControlSo();
    QControlSo(const QControlSo &);
    QControlSo & operator=(const QControlSo &);
    QReadWriteLock internalMutex;
    static QMutex m_Mutex;
    static QAtomicPointer<QControlSo> m_pInstance;
    QLoggingLib* m_pLog;
};

#endif // QCONTROLSO_H
