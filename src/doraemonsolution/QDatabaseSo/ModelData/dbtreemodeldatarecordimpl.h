#ifndef DBTREEMODELDATARECORDIMPL_H
#define DBTREEMODELDATARECORDIMPL_H
#include "ModelData/itreemodeldata.h"
#include "ModelData/treemodeldataitemrecord.h"
#include <QModelIndex>
#include "qdatabaseso_global.h"

class QDATABASESOSHARED_EXPORT DBTreeModelDataRecordImpl : public ITreeModelData
{
public:
    DBTreeModelDataRecordImpl();
    void setQuery(RecordQuery rq);
public:
    int parent(int childrenId);
    int index(int parentId, int row);
    QVariant data(int recordId);

    //行列
    int childCount(int id = 0);
    int columnCount(int parentId);

    //ext
    int realCount();

private:
    RecordQuery m_rq;
    int m_realCount;
};

#endif // DBTREEMODELDATARECORDIMPL_H
