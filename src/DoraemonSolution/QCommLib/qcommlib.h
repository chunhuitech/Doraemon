#ifndef QCOMMLIB_H
#define QCOMMLIB_H
#include <QList>
#include <QMap>
#include <QMutex>
#include <QDebug>
#include <QAtomicPointer>
#include <QFile>
#include <QByteArray>
#include <QBitArray>
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned long long uint64_t;
const int GB = 1024 * 1024 * 1024;
const int MB = 1024 * 1024;
const int KB = 1024;
//quint64
#define FlashPlayWayFLAG "flashPlayWayFlag"
#define OSPlatFlag "OsPlatFlag"
#define DB_VERSION  "dbver"
#define UI_MAX_RECORD_SHOW  "maxrecordshow"
#define VERSION "1.0.0"
#define VERSION_NUM "10000"
#define APP_NAME "Doraemon"
#define APP_ID "1"
#define APP_PLAT_FORM_WIN_32 "Qt_Windows_32bit"
#define APP_PLAT_FORM_WIN_64 "Qt_Windows_64bit"
#define EVENT_START_UP    "start-up"
enum RecordStatusValue
{
    RSV_NORMAL = 0,
    RSV_DELETE = 1
};

enum LogModelValue
{
    LMV_ROOT = 0,
    LMV_NET = 32,
    LMV_DB = 64
};

enum ErrorCode
{
    EC_SUCCESS = 0,
    EC_ERROR = 400000,
    EC_UNKNOWN = 900000,
    EC_DB = 900002
};

enum FlashPlayWayFlag
{
    FPWF_AXWIDGET = 0,
    FPWF_WEBVIEW = 1
};

enum OsPlatFlag
{
    OPF_WIN_32 = 0,
    OPF_WIN_64 = 1
};

struct CommonData {
    QString iniFileName;
    int dbVersion;
    int maxRecordShow;
    int flashPlayWayFLag;
    int OsPlatFlag;
    bool hasFlashActiveX;
};


///////Database table structure/////////
struct ClassificationStruct
{
    int id;
    QString cnName;
    QString enName;
    int parentId;
    int sortNum;
    int status;
    QString des;
    qlonglong modifyTime;
    qlonglong createTime;
};
Q_DECLARE_METATYPE(ClassificationStruct)

struct RecordStruct
{
    int recordId;
    int classId;
    int sortNum;
    QString title;
    QString label;
    QString relativePath;
    int fileSize;
    QString fileType;
    QString contentHtml;
    QString contentPlain;
    int status;
    int modifyTime;
    int createTime;
};
Q_DECLARE_METATYPE(RecordStruct)

struct VersionInfoStruct
{
    int verNum;
    QString version;
    QString downAddress;
    QString appName;
    QString platform;
};
Q_DECLARE_METATYPE(VersionInfoStruct)

struct ProductActivityStruct
{
    int userId;
    QString clientFlag;
    QString procName;
    QString procVersion;
    int procId;
    QString os;
    QString eventName;
    QString ip;
    QString netIp;
    QString area;
    QString modifyTime;
    QString createTime;
    QString remarks;
};
Q_DECLARE_METATYPE(ProductActivityStruct)

struct IpInfoStruct
{
    QString netIp;
    QString areaInfo;
};

struct DoraemonConfigTable
{
    uint id;
    QString keyName;
    QString keyValue;
};


struct DorDataFileStruct
{
    int versionNum;
    QString downAddress;
};
Q_DECLARE_METATYPE(DorDataFileStruct)


struct SyncRetClassificationStruct
{
    qlonglong lastModTime;
    QList<ClassificationStruct> classificationList;
};
Q_DECLARE_METATYPE(SyncRetClassificationStruct)

struct SyncRetRecordStruct
{
    qlonglong lastModTime;
    QList<RecordStruct> recordList;
};
Q_DECLARE_METATYPE(SyncRetRecordStruct)

//query criteria
struct RecordQuery
{
    int classId;
//    QString title;
//    QString label;
//    QString contentPlain;
    QString queryKey;
    int maxCountShow;
};

//Column Headers
enum RecordColumn {
    RC_Title,
    RC_FileSize,
    RC_FileType,
    RC_CreateTime,
    RC_Count
};


class QCommLib
{
public:
    static QCommLib &instance(void)
        {
    #ifdef Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
            if(!QAtomicPointer<QCommLib>::isTestAndSetNative())//Test at runtime
                qDebug() << "Error: don's support TestAndSetNative!!!!!!";
    #endif
            //Double detection and lock
            if(m_pInstance.testAndSetOrdered(0,0)){
                QMutexLocker locker(&m_Mutex);
                m_pInstance.testAndSetOrdered(0, new QCommLib);
            }
            return * m_pInstance;
        }
public:
//    QCommLib();

    QString getErrorMessage(int code);
    QString bytesToGBMBKB(int size);
    void Zip (QString filename , QString zipfilename);
    void Unzip (QString zipfilename , QString filename);

//    CommonData commonData;
private:
    QCommLib();
    QCommLib(const QCommLib &);
    QCommLib & operator=(const QCommLib &);
//    QReadWriteLock internalMutex;
    static QMutex m_Mutex;
    static QAtomicPointer<QCommLib> m_pInstance;

private:
   QMap<int, QString> mapErrorCode;
};

#endif // QCOMMLIB_H
