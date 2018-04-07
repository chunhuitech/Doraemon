#include "recordtreemodel.h"
#include "dbdefine.h"
#include "ModelData/treemodeldataitemrecord.h"
#include <QDateTime>
RecordTreeModel::RecordTreeModel()
{
    m_pModelData = new DBTreeModelDataRecordImpl();
}

void RecordTreeModel::setQuery(RecordQuery rq)
{
    m_rq = rq;
    m_pModelData->setQuery(m_rq);
}

QModelIndex RecordTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    if (parent.isValid())
        return QModelIndex();
    int parentId = NOT_FIND_RECORD_ID;
    //根据sortNum排序后 取第row条的Id
    int recordId  = m_pModelData->index(parentId, row);
    if (recordId != 0) {
        return createIndex(row, column, recordId);
    }
    else {
        return QModelIndex();
    }
}

QModelIndex RecordTreeModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int RecordTreeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    int parentItem = NOT_FIND_RECORD_ID;

    int count = m_pModelData->childCount(parentItem);
    return count;
}

int RecordTreeModel::columnCount(const QModelIndex &parent) const
{
    int parentItem = (int)(parent.internalPointer());
    return m_pModelData->columnCount(parentItem);
}

QVariant RecordTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int itemId = (int)(index.internalPointer());
    QVariant rv;
    if (Qt::DisplayRole == role)
    {
        QVariant variant = m_pModelData->data(itemId);
        if (variant.canConvert<RecordStruct>()) {
             RecordStruct item = variant.value<RecordStruct>();
             switch (index.column()) {
             case RC_Title:
                 rv = item.title;
                 break;

             case RC_FileSize:
                 rv = QCommLib::instance().bytesToGBMBKB(item.fileSize);
                 break;

             case RC_FileType:
                 rv = item.fileType;
                 break;

             case RC_CreateTime:
                  rv = QDateTime::fromTime_t(item.createTime).toString("yyyy-MM-dd hh:mm:ss");
                 break;

             default:
                 break;
             }
        }
    }
    return rv;
}

QVariant RecordTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant rv;
    if(orientation==Qt::Horizontal&&role==Qt::DisplayRole){
        switch (section) {
        case RC_Title:
            rv = "Title";
            break;

        case RC_FileSize:
            rv = "Size";
            break;

        case RC_FileType:
            rv = "Type";
            break;

        case RC_CreateTime:
             rv = "CreateTime";
            break;

        default:
            break;
        }
    }

    return rv;
}

