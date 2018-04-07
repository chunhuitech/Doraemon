#ifndef QCONTROLSO_H
#define QCONTROLSO_H
#include <QMutexLocker>
#include <QAtomicPointer>
#include <QReadWriteLock>
#include "qcontrolso_global.h"
#include "net/classificationnetoper.h"
#include "http/classificatonapi.h"
#include "http/recordapi.h"
#include "dbs/qdboper.h"
#include "qlogginglib.h"
class QCONTROLSOSHARED_EXPORT QControlSo  : public QObject
{
    Q_OBJECT
public:

    /////分类数据处理/////
    void syncClassification();

    ////记录数据处理////
    void syncRecord();

public:

    static QControlSo &instance(void)
        {
    #ifdef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
            if(!QAtomicPointer<QControlSo>::isTestAndSetNative())//运行时进行检测
                qDebug() << "Error: don's support TestAndSetNative!!!!!!";
    #endif
            //双重检测加锁
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
    void OnSignSaveClassInfoFinished(int code);
    void OnSignSaveRecordInfoFinished(int code);

    void OnSignSyncRecordFinished(int code, QString msg, const QVariant& mark);
signals:
    void signSaveClassInfoFinished2UI(int code);
    void signSaveRecordInfoFinished2UI(int code);

private:
//    由于网络请求本向就是异步的，所以这里就不需要再单独封装在线程中处理了，否则Cannot create children for a parent that is in a different thread
//    ClassificationNetOper classNetOper;
    ClassificatonAPI classAPI;
    RecordAPI recordAPI;
    QDBOper dbOper;

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
