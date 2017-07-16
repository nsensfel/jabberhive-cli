#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#include "error/error.h"

#include "pervasive.h"

#include "./cli.h"

static volatile char JH_GATEWAY_IS_RUNNING = (char) 1;

static void request_termination (int const signo)
{
   if ((signo == SIGINT) || (signo == SIGTERM))
   {
      JH_GATEWAY_IS_RUNNING = (char) 0;
   }
}

int JH_cli_is_running (void)
{
   return (int) JH_GATEWAY_IS_RUNNING;
}

int JH_cli_set_signal_handlers (void)
{
   struct sigaction act;
   const int old_errno = errno;

   memset((void *) &act, 0, sizeof(struct sigaction));

   act.sa_handler = request_termination;

   errno = 0;

   if (sigaction(SIGHUP, &act, (struct sigaction * restrict) NULL) == -1)
   {
      JH_FATAL
      (
         stderr,
         "Could not set sigaction for SIGHUP (errno: %d): %s",
         errno,
         strerror(errno)
      );

      errno = old_errno;

      return -1;
   }

   errno = 0;

   if (sigaction(SIGINT, &act, (struct sigaction * restrict) NULL) == -1)
   {
      JH_FATAL
      (
         stderr,
         "Could not set sigaction for SIGINT (errno: %d): %s",
         errno,
         strerror(errno)
      );

      errno = old_errno;

      return -1;
   }

   act.sa_handler = SIG_IGN;

   if (sigaction(SIGPIPE, &act, (struct sigaction * restrict) NULL) == -1)
   {
      JH_FATAL
      (
         stderr,
         "Could not set sigaction for SIGPIPE (errno: %d): %s",
         errno,
         strerror(errno)
      );

      errno = old_errno;

      return -1;
   }

   errno = old_errno;

   return 0;
}
