#ifndef QLOGGINGLIB_H
#define QLOGGINGLIB_H

#include <QMutexLocker>
#include <QSharedPointer>

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
    static QSharedPointer<QLoggingLib> m_pInstance;

public:
    static QSharedPointer<QLoggingLib>& instance()
    {

        if (m_pInstance.isNull())
        {
            QMutexLocker mutexLocker(&m_Mutex);
            if (m_pInstance.isNull())
                m_pInstance = QSharedPointer<QLoggingLib>(new QLoggingLib());
        }
        return m_pInstance;
    }
    void initLogConfig(QString appPath);
    void info(const QString &rMessage, LogModelValue lmv = LMV_ROOT);
    void debug(const QString &rMessage, LogModelValue lmv = LMV_ROOT);
    void error(const QString &rMessage, LogModelValue lmv = LMV_ROOT);
};

#endif // QLOGGINGLIB_H
