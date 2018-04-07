#ifndef QCOMMLIB_H
#define QCOMMLIB_H
#include <QList>
#include <QMap>
#include <QMutex>
#include <QDebug>
#include <QAtomicPointer>
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



///////数据库表结构体/////////
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

struct DoraemonConfigTable
{
    uint id;
    QString keyName;
    QString keyValue;
};



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

//查询条件
struct RecordQuery
{
    int classId;
//    QString title;
//    QString label;
//    QString contentPlain;
    QString queryKey;
};


//列头
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
            if(!QAtomicPointer<QCommLib>::isTestAndSetNative())//运行时进行检测
                qDebug() << "Error: don's support TestAndSetNative!!!!!!";
    #endif
            //双重检测加锁
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
