/*
** main.c for main in /src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Mar 31 12:03:48 2017 Frederic ODDOU
** Last update Tue Apr 18 21:55:10 2017 Frederic Oddou
*/

#include <string.h>
#include <stdlib.h>
#include "strace.h"
#include "parser.h"

static void	init_strace(t_core *core)
{
  memset(core, 0, sizeof(t_core));
  core->fd = stderr;
  core->padding = 40;
}

static void	destruct_strace(t_core *core)
{
  if (core->dot_file != NULL)
    {
      display_link(core);
      fclose(core->dot_file);
    }
  free(core->elf.ehdr);
  free(core->elf.dynval);
  free(core->elf.symval);
  free(core->stack_ptr);
  free(core->call_func);
  free(core->link);
  if (core->fd != stderr && core->fd != NULL)
    fclose(core->fd);
}

int		main(int ac, char **av)
{
  t_core	core;

  init_strace(&core);
  if (!parser(ac, av, &core))
    return (EXIT_FAILURE);
  if (!get_binary_path(&core, core.av[0]))
    {
      fprintf(stderr, "%s doesn't found.\n", core.av[0]);
      return (EXIT_FAILURE);
    }
  if (!elf_open_file(&core))
    {
      fprintf(stderr, "%s is not a good file.\n", core.av[0]);
      return (EXIT_FAILURE);
    }
  exec_strace(&core);
  if (core.options[OPT_COUNTER])
    show_call_func(&core);
  destruct_strace(&core);
  return (EXIT_SUCCESS);
}
