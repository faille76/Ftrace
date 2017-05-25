/*
** parser_types.c for types in /src/parser/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Mon Apr 10 19:02:13 2017 Frederic Oddou
** Last update Mon Apr 10 23:45:45 2017 Frederic Oddou
*/

#include <string.h>
#include <stdlib.h>
#include "parser.h"

int		parser_find_double(char *str)
{
  int		i;

  i = 0;
  while (g_parg[i].flag != NULL)
    {
      if (g_parg[i].type == FLAG_DOUBLE && !strcmp(g_parg[i].flag, str))
	return (i);
      i++;
    }
  return (-1);
}

int		parser_find_equal(char *str)
{
  int		i;

  i = 0;
  while (g_parg[i].flag != NULL)
    {
      if (g_parg[i].type == FLAG_EQUAL &&
	  !strncmp(g_parg[i].flag, str, strlen(g_parg[i].flag)) &&
	  str[strlen(g_parg[i].flag)] == '=' &&
	  str[strlen(g_parg[i].flag) + 1] != '\0')
	return (i);
      i++;
    }
  return (-1);
}

int		parser_find_argument(char *str)
{
  int		i;

  i = 0;
  while (g_parg[i].flag != NULL)
    {
      if (g_parg[i].type == FLAG_ARG && !strcmp(g_parg[i].flag, str))
	return (i);
      i++;
    }
  return (-1);
}

int		parser_find_single(char *str)
{
  int		i;

  i = 0;
  while (g_parg[i].flag != NULL)
    {
      if (g_parg[i].type == FLAG_SINGLE && !strncmp(g_parg[i].flag, str, 1))
	return (i);
      i++;
    }
  return (-1);
}
