#ifndef QCOMMLIB_H
#define QCOMMLIB_H

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned long long uint64_t;

struct stTest
{
    int itemType;
    uint64_t id;
};

class QCommLib
{

public:
    QCommLib();
};

#endif // QCOMMLIB_H
