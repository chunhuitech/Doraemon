#include "qnetso.h"
#include <QHostAddress>
#include <QNetworkInterface>
#include <QSysInfo>
#include <QHostInfo>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <QEventLoop>
QMutex QNetSo::m_Mutex;
QAtomicPointer<QNetSo> QNetSo::m_pInstance;

QNetSo::QNetSo()
{
}

void QNetSo::setLog(QLoggingLib *pLog)
{
    m_pLog = pLog;
}

QString QNetSo::gethostMac()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning)
                && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    return strMacAddr;
}

QString QNetSo::gethostIp()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
       if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
           ipAddressesList.at(i).toIPv4Address())
       {
           strIpAddress = ipAddressesList.at(i).toString();
           break;
       }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     return strIpAddress;
}

QString QNetSo::getOSInfo()
{
    QString osInfo;
    QString machineName = QHostInfo::localHostName();
//    qDebug() << "buildCpuArchitecture: " << QSysInfo::buildCpuArchitecture();
    osInfo = QSysInfo::prettyProductName() +" [" +QSysInfo::productType() +" "+ QSysInfo::productVersion() +"(" + QString::number(QSysInfo::windowsVersion()) + ")]";
    osInfo += " | " + QSysInfo::buildAbi() + " | " + QSysInfo::currentCpuArchitecture() + " | " + QSysInfo::kernelType() + " " + QSysInfo::kernelVersion() + " | " + machineName;
    return osInfo;
}

IpInfoStruct QNetSo::GetNetIPInfo()
{
    IpInfoStruct iis;
    QString url = "http://whois.pconline.com.cn/";
    QByteArray res = GetHtml(url);
    QString netIp = GetNetIPPconline(res);
    QString areaInfo = GetAttributionPconline(res);
    iis.netIp = netIp;
    iis.areaInfo = areaInfo;
    return iis;
}

QByteArray QNetSo::GetHtml(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    responseData = reply->readAll();
    return responseData;
}

QString QNetSo::GetNetIPPconline(QByteArray responseData)
{
   QTextCodec* pTextCodec = QTextCodec::codecForName("GB2312");
   if (NULL == pTextCodec)
   {
       return "";
   }
   QString webCode = pTextCodec->toUnicode(responseData);
   QString ipinfo = "";
   QString web = webCode.replace(" ", "");
   web = web.replace("\r", "");
   web = web.replace("\n", "");
   web = web.replace("\t", "");
   QStringList list = web.split("</form>");
   if(list.count() > 0)
   {
       ipinfo = list[0];
       list = ipinfo.split("value=");
       ipinfo = list.last();
       list = ipinfo.split("><");
       ipinfo = list[0];
   }
   return ipinfo.replace("\"","");

}

QString QNetSo::GetAttributionPconline(QByteArray responseData)
{
    QTextCodec* pTextCodec = QTextCodec::codecForName("GB2312");
    if (NULL == pTextCodec)
    {
        return "";
    }
    QString webCode = pTextCodec->toUnicode(responseData);
    //    webCode = webCode.fromLocal8Bit(responseData.data());

    QString attribution = "";
    QString web = webCode; //.replace(" ", "");
    web = web.replace("\r", "");
    web = web.replace("\n", "");
    web = web.replace("\t", "");
    QStringList list = web.split("</form>");
    if(list.count() > 0)
    {
        attribution = list[0];
        list = attribution.split("<p>");
        attribution = list.last();
        list = attribution.split("</p>");
        attribution = list[0];
    }
    QStringList addInfo =  attribution.split("：");
    if(addInfo.count() > 1){
        return addInfo[1].trimmed();
    }
    return attribution;
}

