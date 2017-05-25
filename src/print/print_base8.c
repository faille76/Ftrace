/*
** print_base8.c for base 8 in /src/print/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon Apr  3 17:45:07 2017 Frederic ODDOU
** Last update Mon Apr  3 17:45:07 2017 Frederic ODDOU
*/

#include <string.h>
#include <stdio.h>
#include "strace.h"

int		print_base8(t_core *core,
			    long long nb)
{
  int		len;
  long long     div;
  int           size;
  char		*base;

  len = printf("0");
  base = "01234567";
  size = strlen(base);
  if (nb < 0)
    {
      len += fprintf(core->fd, "-");
      nb = -(nb);
    }
  div = 1;
  while ((nb / div) >= size)
    div *= size;
  while (div > 0)
    {
      len += fprintf(core->fd, "%c", base[(nb / div) % size]);
      div /= size;
    }
  return (len);
}
