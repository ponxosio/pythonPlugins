#ifndef PYTHONPLUGINS_GLOBAL_H
#define PYTHONPLUGINS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PYTHONPLUGINS_LIBRARY)
#  define PYTHONPLUGINSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PYTHONPLUGINSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PYTHONPLUGINS_GLOBAL_H