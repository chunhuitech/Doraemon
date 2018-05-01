#include "configapi.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
ConfigApi::ConfigApi()
{

}

ConfigApi::~ConfigApi()
{

}

void ConfigApi::getDorDataVersion()
{
    QString postUrl = "https://www.chunhuitech.cn/api/admin/api/config/recorddataver";
    QJsonObject json;
    json.insert("time", "0");
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    post(postUrl, dataArray);
}

void ConfigApi::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
}

void ConfigApi::requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode)
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
                DorDataFileStruct ddfs;
                QVariantMap result = resJsonDoc.toVariant().toMap();
                code = result["code"].toInt();
                msg = result["msg"].toString();
                QVariantMap jsonData = result["data"].toMap();
//                    qDebug() << "lastModTime:" << jsonData["lastModTime"].toLongLong();
                ddfs.downAddress = jsonData["recordDataDownAddr"].toString();
                ddfs.versionNum = jsonData["recordDataVersion"].toInt();
                QString info = QString("dor data file sync finish version:%1 code: %2  msg: %3").arg(QString::number(ddfs.versionNum)).arg(QString::number(code)).arg(msg);
                m_pLog->info(info, LMV_NET);
                dataVar.setValue(ddfs);
                emit signGetDorDataVersionFinished(code, msg, dataVar);
            }
        }
    }
}

