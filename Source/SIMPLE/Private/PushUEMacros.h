#include "Runtime/Launch/Resources/Version.h"
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION == 19
#define RESTORE_4_19_MACROS
#include "UndefineMacros_UE_4.19.h"
#elif ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION == 20
#define RESTORE_4_20_MACROS
#include "UndefineMacros_UE_4.20.h"
#endif

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4668)
#endif
