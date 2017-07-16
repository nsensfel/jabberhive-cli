#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "error/error.h"

#include "pervasive.h"

#include "./cli.h"

int JH_cli_open_socket
(
   FILE * s [const restrict static 1],
   const char socket_name [const restrict static 1]
)
{
   int fd;
   struct sockaddr_un addr;

   const int old_errno = errno;

   errno = 0;

   if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
   {
      JH_FATAL
      (
         stderr,
         "Unable to create socket: %s.",
         strerror(errno)
      );

      errno = old_errno;

      return -1;
   }

   errno = old_errno;

   memset(&addr, 0, sizeof(addr));
   addr.sun_family = AF_UNIX;
   strncpy(addr.sun_path, socket_name, sizeof(addr.sun_path)-1);

   errno = 0;

   if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
   {
      JH_FATAL
      (
         stderr,
         "Unable to connect to address: %s.",
         strerror(errno)
      );

      errno = old_errno;

      close(fd);

      return -1;
   }

   errno = 0;

   *s = fdopen(fd, "w+");

   if (*s == (FILE *) NULL)
   {
      JH_FATAL
      (
         stderr,
         "Unable to open socket as a file: %s.",
         strerror(errno)
      );

      errno = old_errno;

      close(fd);

      return -1;
   }

   errno = old_errno;

   return 0;
}
