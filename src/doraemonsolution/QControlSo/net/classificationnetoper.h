#ifndef CLASSIFICATIONNETOPER_H
#define CLASSIFICATIONNETOPER_H
#include <QObject>
#include <QThread>
#include "qnetoperthreadentity.h"
#include "../qcontrolso_global.h"

class QCONTROLSOSHARED_EXPORT ClassificationNetOper : public QObject
{
    Q_OBJECT
public:
    ClassificationNetOper();

    void syncNetClass(int lastTime);
    void printNetThreadId();
    void exitHandler();
public slots :
    void onThreadFinished();

private:
//
    QNetOperThreadEntity m_threadNetEntity;
    QThread m_netThread;
signals:
    void signSyncClass(int lastTime);
    void signalPrintNetThreadId();
};


#endif // CLASSIFICATIONNETOPER_H
