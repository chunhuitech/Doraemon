#include "qcommlib.h"

QMutex QCommLib::m_Mutex;
QAtomicPointer<QCommLib> QCommLib::m_pInstance;

QCommLib::QCommLib()
{
    mapErrorCode.insert(0, "成功");
    mapErrorCode.insert(900000, "未知错误");
    mapErrorCode.insert(900002, "数据库错误");
}

QString QCommLib::getErrorMessage(int code)
{
    if(mapErrorCode.contains(code))
    {
        QMap<int,QString>::iterator it = mapErrorCode.find(code);
        return it.value();
    }
    return "未查找到错误码信息";
}

QString QCommLib::bytesToGBMBKB(int size)
{
    if (size / GB >= 1)
        return QString("%1 GB").arg(QString::number(size / (float)GB, 'f', 2));
    else if (size / MB >= 1)
        return QString("%1 MB").arg(QString::number(size / (float)MB, 'f', 2));
    else if (size / KB >= 1)
        return QString("%1 KB").arg(QString::number(size / (float)KB, 'f', 2));
    else
        return QString("%1 Bytes").arg(size);
}

void QCommLib::Zip(QString filename, QString zipfilename)
{
    QFile infile(filename);
    QFile outfile(zipfilename);
    infile.open(QIODevice::ReadOnly);
    outfile.open(QIODevice::WriteOnly);
    QByteArray uncompressedData = infile.readAll();
    QByteArray compressedData = qCompress(uncompressedData,9);
    outfile.write(compressedData);
    infile.close();
    outfile.close();
}

void QCommLib::Unzip(QString zipfilename, QString filename)
{
    QFile infile(zipfilename);
    QFile outfile(filename);
    infile.open(QIODevice::ReadOnly);
    outfile.open(QIODevice::WriteOnly);
    QByteArray uncompressedData = infile.readAll();
    QByteArray compressedData = qUncompress(uncompressedData);
    outfile.write(compressedData);
    infile.close();
    outfile.close();
}
