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
#include <stdio.h>
#include "parser.h"

bool		parser_arg_o(t_core *core, char *str)
{
  if ((core->fd = fopen(str, "w+")) == NULL)
    {
      perror("fopen failed");
      return (false);
    }
  return (true);
}
