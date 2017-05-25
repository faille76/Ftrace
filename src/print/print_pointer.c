/*
** print_pointer.c for print pointer in /src/print/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun Apr  2 15:01:46 2017 Frederic ODDOU
** Last update Sun Apr  2 15:01:46 2017 Frederic ODDOU
*/

#include <stdio.h>
#include "strace.h"

int		print_pointer(t_core *core, long long value)
{
  int		len;

  len = 0;
  if (value)
    len += fprintf(core->fd, "0x%llx", (long long)value);
  else
    len += fprintf(core->fd, "NULL");
  return (len);
}
