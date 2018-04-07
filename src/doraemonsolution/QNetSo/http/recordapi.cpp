#include "recordapi.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

RecordAPI::RecordAPI()
{

}

RecordAPI::~RecordAPI()
{

}

void RecordAPI::syncData(qlonglong lastTime)
{
    QString postUrl = "http://www.firemail.wang:8880/api/admin/api/record/fetch";
    QJsonObject json;
    json.insert("syncTime", lastTime);
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    post(postUrl, dataArray);
}

void RecordAPI::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
}

void RecordAPI::requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode)
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
                SyncRetRecordStruct sRRS;
                QVariantMap result = resJsonDoc.toVariant().toMap();
                qDebug() << "code:" << result["code"].toString();
                qDebug() << "msg:" << result["msg"].toString();
                QVariantMap jsonData = result["data"].toMap();
                qDebug() << "lastModTime:" << jsonData["lastModTime"].toLongLong();
                sRRS.lastModTime = jsonData["lastModTime"].toLongLong();
                QVariantList jsonDataList = jsonData["dataList"].toList();
                QString info = QString("record sync finish cout:%1").arg(jsonDataList.size());
                m_pLog->info(info, LMV_NET);
                for(int i=0; i < jsonDataList.size(); i++){
                    QVariantMap jsonDataItem = jsonDataList[i].toMap();
                    qDebug() << "recordId:" << jsonDataItem["id"].toInt();
                    qDebug() << "title:" << jsonDataItem["title"].toString();
                    RecordStruct rs;
                    rs.recordId = jsonDataItem["id"].toInt();
                    rs.classId = jsonDataItem["classId"].toInt();
                    rs.sortNum = jsonDataItem["sortNum"].toInt();
                    rs.title = jsonDataItem["title"].toString();
                    rs.label = jsonDataItem["label"].toString();
                    rs.relativePath = jsonDataItem["relativePath"].toString();
                    rs.fileSize = jsonDataItem["fileSize"].toInt();
                    rs.fileType = jsonDataItem["fileType"].toString();
                    rs.contentPlain = jsonDataItem["contentPlain"].toString();
                    rs.contentHtml = jsonDataItem["contentHtml"].toString();
                    rs.status = jsonDataItem["status"].toInt();
                    rs.modifyTime = jsonDataItem["modifyTime"].toLongLong() / 1000;
                    rs.createTime = jsonDataItem["createTime"].toLongLong() / 1000;
                    sRRS.recordList.append(rs);
                }
                if(sRRS.lastModTime > 0 && sRRS.recordList.length() > 0){
                    dataVar.setValue(sRRS);
                    emit signSyncRecordFinished(code, msg, dataVar);
                }
            }
        }
    }
}

