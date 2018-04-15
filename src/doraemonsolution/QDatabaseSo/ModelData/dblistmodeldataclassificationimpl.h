#ifndef DBLISTMODELDATACLASSIFICATIONIMPL_H
#define DBLISTMODELDATACLASSIFICATIONIMPL_H

#include "ModelData/itreemodeldata.h"
#include <QModelIndex>
#include "qdatabaseso_global.h"

class QDATABASESOSHARED_EXPORT DBListModelDataClassificationImpl : public ITreeModelData
{
public:
    DBListModelDataClassificationImpl();

public:
    int parent(int childrenId) {return (childrenId); }
    int index(int parentId, int row);
    QVariant data(int recordId);

    //行列
     int childCount(int id = 0);
    int columnCount(int parentId);

    int realCount() {return 0;}
     void setQuery(RecordQuery rq);

private:
     RecordQuery m_rq;
};

#endif // DBLISTMODELDATACLASSIFICATIONIMPL_H
