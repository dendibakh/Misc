#pragma once

#include "ListAndIter.h"

#ifdef _DLL_EXPORTS
   #define _DLL_EXP __declspec(dllexport)
#else
   #define _DLL_EXP __declspec(dllimport)
#endif

_DLL_EXP ListAndIter GetStaticObj();