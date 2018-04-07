#include "classificationnetoper.h"

ClassificationNetOper::ClassificationNetOper()
{
    connect(&m_netThread, SIGNAL(finished()), this, SLOT(onThreadFinished()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(signalPrintNetThreadId()),
            &m_threadNetEntity, SLOT(onPrintNetThreadId()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(signSyncClass(int)),
            &m_threadNetEntity, SLOT(OnSignSyncClassStart(int)), Qt::QueuedConnection);
    m_threadNetEntity.moveToThread(&m_netThread);
    m_netThread.start();
}

void ClassificationNetOper::syncNetClass(int lastTime)
{
//
    emit signSyncClass(lastTime);
}

void ClassificationNetOper::printNetThreadId()
{
    emit signalPrintNetThreadId();
}

void ClassificationNetOper::exitHandler()
{
    m_netThread.quit();
    m_netThread.wait();
}

void ClassificationNetOper::onThreadFinished()
{
    qDebug() <<"on net ThreadFinished";
}

