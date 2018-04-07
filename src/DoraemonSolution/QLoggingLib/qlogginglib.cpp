#include "qlogginglib.h"

QMutex QLoggingLib::m_Mutex;
QAtomicPointer<QLoggingLib> QLoggingLib::m_pInstance;
void QLoggingLib::initLogConfig(QString appPath)
{
    //Log4Qt::BasicConfigurator::configure();
    Log4Qt::PropertyConfigurator::configure(appPath + "/log4qt.conf");
    loggerRoot = Log4Qt::Logger::rootLogger();
    loggerRoot->info("root log init.");
    loggerNet = Log4Qt::Logger::logger("net");
    loggerNet->info("net log init.");
    loggerDb = Log4Qt::Logger::logger("db");
    loggerDb->info("db log init.");
}

void QLoggingLib::info(const QString &rMessage, LogModelValue lmv)
{
    switch (lmv) {
    case LMV_NET:
        loggerNet->info(rMessage);
        break;
    case LMV_DB:
        loggerDb->info(rMessage);
        break;
    default:
        loggerRoot->info(rMessage);
        break;
    }

}

void QLoggingLib::debug(const QString &rMessage, LogModelValue lmv)
{
    switch (lmv) {
    case LMV_NET:
        loggerNet->debug(rMessage);
        break;
    case LMV_DB:
        loggerDb->debug(rMessage);
        break;
    default:
        loggerRoot->debug(rMessage);
        break;
    }
}

void QLoggingLib::error(const QString &rMessage, LogModelValue lmv)
{
    switch (lmv) {
    case LMV_NET:
        loggerNet->error(rMessage);
        break;
    case LMV_DB:
        loggerDb->error(rMessage);
        break;
    default:
        loggerRoot->error(rMessage);
        break;
    }
}
