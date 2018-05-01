#include "productinoapi.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextCodec>
ProductInoAPI::ProductInoAPI()
{

}

ProductInoAPI::~ProductInoAPI()
{

}

void ProductInoAPI::checkVersion(VersionInfoStruct vis)
{
    QString postUrl = "https://www.chunhuitech.cn/api/admin/api/prodinfo/versioncheck";
    QJsonObject json;
    json.insert("name", vis.appName);
    json.insert("technologyPlatform", vis.platform);
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    post(postUrl, dataArray);
}

void ProductInoAPI::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
}

void ProductInoAPI::requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode)
{
    Q_UNUSED(reply);
    QVariant dataVar;
    int code = EC_UNKNOWN;
    QString msg = QCommLib::instance().getErrorMessage(code);
    if (statusCode == 200) {
        QJsonParseError jsonError;
        QJsonDocument resJsonDoc = QJsonDocument::fromJson(data, &jsonError);
        if (jsonError.error == QJsonParseError::NoError) {
            if(resJsonDoc.isObject()){
                VersionInfoStruct vis;
                QVariantMap result = resJsonDoc.toVariant().toMap();
                code = result["code"].toInt();
                msg = result["msg"].toString();
                QVariantMap jsonData = result["data"].toMap();
//                qDebug() << "lastModTime:" << jsonData["lastModTime"].toLongLong();
                vis.verNum = jsonData["versionNum"].toInt();
                vis.downAddress = jsonData["downAddress"].toString();
                vis.version = jsonData["version"].toString();
                QString info = QString("check version finish code: %1  msg: %2").arg(QString::number(code)).arg(msg);
                m_pLog->info(info, LMV_NET);
                dataVar.setValue(vis);
                emit signCheckVersionFinished(code, msg, dataVar);
            }
        }
    }
}

