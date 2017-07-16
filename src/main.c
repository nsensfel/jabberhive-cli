#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "error/error.h"

#include "pervasive.h"

#include "./cli.h"

static void print_help (const char runnable [const restrict static 1])
{
   printf
   (
      "JabberHive - CLI Gateway\n"
      "Software Version %d\n"
      "Protocol Version %d\n"
      "\nUsages:\n"
      "   JH GATEWAY:\t%s SOCKET_NAME\n"
      "   SHOW HELP:\tAnything else.\n"
      "\nParameters:\n"
      "   SOCKET_NAME:\tValid UNIX socket.\n",
      JH_PROGRAM_VERSION,
      JH_PROTOCOL_VERSION,
      runnable
   );
}

static int send_to_network
(
   FILE socket [const restrict static 1]
)
{
   int data;

   while (JH_cli_is_running())
   {
      data = fgetc(stdin);

      if (data == EOF)
      {
         return -1;
      }
      else
      {
         if (fputc(data, socket) == EOF)
         {
            JH_S_FATAL(stderr, "Unable to write to socket.");

            return -2;
         }
      }

      if (data == '\n')
      {
         return 0;
      }
   }

   return -1;
}

static int receive_from_network
(
   FILE socket [const restrict static 1]
)
{
   int data;
   int match_index;

   match_index = 0;

   while (JH_cli_is_running())
   {
      data = fgetc(socket);

      if (data == EOF)
      {
         JH_S_FATAL(stderr, "Unable to read from socket.");

         return -1;
      }
      else
      {
         if (fputc(data, stdout) == EOF)
         {
            /* ... seems like it wouldn't work. */
            JH_S_FATAL(stderr, "Unable to write to stdout.");

            return -2;
         }
      }

      switch (match_index)
      {
         case -1:
            if (data == '\n')
            {
               match_index = 0;
            }
            break;

         case 0:
            if (data == '!')
            {
               match_index = 1;
            }
            else if (data == '\n')
            {
               match_index = 0;
            }
            else
            {
               match_index = -1;
            }
            break;

         case 1:
            if ((data == 'P') || (data == 'N'))
            {
               match_index = 2;
            }
            else if (data == '\n')
            {
               match_index = 0;
            }
            else
            {
               match_index = -1;
            }
            break;

         case 2:
            if (data == ' ')
            {
               match_index = 3;
            }
            else if (data == '\n')
            {
               match_index = 0;
            }
            else
            {
               match_index = -1;
            }
            break;

         case 3:
            if (data == '\n')
            {
               return 0;
            }
            else
            {
               match_index = -1;
            }
            break;
      }
   }

   return -1;
}

int main (int const argc, const char * argv [const static argc])
{
   FILE * socket;

   if (argc != 2)
   {
      print_help(argv[0]);

      return -1;
   }

   if (JH_cli_set_signal_handlers() < 0)
   {
      return -1;
   }

   if (JH_cli_open_socket(&socket, argv[1]) < 0)
   {
      return -1;
   }

   while (JH_cli_is_running())
   {
      if (send_to_network(socket) < 0)
      {
         break;
      }

      if (receive_from_network(socket) < 0)
      {
         break;
      }
   }

   fclose(socket);

   return 0;
}
