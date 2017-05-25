/*
** print_flags_open.c for flags open in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 28 17:03:38 2017 Frederic Oddou
** Last update Fri Apr 28 17:47:57 2017 Frederic Oddou
*/

#include <stdio.h>
#include <asm/prctl.h>
#include <sys/prctl.h>
#include "strace.h"

static t_flag	g_list_flags[] = {
  {ARCH_SET_FS, "ARCH_SET_FS"},
  {ARCH_GET_FS, "ARCH_GET_FS"},
  {ARCH_SET_GS, "ARCH_SET_GS"},
  {ARCH_GET_GS, "ARCH_GET_GS"},
  {0, NULL}
};

int		print_flags_arch_prctl(t_core *core, long long value)
{
  int		len;
  int		i;
  int		display;

  i = display = len = 0;
  while (g_list_flags[i].name != NULL)
    {
      if (value == g_list_flags[i].flag)
	{
	  if (display)
      	    len += fprintf(core->fd, "|");
	  len += fprintf(core->fd, "%s", g_list_flags[i].name);
	  display++;
	  break;
	}
      i++;
    }
  return (len);
}
