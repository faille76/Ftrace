/*
** display_graph.c for display graph in /src/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 29 02:47:55 2017 Frederic Oddou
** Last update Sat Apr 29 07:55:44 2017 Frederic Oddou
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strace.h"

/*
** Replace . to =
*/

static void	print_string(const t_core *core, const char *name)
{
  size_t	i;

  i = 0;
  while (name[i])
    {
      if (name[i] == '.')
	fprintf(core->dot_file, "_");
      else
	fprintf(core->dot_file, "%c", name[i]);
      i++;
    }
}

/*
** We try to find if the function exist before.
*/

static bool	find_before(const t_core *core, const char *name, size_t max)
{
  size_t	n;

  n = 0;
  while (n < max && core->link && core->link[n].n1)
    {
      if (name == core->link[n].n1 || name == core->link[n].n2)
	return (true);
      n++;
    }
  return (false);
}

/*
** Writing the function prototype (color)
*/

static void	display_status(const t_core *core, const t_link *link,
			       const char *name)
{
  fprintf(core->dot_file, "\t ");
  print_string(core, name);
  fprintf(core->dot_file, " [shape=ellipse, color=");
  if (link->type == FUNC_SYMBOL)
    fprintf(core->dot_file, "blue");
  else if (link->type == FUNC_SYSCALL)
    fprintf(core->dot_file, "green");
  else
    fprintf(core->dot_file, "red");
  fprintf(core->dot_file, "];\n");
}

/*
** Writing the link
*/

void		display_link(const t_core *core)
{
  size_t	n;

  n = 0;
  fprintf(core->dot_file, "digraph callgraph\n{\n");
  while (core->link && core->link[n].n1)
    {
      if (!find_before(core, core->link[n].n1, n))
	display_status(core, &core->link[n], core->link[n].n1);
      if (!find_before(core, core->link[n].n2, n))
	display_status(core, &core->link[n], core->link[n].n2);
      fprintf(core->dot_file, "\t");
      print_string(core, core->link[n].n1);
      fprintf(core->dot_file, " -> ");
      print_string(core, core->link[n].n2);
      fprintf(core->dot_file, "[label=\"%lu\"]\n", core->link[n].nb);
      n++;
    }
  fprintf(core->dot_file, "}\n");
}
