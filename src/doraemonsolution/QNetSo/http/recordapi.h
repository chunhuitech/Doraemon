#ifndef RECORDAPI_H
#define RECORDAPI_H
#include "basehttp.h"
#include "qcommlib.h"
#include "../qnetso_global.h"
#include <QVariant>
#include "qlogginglib.h"
class QNETSOSHARED_EXPORT RecordAPI : public BaseHttp
{
    Q_OBJECT
public:
    RecordAPI();
    ~RecordAPI();

public:
    void syncData(qlonglong lastTime);
    void setLog(QLoggingLib* pLog);

signals:
    void signSyncRecordFinished(int code, QString msg, const QVariant& mark);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    QLoggingLib* m_pLog;
};

#endif // RECORDAPI_H
