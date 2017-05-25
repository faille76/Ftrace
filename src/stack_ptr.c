/*
** stack_ptr.c for stack ptr in /src/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 21 10:19:33 2017 Frederic Oddou
** Last update Sat Apr 29 01:30:47 2017 Frederic Oddou
*/

#include <stdlib.h>
#include <string.h>
#include "strace.h"

/*
** Count all stack ptr actually in the list.
*/

static size_t	count_stack_ptr(const t_core *core)
{
  size_t	i;

  i = 0;
  while (core->stack_ptr && core->stack_ptr[i].value > 0)
    i++;
  return (i);
}

/*
** Adding at the end of the list the informations of the last stackptr.
*/

bool		add_stack_ptr(t_core *core,
			      unsigned long long ptr_stack,
			      unsigned long long value,
			      const char *func)
{
  int		len;

  len = count_stack_ptr(core);
  if ((core->stack_ptr = realloc(core->stack_ptr,
				 sizeof(t_stackpointer) * (len + 2))) == NULL)
    return (false);
  core->stack_ptr[len].ptr_stack = ptr_stack;
  core->stack_ptr[len].value = value;
  core->stack_ptr[len].func = func;
  memset(&core->stack_ptr[len + 1], 0, sizeof(t_stackpointer));
  return (true);
}

/*
** Delete the last element on the stack.
*/

void		delete_stack_ptr(t_core *core)
{
  int		len;

  if (!core->stack_ptr)
    return ;
  len = count_stack_ptr(core) - 1;
  memset(&core->stack_ptr[len], 0, sizeof(t_stackpointer));
}

/*
** Get the informations of the last ptr added.
*/

t_stackpointer		*get_last_stack_ptr(const t_core *core, int c)
{
  long			i;

  if (!core->stack_ptr)
    return (NULL);
  i = count_stack_ptr(core) - (c + 1);
  if (i >= 0)
    return (&core->stack_ptr[i]);
  return (NULL);
}
