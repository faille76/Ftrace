/*
** link.c for link in /home/fredoddou/Documents/Epitech/B4-Unix-System-Programming/PSU_2016_ftrace/src/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 28 20:31:15 2017 Frederic Oddou
** Last update Sat Apr 29 02:51:12 2017 Frederic Oddou
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strace.h"

/*
** Counting the number of element on the link list.
*/

static size_t	count_link(const t_link *link)
{
  size_t	n;

  n = 0;
  while (link != NULL && link[n].n1)
    n++;
  return (n);
}

/*
** Adding an element on the link list.
*/

static bool	add_link(t_core *core, const char *n1, const char *n2,
			 enum e_type_func type)
{
  size_t	n;

  n = count_link(core->link);
  if ((core->link = realloc(core->link,
			    sizeof(t_link) * (n + 2))) == NULL)
    return (false);
  core->link[n].n1 = n1;
  core->link[n].n2 = n2;
  core->link[n].nb = 1;
  core->link[n].type = type;
  memset(&core->link[n + 1], 0, sizeof(t_call_func));
  return (true);
}

/*
** Try to find a link on the list.
** If v1 -> v2 is found, the function return the element.
** We don't try to find v2 -> v1.
*/

static t_link	*if_exist_link(const t_core *core,
			       const char *n1,
			       const char *n2)
{
  size_t	n;

  n = 0;
  while (core->link && core->link[n].n1)
    {
      if (core->link[n].n1 == n1 && core->link[n].n2 == n2)
	return (&core->link[n]);
      n++;
    }
  return (NULL);
}

/*
** If a link is not find on the list, we add it.
*/

bool		add_to_link(t_core *core, const char *n1, const char *n2,
			    enum e_type_func type)
{
  t_link	*ptr;

  if (!(ptr = if_exist_link(core, n1, n2)))
    {
      add_link(core, n1, n2, type);
      return (true);
    }
  ptr->nb += 1;
  return (false);
}
