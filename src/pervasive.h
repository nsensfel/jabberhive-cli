#ifndef _JH_PERVASIVE_H_
#define _JH_PERVASIVE_H_

#include <string.h>

#define JH_PROGRAM_VERSION   1
#define JH_PROTOCOL_VERSION  1

#ifdef __FRAMA_C__
   #define JH_RUNNING_FRAMA_C   1
#endif

#define JH_DEBUG_ALL 1

#ifndef JH_DEBUG_ALL
   #define JH_DEBUG_ALL 0
#endif

#define JH__TO_STRING(x) #x
#define JH_TO_STRING(x) JH__TO_STRING(x)
#define JH_ISOLATE(a) do {a} while (0)

/* strncmp stops at '\0' and strlen does not count '\0'. */
#define JH_IS_PREFIX(a, b) (strncmp(a, b, strlen(a)) == 0)

#define JH_STRING_EQUALS(a, b) (strcmp(a, b) == 0)

#endif
