/*
** print_flags_open.c for flags open in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 28 17:03:38 2017 Frederic Oddou
** Last update Fri Apr 28 17:48:12 2017 Frederic Oddou
*/

#include <stdio.h>
#include "strace.h"

static t_flag	g_list_flags[] = {
  {SEEK_SET, "SEEK_SET"},
  {SEEK_CUR, "SEEK_CUR"},
  {SEEK_END, "SEEK_END"},
  {0, NULL}
};

int		print_flags_lseek(t_core *core, long long value)
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
