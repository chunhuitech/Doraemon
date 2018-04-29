#include "dbtreemodeldatarecordimpl.h"
#include "../qdatabaseso.h"
DBTreeModelDataRecordImpl::DBTreeModelDataRecordImpl()
{
    m_realCount =0;
}

void DBTreeModelDataRecordImpl::setQuery(RecordQuery rq)
{
    m_rq = rq;

}

int DBTreeModelDataRecordImpl::parent(int childrenId)
{
    Q_UNUSED(childrenId);
    return NOT_FIND_RECORD_ID;
}

int DBTreeModelDataRecordImpl::index(int parentId, int row)
{
    return QDatabaseSo::instance().getRecordChildRowId(parentId, row, m_rq);
}

QVariant DBTreeModelDataRecordImpl::data(int recordId)
{
    RecordStruct item = QDatabaseSo::instance().getRecordRecord(recordId);
    QVariant variant = QVariant::fromValue(item);
    return variant;
}

int DBTreeModelDataRecordImpl::childCount(int id)
{
    return QDatabaseSo::instance().getRecordChildCount(m_rq, id);
}

int DBTreeModelDataRecordImpl::columnCount(int parentId)
{
    Q_UNUSED(parentId);
    return RC_Count;
}

int DBTreeModelDataRecordImpl::realCount()
{
    return QDatabaseSo::instance().getRealCount(m_rq);
}

