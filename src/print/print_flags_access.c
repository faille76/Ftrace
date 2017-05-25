/*
** print_flags_open.c for flags open in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 28 17:03:38 2017 Frederic Oddou
** Last update Fri Apr 28 17:47:41 2017 Frederic Oddou
*/

#include <stdio.h>
#include <fcntl.h>
#include "strace.h"

static t_flag	g_list_flags[] = {
  {F_OK, "F_OK"},
  {X_OK, "X_OK"},
  {W_OK, "W_OK"},
  {R_OK, "R_OK"},
  {0, NULL}
};

int		print_flags_access(t_core *core, long long value)
{
  int		i;
  int		len;
  int		display;

  i = display = len = 0;
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
