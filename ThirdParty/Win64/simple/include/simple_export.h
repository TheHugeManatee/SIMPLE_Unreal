
#ifndef SIMPLE_EXPORT_H
#define SIMPLE_EXPORT_H

#ifdef SIMPLE_STATIC_DEFINE
#  define SIMPLE_EXPORT
#  define SIMPLE_NO_EXPORT
#else
#  ifndef SIMPLE_EXPORT
#    ifdef simple_EXPORTS
        /* We are building this library */
#      define SIMPLE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define SIMPLE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef SIMPLE_NO_EXPORT
#    define SIMPLE_NO_EXPORT 
#  endif
#endif

#ifndef SIMPLE_DEPRECATED
#  define SIMPLE_DEPRECATED __declspec(deprecated)
#endif

#ifndef SIMPLE_DEPRECATED_EXPORT
#  define SIMPLE_DEPRECATED_EXPORT SIMPLE_EXPORT SIMPLE_DEPRECATED
#endif

#ifndef SIMPLE_DEPRECATED_NO_EXPORT
#  define SIMPLE_DEPRECATED_NO_EXPORT SIMPLE_NO_EXPORT SIMPLE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SIMPLE_NO_DEPRECATED
#    define SIMPLE_NO_DEPRECATED
#  endif
#endif

#endif /* SIMPLE_EXPORT_H */
