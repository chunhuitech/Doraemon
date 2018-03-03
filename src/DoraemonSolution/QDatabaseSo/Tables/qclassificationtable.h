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
    int getChildRowId(int parentId, int row);
    TreeModelDataItemClassification getRecord(int classId);
    int getParent(int childrenId);

private:
    QSqliteUtils * m_pSqlUtil;
};

#endif // QCLASSIFICATIONTABLE_H
