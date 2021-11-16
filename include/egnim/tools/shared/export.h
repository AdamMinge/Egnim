#ifndef EGNIM_TOOLS_EXPORT_H
#define EGNIM_TOOLS_EXPORT_H


#include <egnim/config.h>

#if defined(TOOLS_SHARED_EXPORTS)
  #define TOOLS_SHARED_API EGNIM_API_EXPORT
#else
  #define TOOLS_SHARED_API EGNIM_API_IMPORT
#endif


#endif //EGNIM_TOOLS_EXPORT_H
