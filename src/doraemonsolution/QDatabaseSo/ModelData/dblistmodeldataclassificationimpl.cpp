#include "dblistmodeldataclassificationimpl.h"
#include "../qdatabaseso.h"
#include "ModelData/treemodeldataitemclassification.h"
DBListModelDataClassificationImpl::DBListModelDataClassificationImpl()
{

}

int DBListModelDataClassificationImpl::index(int parentId, int row)
{
    Q_UNUSED(parentId);
    return QDatabaseSo::instance().getClassificationRowId(row, m_rq);
}

QVariant DBListModelDataClassificationImpl::data(int recordId)
{
    TreeModelDataItemClassification item = QDatabaseSo::instance().getClassificationRecord(recordId);
    if(item.classId != NOT_FIND_RECORD_ID){
        return item.cnName;
    }
    return QVariant();
}

int DBListModelDataClassificationImpl::childCount(int id)
{
    Q_UNUSED(id);
     return QDatabaseSo::instance().getClassificationCount(m_rq);
}

int DBListModelDataClassificationImpl::columnCount(int parentId)
{
    Q_UNUSED(parentId);
    return 1;
}

void DBListModelDataClassificationImpl::setQuery(RecordQuery rq)
{
    m_rq = rq;
}

