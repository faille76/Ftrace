/*
** parser_arg_s.c for parser_arg_s in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Mar 31 11:27:44 2017 Frederic ODDOU
** Last update Fri Mar 31 11:27:44 2017 Frederic ODDOU
*/

#include "parser.h"

bool		parser_arg_s(t_core *core, char *str)
{
  (void)str;
  core->options[OPT_IS_TRUE] = true;
  return (true);
}
