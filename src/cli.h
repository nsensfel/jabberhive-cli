#ifndef _JH_CLI_CLI_H_
#define _JH_CLI_CLI_H_

#include <stdio.h>

int JH_cli_open_socket
(
   FILE * s [const restrict static 1],
   const char socket_name [const restrict static 1]
);

int JH_cli_is_running (void);
int JH_cli_set_signal_handlers (void);

#endif
