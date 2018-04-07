#ifndef QDBOPER_H
#define QDBOPER_H
#include "../qcontrolso_global.h"
#include <QObject>
#include <QThread>
#include "qdboperthreadentity.h"
#include "qcommlib.h"
class QCONTROLSOSHARED_EXPORT QDBOper : public QObject
{
    Q_OBJECT
public:
    QDBOper();

public:
    void saveClassInfo(const SyncRetClassificationStruct srcs);
    void saveRecordInfo(const SyncRetRecordStruct srrs);
public slots :
    void onThreadFinished();
private:
    QDBOperThreadEntity m_threadDbEntity;
    QThread m_dbThread;
signals:
    void signSaveClassInfo(const QVariant& mark);
    void signSaveRecordInfo(const QVariant& mark);
    void signalPrintDbThreadId();
};

#endif // QDBOPER_H
