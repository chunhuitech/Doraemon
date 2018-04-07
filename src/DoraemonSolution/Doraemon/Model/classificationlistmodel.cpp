#include "classificationlistmodel.h"
#include "dbdefine.h"

ClassificationListModel::ClassificationListModel()
{
    m_pModelData = new DBListModelDataClassificationImpl();
}

void ClassificationListModel::setQuery(RecordQuery cq)
{
    m_cq = cq;
    m_pModelData->setQuery(m_cq);
}

QModelIndex ClassificationListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    if (parent.isValid())
        return QModelIndex();
    int parentId = MODEL_INDEX_ROOT_ID;
//    if (parent.isValid()) {
//        parentId = (int)(parent.internalPointer());
//    }
//    else {
//        return createIndex(row, column, MODEL_INDEX_ROOT_ID);
//    }
    //根据sortNum排序后 取第row条的Id
    int classId  = m_pModelData->index(parentId, row);
    if (classId != 0) {
        return createIndex(row, column, classId);
    }
    else {
        return QModelIndex();
    }
}

int ClassificationListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return NOT_FIND_RECORD_ID;

    int parentItem = NOT_FIND_RECORD_ID;
//    if (parent.isValid()) {
//        parentItem = (int)(parent.internalPointer());

//    }
    int count = m_pModelData->childCount(parentItem);
    return count;
}

int ClassificationListModel::columnCount(const QModelIndex &parent) const
{
    int parentItem = (int)(parent.internalPointer());
    return m_pModelData->columnCount(parentItem);
}

QVariant ClassificationListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();

    int classId = (int)(index.internalPointer());
    //根据id获取记录
    return m_pModelData->data(classId);
}

