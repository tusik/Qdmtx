#ifndef QDMTX_GLOBAL_H
#define QDMTX_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QDMTX_LIBRARY)
#  define QDMTX_EXPORT Q_DECL_EXPORT
#else
#  define QDMTX_EXPORT Q_DECL_IMPORT
#endif

#endif // QDMTX_GLOBAL_H
