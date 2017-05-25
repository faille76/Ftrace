/*
** parser.c for parser in /src/parser/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Mar 31 11:08:37 2017 Frederic ODDOU
** Last update Sun May  7 13:45:29 2017 Frederic Oddou
*/

#include <string.h>
#include <stdio.h>
#include "parser.h"

const t_parg	g_parg[] = {
  {"s", &parser_arg_s, FLAG_SINGLE, NULL},
  {"strace", &parser_arg_s, FLAG_DOUBLE, "Display the details of the\
  arguments."},
  {"c", &parser_arg_c, FLAG_SINGLE, NULL},
  {"counter", &parser_arg_s, FLAG_DOUBLE, "Display the number of time\
that a function was called."},
  {"o", &parser_arg_o, FLAG_ARG, NULL},
  {"output", &parser_arg_o, FLAG_EQUAL, "Write the trace output to the\
file filename rather than to stderr."},
  {"dotfile", &parser_arg_dot, FLAG_EQUAL, "Write the graph to the file."},
  {"t", &parser_arg_t, FLAG_SINGLE, NULL},
  {"time", &parser_arg_t, FLAG_DOUBLE, "Prefix each line of the trace\
with the time of day."},
  {"a", &parser_arg_a, FLAG_ARG, NULL},
  {"align", &parser_arg_a, FLAG_EQUAL, "Align return values in a\
specific column (default column 40)."},
  {NULL, NULL, 0, NULL},
};

static void	parser_prog(int ac, char **av, int *i, t_core *core)
{
  core->ac = ac - *i;
  core->av = &av[*i];
  *i = ac;
}

static bool	parser_display_usage(char **av)
{
  short		i;

  i = 0;
  printf("Usage: %s [<options>] [<command>]\n", av[0]);
  while (g_parg[i].flag != NULL)
    {
      if (g_parg[i].type == FLAG_SINGLE)
	printf("\t%s-%s%s", START_ARG, g_parg[i].flag, END_ARG);
      else if (g_parg[i].type == FLAG_DOUBLE)
	printf("\t%s--%s%s", START_ARG, g_parg[i].flag, END_ARG);
      else if (g_parg[i].type == FLAG_ARG)
	printf("\t%s-%s [value]%s", START_ARG, g_parg[i].flag, END_ARG);
      else if (g_parg[i].type == FLAG_EQUAL)
	printf("\t%s--%s=value%s", START_ARG, g_parg[i].flag, END_ARG);
      if (g_parg[i].describe != NULL)
	printf("\t%s\n", g_parg[i].describe);
      printf("\n");
      i++;
    }
  return (false);
}

static bool	parser_simple(int ac, char **av, int *i, t_core *core)
{
  int		fptr_i;
  int		start;

  fptr_i = 0;
  start = L_F_N_STRICT_FORMAT;
  if ((fptr_i = parser_find_argument(&av[*i][start])) != -1)
    {
      *i += 1;
      if (*i >= ac)
	return (parser_display_usage(av));
      return ((g_parg[fptr_i].func)(core, av[*i]));
    }
  else
    {
      while ((fptr_i = parser_find_single(&av[*i][start])) != -1)
	{
	  if (!((g_parg[fptr_i].func)(core, NULL)))
	    return (parser_display_usage(av));
	  start++;
	}
      if (start != L_F_N_STRICT_FORMAT)
	return (true);
    }
  return (parser_display_usage(av));
}

static bool	parser_find(int ac, char **av, int *i, t_core *core)
{
  int		fptr_i;
  int		start;

  fptr_i = 0;
  if (!strncmp(av[*i], F_STRICT_FORMAT, L_F_STRICT_FORMAT))
    {
      start = L_F_STRICT_FORMAT;
      if ((fptr_i = parser_find_double(&av[*i][start])) != -1)
	return ((g_parg[fptr_i].func)(core, NULL));
      else if ((fptr_i = parser_find_equal(&av[*i][start])) != -1)
	return ((g_parg[fptr_i].func)(core,
		 &av[*i][strlen(g_parg[fptr_i].flag) + start + 1]));
      return (parser_display_usage(av));
    }
  else if (!strncmp(av[*i], F_N_STRICT_FORMAT, L_F_N_STRICT_FORMAT))
    return (parser_simple(ac, av, i, core));
  parser_prog(ac, av, i, core);
  return (true);
}

bool		parser(int ac, char **av, t_core *core)
{
  int		i;

  i = 1;
  while (i < ac)
    {
      if (!parser_find(ac, av, &i, core))
	return (false);
      i++;
    }
  if (core->pid <= 0 && core->ac <= 0)
    return (parser_display_usage(av));
  return (true);
}
