#ifndef CLASSIFICATONAPI_H
#define CLASSIFICATONAPI_H
#include "basehttp.h"
#include "qcommlib.h"
#include "../qnetso_global.h"
#include <QVariant>
#include "qlogginglib.h"
class QNETSOSHARED_EXPORT ClassificatonAPI : public BaseHttp
{
    Q_OBJECT
public:
    ClassificatonAPI();
    ~ClassificatonAPI();

public:
    void syncData(qlonglong lastTime);
    void setLog(QLoggingLib* pLog);
signals:
    void signSyncClassFinished(int code, QString msg, const QVariant& mark);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
private:
    QLoggingLib* m_pLog;
};

#endif // CLASSIFICATONAPI_H
