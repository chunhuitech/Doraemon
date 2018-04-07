#ifndef BASEHTTP_H
#define BASEHTTP_H

#include <QObject>

#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class BaseHttp : public QObject
{
    Q_OBJECT
public:
    BaseHttp();
    ~BaseHttp();
    void get(const QString url);
    void post(const QString url, const QByteArray &data);

protected:
    virtual void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode) = 0;

public slots:
    void serviceRequestFinished(QNetworkReply *reply);

private:
    QNetworkRequest httpRequest;
    QNetworkAccessManager networkAccessManager;
    QSettings *settings;

signals:
};

#endif // BASEHTTP_H
