#include "classificationtreemodel.h"

#include "dbdefine.h"

ClassificationTreeModel::ClassificationTreeModel()
{
    m_pModelData = new DBTreeModelDataClassificationImpl();
}

QModelIndex ClassificationTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    int parentId = MODEL_INDEX_ROOT_ID;
    if (parent.isValid()) {
        parentId = (int)(parent.internalPointer());
    }
    else {
        return createIndex(row, column, MODEL_INDEX_ROOT_ID);
    }
    //根据sortNum排序后 取第row条的Id
    int classId  = m_pModelData->index(parentId, row);
    if (classId != 0) {
        return createIndex(row, column, classId);
    }
    else {
        return QModelIndex();
    }
}

QModelIndex ClassificationTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }
    int item = (int)(child.internalPointer());

    int parentId = m_pModelData->parent(item);

    if (NOT_FIND_RECORD_ID == parentId)
        return QModelIndex();
    int rows = m_pModelData->childCount(parentId);
    return createIndex(rows, 0, parentId);
}

int ClassificationTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0;
    }

    int parentItem = NOT_FIND_RECORD_ID;
    if (parent.isValid()) {
        parentItem = (int)(parent.internalPointer());

    }
    int count = m_pModelData->childCount(parentItem);
    return count;
}

int ClassificationTreeModel::columnCount(const QModelIndex &parent) const
{
    int parentItem = (int)(parent.internalPointer());
    return m_pModelData->columnCount(parentItem);
}

QVariant ClassificationTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();

    int classId = (int)(index.internalPointer());
    //根据id获取记录
    return m_pModelData->data(classId);
}

