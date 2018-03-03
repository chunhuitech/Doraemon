#ifndef TREEMODELDATAITEMCLASSIFICATION_H
#define TREEMODELDATAITEMCLASSIFICATION_H
#include <QString>
#include "itreemodeldataitem.h"
class TreeModelDataItemClassification : public ITreeModelDataItem
{
public:
    TreeModelDataItemClassification();

public:
    int classId;
    QString cnName;
    QString enName;
    int parentId;
    int status;
    int sortNum;
    QString des;
};

#endif // TREEMODELDATAITEMCLASSIFICATION_H
