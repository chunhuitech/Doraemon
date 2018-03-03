#include "dbtreemodeldataclassificationimpl.h"
#include "../qdatabaseso.h"
#include "ModelData/treemodeldataitemclassification.h"

DBTreeModelDataClassificationImpl::DBTreeModelDataClassificationImpl()
{

}

int DBTreeModelDataClassificationImpl::parent(int childrenId)
{
    return QDatabaseSo::instance()->getClassificationParent(childrenId);
}

int DBTreeModelDataClassificationImpl::index(int parentId, int row)
{
    return QDatabaseSo::instance()->getClassificationChildRowId(parentId, row);
}

QVariant DBTreeModelDataClassificationImpl::data(int recordId)
{
    TreeModelDataItemClassification item = QDatabaseSo::instance()->getClassificationRecord(recordId);
    if(item.classId != NOT_FIND_RECORD_ID){
        return item.cnName;
    }
    return QVariant();
}



int DBTreeModelDataClassificationImpl::childCount(int id)
{
    return QDatabaseSo::instance()->getClassificationChildCount(id);
}

int DBTreeModelDataClassificationImpl::columnCount(int parentId)
{
    Q_UNUSED(parentId);
    return 1;
}

