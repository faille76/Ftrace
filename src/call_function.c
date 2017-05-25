/*
** call_function.c for call function in /src/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 28 19:45:46 2017 Frederic Oddou
** Last update Fri Apr 28 23:39:51 2017 Frederic Oddou
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "strace.h"

/*
** Counting every functions called at least once.
*/

static size_t	count_call_func(const t_call_func *func)
{
  size_t	n;

  n = 0;
  while (func != NULL && func[n].name != NULL)
    n++;
  return (n);
}

/*
** If the function called doesn't exist on the list, the function add it.
** We set at 1 by default.
*/

static bool	add_call_func(t_core *core,
			      long value,
			      const char *name)
{
  size_t	n;

  n = count_call_func(core->call_func);
  if ((core->call_func = realloc(core->call_func,
				 sizeof(t_call_func) * (n + 2))) == NULL)
    return (false);
  core->call_func[n].value = value;
  core->call_func[n].name = name;
  core->call_func[n].nb_call = 1;
  memset(&core->call_func[n + 1], 0, sizeof(t_call_func));
  return (true);
}

/*
** If the function exists on the list, we add one call. Else, we create.
*/

bool		add_nb_call_func(t_core *core, long value, const char *name)
{
  size_t	n;

  n = 0;
  while (core->call_func != NULL && core->call_func[n].name != NULL)
    {
      if (core->call_func[n].value == value)
	{
	  core->call_func[n].nb_call += 1;
	  return (true);
	}
      n++;
    }
  return (add_call_func(core, value, name));
}

/*
** Displays every function called once from the list.
*/

void		show_call_func(const t_core *core)
{
  size_t	n;

  n = 0;
  if (core->call_func == NULL)
    {
      fprintf(core->fd, "No function called.\n");
      return ;
    }
  fprintf(core->fd, "Resume functions called:\n");
  while (core->call_func[n].name != NULL)
    {
      fprintf(core->fd, "[0x%lx][%s] -> %d\n", core->call_func[n].value,
	      core->call_func[n].name, core->call_func[n].nb_call);
      n++;
    }
}
