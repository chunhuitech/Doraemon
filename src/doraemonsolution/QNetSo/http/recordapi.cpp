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
    QString postUrl = "https://www.chunhuitech.cn/api/admin/api/record/fetch";
    QJsonObject json;
    json.insert("syncTime", lastTime);
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    QString info = QString("start record sync syncTime:%1").arg(QString::number(lastTime));
    m_pLog->info(info, LMV_NET);
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
                code = result["code"].toInt();
                msg = result["msg"].toString();
                QVariantMap jsonData = result["data"].toMap();
//                qDebug() << "lastModTime:" << jsonData["lastModTime"].toLongLong();
                sRRS.lastModTime = jsonData["lastModTime"].toLongLong();
                QVariantList jsonDataList = jsonData["dataList"].toList();
                QString info = QString("record sync finish cout:%1 code: %2  msg: %3").arg(QString::number(jsonDataList.size())).arg(QString::number(code)).arg(msg);
                m_pLog->info(info, LMV_NET);
                for(int i=0; i < jsonDataList.size(); i++){
                    QVariantMap jsonDataItem = jsonDataList[i].toMap();
//                    qDebug() << "recordId:" << jsonDataItem["id"].toInt();
//                    qDebug() << "title:" << jsonDataItem["title"].toString();
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
//                if(sRRS.lastModTime > 0 && sRRS.recordList.length() > 0){
                    dataVar.setValue(sRRS);
                    emit signSyncRecordFinished(code, msg, dataVar);
//                }
            }
        }
    }
}

