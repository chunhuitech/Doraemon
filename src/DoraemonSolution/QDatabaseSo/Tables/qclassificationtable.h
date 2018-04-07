#ifndef QCLASSIFICATIONTABLE_H
#define QCLASSIFICATIONTABLE_H
#include <QSqlRecord>
#include <QVariant>
#include "../qsqliteutils.h"
#include "qlogginglib.h"
#include "../dbdefine.h"
#include "ModelData/treemodeldataitemclassification.h"
class QClassificationTable
{
public:
    QClassificationTable();

public:
    void setSqliteUtil(QSqliteUtils * pSqlUtil);
    int getChildCount(int classId);
    int getCount(RecordQuery cq);
    int getChildRowId(int parentId, int row);
    int getRowId(int row, RecordQuery cq);
    TreeModelDataItemClassification getRecord(int classId);
    int getParent(int childrenId);
    int handleRecord(QList<ClassificationStruct> classificationList);
    int insert(ClassificationStruct cfs);
    int exist(int classId);
    bool update(ClassificationStruct cfs);
    bool deleteRecord(int classId);
private:
    QSqliteUtils * m_pSqlUtil;
};

#endif // QCLASSIFICATIONTABLE_H
