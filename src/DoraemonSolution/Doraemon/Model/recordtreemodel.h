#ifndef RECORDTREEMODEL_H
#define RECORDTREEMODEL_H
#include <QAbstractItemModel>
#include "qcommlib.h"
#include "ModelData/dbtreemodeldatarecordimpl.h"
#include "ModelData/itreemodeldata.h"

class RecordTreeModel : public QAbstractItemModel
{
public:
    RecordTreeModel();
    void setQuery(RecordQuery rq);
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
private:
    RecordQuery m_rq;
    ITreeModelData * m_pModelData;

};

#endif // RECORDTREEMODEL_H
