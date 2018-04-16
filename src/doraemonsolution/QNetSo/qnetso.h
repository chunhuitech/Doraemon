#ifndef QNETSO_H
#define QNETSO_H
#include <QMutexLocker>
#include <QAtomicPointer>
#include <QReadWriteLock>

#include "qnetso_global.h"
#include "qlogginglib.h"

class QNETSOSHARED_EXPORT QNetSo : public QObject
{
    Q_OBJECT

public:
    static QNetSo &instance(void)
        {
    #ifdef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
            if(!QAtomicPointer<QNetSo>::isTestAndSetNative())
                qDebug() << "Error: don's support TestAndSetNative!!!!!!QNetSo";
    #endif
            if(m_pInstance.testAndSetOrdered(0,0)){
                QMutexLocker locker(&m_Mutex);
                m_pInstance.testAndSetOrdered(0, new QNetSo);
            }
            return * m_pInstance;
        }

public:
    void setLog(QLoggingLib* pLog);
    QString gethostMac();
    QString gethostIp();
    QString getOSInfo();
    IpInfoStruct GetNetIPInfo();
private:
    QByteArray GetHtml(QString url);
    QString GetNetIPPconline(QByteArray responseData);
    QString GetAttributionPconline(QByteArray responseData);

private:
    QNetSo();
    QNetSo(const QNetSo &);
    QNetSo & operator=(const QNetSo &);
    QReadWriteLock internalMutex;
    static QMutex m_Mutex;
    static QAtomicPointer<QNetSo> m_pInstance;
    QLoggingLib* m_pLog;
};

#endif // QNETSO_H
