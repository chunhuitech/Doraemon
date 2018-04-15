#ifndef QDBOPERTHREADENTITY_H
#define QDBOPERTHREADENTITY_H
#include "../qcontrolso_global.h"
#include <QObject>
#include "qlogginglib.h"

class QCONTROLSOSHARED_EXPORT QDBOperThreadEntity : public QObject
{
    Q_OBJECT
public:
    QDBOperThreadEntity();
public:
    void setLog(QLoggingLib* pLog);
public slots :
    void OnSaveClassInfo(const QVariant &mark);
    void OnSaveRecordInfo(const QVariant &mark);
    void OnImportRecords();
    void onPrintDbThreadId();

private:
    QLoggingLib* m_pLog;
};

#endif // QDBOPERTHREADENTITY_H
