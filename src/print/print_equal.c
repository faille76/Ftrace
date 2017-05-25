/*
** print_equal.c for print equal in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr  6 23:45:31 2017 Frederic Oddou
** Last update Thu Apr  6 23:58:42 2017 Frederic Oddou
*/

#include <stdio.h>
#include "strace.h"

int		print_equal(t_core *core, long long value)
{
  int		len;
  int		padding;

  padding = ((value < core->padding) ? (core->padding - value + 1) : 2);
  len = fprintf(core->fd, "%*c ", padding, '=');
  return (len);
}
