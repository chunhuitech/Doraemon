#ifndef PRODUCTACTIVITYAPI_H
#define PRODUCTACTIVITYAPI_H

#include "basehttp.h"
#include "qcommlib.h"
#include "../qnetso_global.h"
#include <QVariant>
#include "qlogginglib.h"

class QNETSOSHARED_EXPORT ProductActivityAPI : public BaseHttp
{
    Q_OBJECT
public:
    ProductActivityAPI();
    ~ProductActivityAPI();


public:
    void pushActivityInfo(ProductActivityStruct pas);
    void setLog(QLoggingLib* pLog);


protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    QLoggingLib* m_pLog;
};

#endif // PRODUCTACTIVITYAPI_H
