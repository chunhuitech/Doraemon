#include "classificatonapi.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
const QString GET_Classfication = QString("https://www.chunhuitech.cn/api/admin/api/class/fetch");

ClassificatonAPI::ClassificatonAPI()
{
//    qRegisterMetaType<qlonglong>("qlonglong");
//    qRegisterMetaType<QVariant>("QVariant");
//    qRegisterMetaType<ClassificationStruct>("ClassificationStruct");
//    qRegisterMetaType<SyncRetClassificationStruct>("SyncRetClassificationStruct");
}

ClassificatonAPI::~ClassificatonAPI()
{

}

void ClassificatonAPI::syncData(qlonglong lastTime)
{
    QString postUrl = "https://www.chunhuitech.cn/api/admin/api/class/fetch";
    QJsonObject json;
    json.insert("syncTime", lastTime);
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    post(postUrl, dataArray);
}

void ClassificatonAPI::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
}

void ClassificatonAPI::requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode)
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
                SyncRetClassificationStruct sRCS;
                QVariantMap result = resJsonDoc.toVariant().toMap();
                code = result["code"].toInt();
                msg = result["msg"].toString();
                QVariantMap jsonData = result["data"].toMap();
//                    qDebug() << "lastModTime:" << jsonData["lastModTime"].toLongLong();
                sRCS.lastModTime = jsonData["lastModTime"].toLongLong();
                QVariantList jsonDataList = jsonData["dataList"].toList();
                QString info = QString("class sync finish cout:%1 code: %2  msg: %3").arg(QString::number(jsonDataList.size())).arg(QString::number(code)).arg(msg);
                m_pLog->info(info, LMV_NET);
                for(int i=0; i < jsonDataList.size(); i++){
                    QVariantMap jsonDataItem = jsonDataList[i].toMap();
//                        qDebug() << "id:" << jsonDataItem["id"].toString();
//                        qDebug() << "cnName:" << jsonDataItem["cnName"].toString();
                    ClassificationStruct cfs;
                    cfs.id = jsonDataItem["id"].toInt();
                    cfs.cnName = jsonDataItem["cnName"].toString();
                    cfs.enName = jsonDataItem["enName"].toString();
                    cfs.parentId = jsonDataItem["parentId"].toInt();
                    cfs.sortNum = jsonDataItem["sortNum"].toInt();
                    cfs.status = jsonDataItem["status"].toInt();
                    cfs.des = jsonDataItem["des"].toString();
                    sRCS.classificationList.append(cfs);
                }
//                    if(sRCS.lastModTime > 0 && sRCS.classificationList.length() > 0){
                    dataVar.setValue(sRCS);
                    emit signSyncClassFinished(code, msg, dataVar);
//                    }
            }
        }
    }
}

