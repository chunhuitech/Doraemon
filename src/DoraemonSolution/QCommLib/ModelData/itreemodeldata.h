#ifndef ITREEMODELDATA_H
#define ITREEMODELDATA_H
#include "itreemodeldataitem.h"
#include <QVariant>
#include <QModelIndex>
class ITreeModelData
{
public:
//    ITreeModelData();
    //项
//    virtual ITreeModelDataItem *child(int number) = 0;
    virtual int parent(int childrenId) = 0;
    virtual int index(int parentId, int row) = 0;
    virtual QVariant data(int recordId) = 0;
//    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const = 0;
//    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;
//    virtual int childNumber() = 0;
//    virtual ITreeModelData *insertChildren(int position, const ITreeModelDataItem * tmdi) = 0;
//    virtual ITreeModelData *childExist(const ITreeModelDataItem * tmdi) = 0;
//    virtual bool removeChildren(int position, int count) = 0;
//    virtual bool setData(const ITreeModelDataItem * tmdi) = 0;
    //如何删除相关项目(递归)？

    //行列
    virtual int childCount(int id = 0)  = 0;
    virtual int columnCount(int parentId) = 0;

};

#endif // ITREEMODELDATA_H