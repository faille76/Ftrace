/*
** display_signal.c for signal in /src/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Sun May  7 13:52:01 2017 Frederic Oddou
** Last update Sun May  7 14:22:55 2017 Frederic Oddou
*/

#include <stdio.h>
#include "strace.h"

static const char *g_list_signal[] = {
  NULL,
  "SIGHUP",
  "SIGINT",
  "SIGQUIT",
  "SIGILL",
  "SIGTRAP",
  "SIGABRT",
  "SIGBUS",
  "SIGFPE",
  "SIGKILL",
  "SIGUSR1",
  "SIGSEGV",
  "SIGUSR2",
  "SIGPIPE",
  "SIGALRM",
  "SIGTERM",
  "SIGIO",
  "SIGCONT",
  "SIGCHLD",
  NULL,
  "SIGSTOP",
  "SIGTTIN",
  "SIGTTOU",
  "SIGINFO",
  "SIGXCPU",
  "SIGXFSZ",
  "SIGVTALRM",
  "SIGPROF",
  "SIGWINCH",
  NULL,
  "SIGBUS",
};

void	display_signal(const t_core *core, int signal)
{
  int	num;

  num = WSTOPSIG(signal);
  if (num >= 0 && num <= 33 && g_list_signal[num])
    fprintf(core->fd, "Received signal %s\n", g_list_signal[num]);
}
