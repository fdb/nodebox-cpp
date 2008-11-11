#ifndef NodeCoreGlobal_h
#define NodeCoreGlobal_h

#include <QtCore/qglobal.h>

#if defined(NODECORE_LIBRARY)
#  define NODECORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define NODECORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NodeCoreGlobal_h
