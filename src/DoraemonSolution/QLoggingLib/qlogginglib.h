#ifndef QLOGGINGLIB_H
#define QLOGGINGLIB_H

#include <QMutexLocker>
#include <QAtomicPointer>

#include "log4qt/logger.h"
#include "log4qt/basicconfigurator.h"
#include "log4qt/propertyconfigurator.h"

#include "qcommlib.h"

//https://github.com/devbean/log4qt
class QLoggingLib
{
private:
    QLoggingLib(){}
    QLoggingLib(const QLoggingLib&){}
    QLoggingLib& operator=(const QLoggingLib&){return *this;}
public:
    ~QLoggingLib(){}

private:
    Log4Qt::Logger * loggerDb;
    Log4Qt::Logger * loggerNet;
    Log4Qt::Logger * loggerRoot;

private:
    static QMutex m_Mutex;
    static QAtomicPointer<QLoggingLib> m_pInstance;
public:
    static QLoggingLib &instance(void)
        {
    #ifdef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
            if(!QAtomicPointer<QLoggingLib>::isTestAndSetNative())
                qDebug() << "Error: don's support TestAndSetNative!!!!!!";
    #endif

            if(m_pInstance.testAndSetOrdered(0,0)){
                QMutexLocker locker(&m_Mutex);
                m_pInstance.testAndSetOrdered(0, new QLoggingLib);
            }
            return * m_pInstance;
        }
    void initLogConfig(QString appPath);
    void info(const QString &rMessage, LogModelValue lmv = LMV_ROOT);
    void debug(const QString &rMessage, LogModelValue lmv = LMV_ROOT);
    void error(const QString &rMessage, LogModelValue lmv = LMV_ROOT);
};

#endif // QLOGGINGLIB_H
