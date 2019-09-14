#ifndef HTMLQT_GLOBAL_H
#define HTMLQT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HTMLQT_LIBRARY)
#  define HTMLQT_EXPORT Q_DECL_EXPORT
#else
#  define HTMLQT_EXPORT Q_DECL_IMPORT
#endif

#endif // HTMLQT_GLOBAL_H
