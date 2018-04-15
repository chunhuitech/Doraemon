#ifndef PRODUCTINOAPI_H
#define PRODUCTINOAPI_H
#include "basehttp.h"
#include "qcommlib.h"
#include "../qnetso_global.h"
#include <QVariant>
#include "qlogginglib.h"

class QNETSOSHARED_EXPORT ProductInoAPI : public BaseHttp
{
    Q_OBJECT
public:
    ProductInoAPI();
    ~ProductInoAPI();

public:
    void checkVersion(VersionInfoStruct vis);
    void setLog(QLoggingLib* pLog);


signals:
    void signCheckVersionFinished(int code, QString msg, const QVariant& mark);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    QLoggingLib* m_pLog;
};

#endif // PRODUCTINOAPI_H
