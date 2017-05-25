/*
** print_char_pointer.c for print_char_pointer in /src/print/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun Apr  2 14:57:50 2017 Frederic ODDOU
** Last update Sun Apr  2 14:57:50 2017 Frederic ODDOU
*/

#include <stdio.h>
#include <sys/ptrace.h>
#include "strace.h"

static int	print_char(t_core *core,
			   char c)
{
  if (c == '\0')
    return (fprintf(core->fd, "\\0"));
  else if (c == '\n')
    return (fprintf(core->fd, "\\n"));
  else if (c == '\t')
    return (fprintf(core->fd, "\\t"));
  return (fprintf(core->fd, "%c", c));
}

int		print_char_pointer(t_core *core,
				   long long value)
{
  void		*ptr;
  int		len;
  long		ret;
  bool		cont;

  cont = true;
  len = 0;
  if ((ptr = (void *)value) != NULL)
    {
      len += fprintf(core->fd, "\"");
      while (cont)
	{
	  ret = ptrace(PTRACE_PEEKTEXT, core->pid, ptr, NULL);
	  if (*((char *)&ret))
	    len += print_char(core, *((char *)&ret));
	  else
	    cont = false;
	  ptr++;
	}
      len += fprintf(core->fd, "\"");
    }
  else
    len += fprintf(core->fd, "NULL");
  return (len);
}
