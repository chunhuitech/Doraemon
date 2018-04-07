#ifndef QNETSO_GLOBAL_H
#define QNETSO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QNETSO_LIBRARY)
#  define QNETSOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QNETSOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QNETSO_GLOBAL_H
