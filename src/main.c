#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "error/error.h"

#include "pervasive.h"

static void print_help (const char runnable [])
{
   printf
   (
      "JabberHive - CLI Gateway\n"
      "Software Version %d\n"
      "Protocol Version %d\n"
      "\nUsages:\n"
      "   JH GATEWAY:\t%s SOCKET_NAME\n"
      "   SHOW HELP:\tAnything else\n"
      "\nParameters:\n"
      "   SOCKET_NAME: valid UNIX socket.\n",
      JH_PROGRAM_VERSION,
      JH_PROTOCOL_VERSION,
      runnable
   );
}

static int open_socket
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

static void gateway
(
   FILE socket [const restrict static 1]
)
{
   int is_sending;
   int data, data_prev, is_last_message;

   is_sending = 1;

   for (;;)
   {
      if (is_sending)
      {
         data = fgetc(stdin);

         if (data == EOF)
         {
            return;
         }
         else
         {
            if (fputc(data, socket) == EOF)
            {
               JH_S_FATAL(stderr, "Unable to write to socket.");

               return;
            }
         }

         if (data == '\n')
         {
            is_sending = 0;
            data = 0;
            is_last_message = 0;
         }
      }
      else
      {
         data_prev = data;
         data = fgetc(socket);

         if (data == EOF)
         {
            JH_S_FATAL(stderr, "Unable to read from socket.");

            return;
         }
         else
         {
            if (fputc(data, stdout) == EOF)
            {
               /* ... seems like it wouldn't work. */
               JH_S_FATAL(stderr, "Unable to write to stdout.");

               return;
            }
         }

         is_last_message =
            (
               is_last_message
               || (
                  (data_prev == '!')
                  && (
                     (data == 'P')
                     || (data == 'N')
                  )
                  // TODO: check for the ' '.
               )
            );

         if (is_last_message && (data == '\n'))
         {
            is_sending = 1;
         }
      }
   }
}

int main (int const argc, const char * argv [const static argc])
{
   FILE * socket;

   if (argc != 2)
   {
      print_help(argv[0]);

      return -1;
   }

   if (open_socket(&socket, argv[1]) < 0)
   {
      return -1;
   }

   gateway(socket);

   fclose(socket);

   return 0;
}
