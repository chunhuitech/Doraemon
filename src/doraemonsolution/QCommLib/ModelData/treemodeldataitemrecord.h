#ifndef TREEMODELDATAITEMRECORD_H
#define TREEMODELDATAITEMRECORD_H
#include <QString>
#include "itreemodeldataitem.h"

class TreeModelDataItemRecord : public ITreeModelDataItem
{
public:
    TreeModelDataItemRecord();

public:
    int recordId;
    QString title;
    QString relativePath;
    int fileSize;
    QString fileType;
    QString contentHtml;
    QString contentPlain;
    int modifyTime;
    int createTime;
};

#endif // TREEMODELDATAITEMRECORD_H
