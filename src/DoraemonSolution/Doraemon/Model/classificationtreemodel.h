#ifndef CLASSIFICATIONTREEMODEL_H
#define CLASSIFICATIONTREEMODEL_H
#include <QAbstractItemModel>
#include "ModelData/dbtreemodeldataclassificationimpl.h"
#include "ModelData/itreemodeldata.h"

class ClassificationTreeModel : public QAbstractItemModel
{
public:
    ClassificationTreeModel();
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    ITreeModelData * m_pModelData;

};

#endif // CLASSIFICATIONTREEMODEL_H
