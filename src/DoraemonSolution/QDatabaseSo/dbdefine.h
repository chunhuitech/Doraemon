#ifndef DBDEFINE_H
#define DBDEFINE_H

#define NOT_FIND_RECORD_ID    0
#define MODEL_INDEX_ROOT_ID   1

#define DORAEMON_DB_NAME    "doraemon.db"
#define TABLE_NAME_CLASSIFICATION    "classification"
#define TABLE_NAME_RECORD    "record"
#define TABLE_CONFIG_CLASS_FLAG    "classSyncTime"

#define CLASSIFICATION_TABLE_SELECT_FIELDS    "select classId,cnName,enName,parentId,"\
                                              "status,sortNum,des from classification  where "
class dbDefine
{
public:
    dbDefine();
};

#endif // DBDEFINE_H
