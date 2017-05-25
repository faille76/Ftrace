/*
** print_flags_open.c for flags open in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 28 17:03:38 2017 Frederic Oddou
** Last update Fri Apr 28 17:43:39 2017 Frederic Oddou
*/

#include <stdio.h>
#include <sys/mman.h>
#include "strace.h"

static t_flag	g_list_flags[] = {
  {PROT_READ, "PROT_READ"},
  {PROT_WRITE, "PROT_WRITE"},
  {PROT_EXEC, "PROT_EXEC"},
  {PROT_GROWSUP, "PROT_GROWSUP"},
  {PROT_GROWSDOWN, "PROT_GROWSDOWN"},
  {0, NULL}
};

int		print_flags_mprotect(t_core *core, long long value)
{
  int		i;
  int		len;
  int		display;

  i = display = len = 0;
  if (value == 0)
    {
      len += fprintf(core->fd, "PROT_NONE");
      return (len);
    }
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
