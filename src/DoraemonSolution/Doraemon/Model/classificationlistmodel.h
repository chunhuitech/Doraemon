#ifndef CLASSIFICATIONLISTMODEL_H
#define CLASSIFICATIONLISTMODEL_H
#include <QAbstractItemModel>
#include "ModelData/dblistmodeldataclassificationimpl.h"
#include "ModelData/itreemodeldata.h"

class ClassificationListModel : public QAbstractListModel
{
public:
    ClassificationListModel();
    void setQuery(RecordQuery cq);
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    RecordQuery m_cq;
    ITreeModelData * m_pModelData;
};

#endif // CLASSIFICATIONLISTMODEL_H
