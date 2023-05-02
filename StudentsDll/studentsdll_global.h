#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(STUDENTSDLL_LIB)
#  define STUDENTSDLL_EXPORT Q_DECL_EXPORT
# else
#  define STUDENTSDLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define STUDENTSDLL_EXPORT
#endif
