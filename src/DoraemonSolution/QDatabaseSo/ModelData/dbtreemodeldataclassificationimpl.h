#ifndef DBTREEMODELDATACLASSIFICATIONIMPL_H
#define DBTREEMODELDATACLASSIFICATIONIMPL_H
#include "ModelData/itreemodeldata.h"
#include <QModelIndex>
#include "qdatabaseso_global.h"
//
class QDATABASESOSHARED_EXPORT DBTreeModelDataClassificationImpl : public ITreeModelData
{
public:
    DBTreeModelDataClassificationImpl();

public:
    int parent(int childrenId);
    int index(int parentId, int row);
    QVariant data(int recordId);

    //行列
    int childCount(int id = 0);
    int columnCount(int parentId);

    int realCount() {return 0;}
    void setQuery(RecordQuery rq) {Q_UNUSED(rq);}

private:

};

#endif // DBTREEMODELDATACLASSIFICATIONIMPL_H
