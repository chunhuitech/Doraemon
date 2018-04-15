#ifndef CONFIGAPI_H
#define CONFIGAPI_H
#include "basehttp.h"
#include "qcommlib.h"
#include "../qnetso_global.h"
#include <QVariant>
#include "qlogginglib.h"

class QNETSOSHARED_EXPORT ConfigApi : public BaseHttp
{
    Q_OBJECT
public:
    ConfigApi();
    ~ConfigApi();


public:
    void getDorDataVersion();
    void setLog(QLoggingLib* pLog);
signals:
    void signGetDorDataVersionFinished(int code, QString msg, const QVariant& mark);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
private:
    QLoggingLib* m_pLog;
};

#endif // CONFIGAPI_H
