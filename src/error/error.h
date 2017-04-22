#ifndef _JH_ERROR_ERROR_H_
#define _JH_ERROR_ERROR_H_

#include <stdio.h>

#include "../pervasive.h"

#ifndef JH_DEBUG_PROGRAM_FLOW
   #define JH_DEBUG_PROGRAM_FLOW   (0 || JH_DEBUG_ALL)
#endif

#ifndef JH_DEBUG_CONFIG
   #define JH_DEBUG_CONFIG         (0 || JH_DEBUG_ALL)
#endif

#ifndef JH_DEBUG_LEARNING
   #define JH_DEBUG_LEARNING       (0 || JH_DEBUG_ALL)
#endif

#ifndef JH_DEBUG_NETWORK
   #define JH_DEBUG_NETWORK  1
#endif

#ifndef JH_DEBUG_NETWORK
   #define JH_DEBUG_NETWORK        (0 || JH_DEBUG_ALL)
#endif

#define JH_ENABLE_WARNINGS_OUTPUT              1
#define JH_ENABLE_RUNTIME_ERRORS_OUTPUT        1
#define JH_ENABLE_PROGRAMMING_ERRORS_OUTPUT    1
#define JH_ENABLE_FATAL_ERROR_OUTPUT           1

#ifdef JH_ENABLE_ERROR_LOCATION
   #define JH_LOCATION " [" __FILE__ "][" JH_TO_STRING(__LINE__) "]"
#else
   #define JH_LOCATION ""
#endif

#define JH_PRINT_STDERR(io, symbol, str, ...)\
   fprintf(io, "[" symbol "]" JH_LOCATION " " str "\n", __VA_ARGS__);

/*
 * Given that we use preprocessor contants as flags, we can expect the compilers
 * to remove the test condition for disabled flags. No need to be shy about
 * allowing many debug options.
 */

#define JH_DEBUG(io, flag, str, ...)\
   JH_ISOLATE\
   (\
      if (flag)\
      {\
         JH_PRINT_STDERR(io, "D", str, __VA_ARGS__);\
      }\
   )


#define JH_WARNING(io, str, ...)\
   JH_ISOLATE\
   (\
      if (JH_ENABLE_WARNINGS_OUTPUT)\
      {\
         JH_PRINT_STDERR(io, "W", str, __VA_ARGS__);\
      }\
   )

#define JH_ERROR(io, str, ...)\
   JH_ISOLATE\
   (\
      if (JH_ENABLE_RUNTIME_ERRORS_OUTPUT)\
      {\
         JH_PRINT_STDERR(io, "E", str, __VA_ARGS__);\
      }\
   )

#define JH_PROG_ERROR(io, str, ...)\
   JH_ISOLATE\
   (\
      if (JH_ENABLE_PROGRAMMING_ERRORS_OUTPUT)\
      {\
         JH_PRINT_STDERR(io, "P", str, __VA_ARGS__);\
      }\
   )

#define JH_FATAL(io, str, ...)\
   JH_ISOLATE\
   (\
     if (JH_ENABLE_FATAL_ERROR_OUTPUT)\
      {\
         JH_PRINT_STDERR(io, "F", str, __VA_ARGS__);\
      }\
   )

/* For outputs without dynamic content (static). ******************************/

#define JH_PRINT_S_STDERR(io, symbol, str)\
   fprintf(io, "[" symbol "]" JH_LOCATION " " str "\n");

#define JH_S_DEBUG(io, flag, str)\
   JH_ISOLATE\
   (\
      if (flag)\
      {\
         JH_PRINT_S_STDERR(io, "D", str);\
      }\
   )

#define JH_S_WARNING(io, str)\
   JH_ISOLATE\
   (\
      if (JH_ENABLE_WARNINGS_OUTPUT)\
      {\
         JH_PRINT_S_STDERR(io, "W", str);\
      }\
   )

#define JH_S_ERROR(io, str)\
   JH_ISOLATE\
   (\
      if (JH_ENABLE_RUNTIME_ERRORS_OUTPUT)\
      {\
         JH_PRINT_S_STDERR(io, "E", str);\
      }\
   )

#define JH_S_PROG_ERROR(io, str)\
   JH_ISOLATE\
   (\
      if (JH_ENABLE_PROGRAMMING_ERRORS_OUTPUT)\
      {\
         JH_PRINT_S_STDERR(io, "P", str);\
      }\
   )

#define JH_S_FATAL(io, str)\
   JH_ISOLATE\
   (\
     if (JH_ENABLE_FATAL_ERROR_OUTPUT)\
      {\
         JH_PRINT_S_STDERR(io, "F", str);\
      }\
   )
#endif
