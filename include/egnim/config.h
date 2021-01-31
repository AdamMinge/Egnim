/* -------------------------------------------------------------------------------------------------- */
#ifndef EGNIM_CONFIG_H
#define EGNIM_CONFIG_H
/* -------------------------------------------------------------------------------------------------- */
/* ------------------------------------- Define EGNIM version --------------------------------------- */
/* -------------------------------------------------------------------------------------------------- */
#define EGNIM_VERSION_MAJOR 0
#define EGNIM_VERSION_MINOR 1
#define EGNIM_VERSION_PATCH 0
#define EGNIM_VERSION 0.1.0
#define EGNIM_VERSION_STR "0.1.0"
/* -------------------------------------------------------------------------------------------------- */
/* --------------------------------- Identify the operating system ---------------------------------- */
/* -------------------------------------------------------------------------------------------------- */
#if defined(_WIN32)
    #define EGNIM_OS_WINDOWS
#elif defined(__linux__)
    #define EGNIM_OS_LINUX
#else
    #error This operating system is not supported by EGNIM library
#endif
/* -------------------------------------------------------------------------------------------------- */
/* --------------------------------- Define a portable debug macro ---------------------------------- */
/* -------------------------------------------------------------------------------------------------- */
#if !defined(NDEBUG)
    #define EGNIM_DEBUG
#endif
/* -------------------------------------------------------------------------------------------------- */
/* ------------------- Define helpers to create portable import / export macros --------------------- */
/* -------------------------------------------------------------------------------------------------- */
#if !defined(EGNIM_STATIC)
    #if defined(EGNIM_OS_WINDOWS)
        #define EGNIM_API_EXPORT __declspec(dllexport)
        #define EGNIM_API_IMPORT __declspec(dllimport)
    #else
        #if __GNUC__ >= 4
            #define EGNIM_API_EXPORT __attribute__ ((__visibility__ ("default")))
            #define EGNIM_API_IMPORT __attribute__ ((__visibility__ ("default")))
        #else
            #define EGNIM_API_EXPORT
            #define EGNIM_API_IMPORT
        #endif
    #endif
#else
    #define EGNIM_API_EXPORT
    #define EGNIM_API_IMPORT
#endif
/* -------------------------------------------------------------------------------------------------- */
/* --------------------------- Define helpers to set items as depracted ----------------------------- */
/* -------------------------------------------------------------------------------------------------- */
#if !defined(EGNIM_DEPRECATED_WARNINGS)
    #define EGNIM_DEPRECATED [[deprecated]]
#else
    #define EGNIM_DEPRECATED
#endif
/* -------------------------------------------------------------------------------------------------- */
#endif //EGNIM_CONFIG_H
/* -------------------------------------------------------------------------------------------------- */
