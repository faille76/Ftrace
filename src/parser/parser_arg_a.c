/*
** parser_arg_a.c for parser_arg_p in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Mar 31 11:35:34 2017 Frederic ODDOU
** Last update Fri Mar 31 11:35:34 2017 Frederic ODDOU
*/

#include <stdlib.h>
#include "parser.h"

static bool	is_positive_number(char *s)
{
  while (*s)
    {
      if (!(*s >= '0' && *s <= '9'))
	return (false);
      s++;
    }
  return (true);
}

bool		parser_arg_a(t_core *core, char *str)
{
  if (!is_positive_number(str))
    return (false);
  if ((core->padding = atoi(str)) <= 0)
    return (false);
  return (true);
}
