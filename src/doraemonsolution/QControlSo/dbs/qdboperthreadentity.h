#ifndef QDBOPERTHREADENTITY_H
#define QDBOPERTHREADENTITY_H
#include "../qcontrolso_global.h"
#include <QObject>

class QCONTROLSOSHARED_EXPORT QDBOperThreadEntity : public QObject
{
    Q_OBJECT
public:
    QDBOperThreadEntity();

public slots :
    void OnSaveClassInfo(const QVariant &mark);
    void OnSaveRecordInfo(const QVariant &mark);
     void onPrintDbThreadId();
};

#endif // QDBOPERTHREADENTITY_H
