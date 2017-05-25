/*
** print_number.c for print number in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Wed Apr  5 17:48:28 2017 Frederic Oddou
** Last update Thu Apr  6 21:16:36 2017 Frederic Oddou
*/

#include <stdio.h>
#include "strace.h"

int		print_number(t_core *core, long long value)
{
  int		len;

  len = fprintf(core->fd, "%lld", value);
  return (len);
}
