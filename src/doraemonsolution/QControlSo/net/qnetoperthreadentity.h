#ifndef QNETOPERTHREADENTITY_H
#define QNETOPERTHREADENTITY_H

#include <QObject>
#include "http/classificatonapi.h"
#include "../qcontrolso_global.h"
class QCONTROLSOSHARED_EXPORT QNetOperThreadEntity : public QObject
{
    Q_OBJECT
public:
    explicit QNetOperThreadEntity(QObject *parent = 0);

private:
    ClassificatonAPI classAPI;
signals:

public slots :
    void OnSignSyncClassStart(int lastTime);
    void onPrintNetThreadId();
};

#endif // QNETOPERTHREADENTITY_H
