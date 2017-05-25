/*
** print_flags_open.c for flags open in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 28 17:03:38 2017 Frederic Oddou
** Last update Fri Apr 28 18:08:41 2017 Frederic Oddou
*/

#include <stdio.h>
#include <sys/mman.h>
#include "strace.h"

static t_flag	g_list_flags_prot[] = {
  {PROT_EXEC, "PROT_EXEC"},
  {PROT_READ, "PROT_READ"},
  {PROT_WRITE, "PROT_WRITE"},
  {PROT_NONE, "PROT_NONE"},
  {0, NULL}
};

static t_flag	g_list_flags[] = {
  {MAP_SHARED, "MAP_SHARED"},
  {MAP_PRIVATE, "MAP_PRIVATE"},
  {MAP_32BIT, "MAP_32BIT"},
  {MAP_FIXED, "MAP_FIXED"},
  {MAP_ANONYMOUS, "MAP_ANONYMOUS"},
  {MAP_DENYWRITE, "MAP_DENYWRITE"},
  {MAP_EXECUTABLE, "MAP_EXECUTABLE"},
  {MAP_FILE, "MAP_FILE"},
  {MAP_GROWSDOWN, "MAP_GROWSDOWN"},
  {MAP_HUGETLB, "MAP_HUGETLB"},
  {MAP_LOCKED, "MAP_LOCKED"},
  {MAP_NONBLOCK, "MAP_NONBLOCK"},
  {MAP_NORESERVE, "MAP_NORESERVE"},
  {MAP_POPULATE, "MAP_POPULATE"},
  {MAP_STACK, "MAP_STACK"},
  {0, NULL}
};

static int	display_flags(t_core *core, int flags, t_flag *list)
{
  int		i;
  int		len;
  int		display;

  i = display = len = 0;
  while (list[i].name != NULL)
    {
      if (flags & list[i].flag)
	{
	  if (display)
	    len += fprintf(core->fd, "|");
	  len += fprintf(core->fd, "%s", list[i].name);
	  display++;
	}
      i++;
    }
  return (len);
}

int		print_flags_mmap_prot(t_core *core, long long value)
{
  return (display_flags(core, value, g_list_flags_prot));
}

int		print_flags_mmap(t_core *core, long long value)
{
  return (display_flags(core, value, g_list_flags));
}
