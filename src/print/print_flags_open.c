/*
** print_flags_open.c for flags open in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 28 17:03:38 2017 Frederic Oddou
** Last update Fri Apr 28 17:48:27 2017 Frederic Oddou
*/

#include <stdio.h>
#include <fcntl.h>
#include "strace.h"

static t_flag	g_list_flags[] = {
  {O_APPEND, "O_APPEND"},
  {O_ASYNC, "O_ASYNC"},
  {O_CREAT, "O_CREAT"},
  {O_NOCTTY, "O_NOCTTY"},
  {O_NONBLOCK, "O_NONBLOCK"},
  {O_DIRECTORY, "O_DIRECTORY"},
  {O_DSYNC, "O_DSYNC"},
  {O_EXCL, "O_EXCL"},
  {O_NOFOLLOW, "O_NOFOLLOW"},
  {O_SYNC, "O_SYNC"},
  {O_TRUNC, "O_TRUNC"},
  {O_CLOEXEC, "O_CLOEXEC"},
  {0, NULL}
};

int		print_flags_open(t_core *core, long long value)
{
  int		i;
  int		len;
  int		display;

  i = len = 0;
  display = 1;
  if ((value & O_RDONLY) == 0)
    len += fprintf(core->fd, "O_RDONLY");
  else if ((value & O_WRONLY) == 1)
    len += fprintf(core->fd, "O_WRONLY");
  else if ((value & O_RDWR) == 2)
    len += fprintf(core->fd, "O_RDWR");
  while (g_list_flags[i].name != NULL)
    {
      if (value & g_list_flags[i].flag)
	{
	  if (display)
	    len += fprintf(core->fd, "|");
	  len += fprintf(core->fd, "%s", g_list_flags[i].name);
	  display++;
	}
      i++;
    }
  return (len);
}
