/*
** func_syscall.c for syscall in /src/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 21 09:51:16 2017 Frederic Oddou
** Last update Sun May  7 14:36:57 2017 Frederic Oddou
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <string.h>
#include <sys/reg.h>
#include "strace.h"

static void			utils_syscall(t_core *core, int id_func)
{
  t_stackpointer		*ptr;

  if (core->options[OPT_DOTFILE] &&
      (ptr = get_last_stack_ptr(core, 0)) != NULL)
    add_to_link(core, ptr->func, g_list_functions[id_func].name, FUNC_SYSCALL);
  if (core->options[OPT_COUNTER])
    add_nb_call_func(core, id_func, g_list_functions[id_func].name);
}

static int			print_arguments(t_core *core,
						const t_registers *regs,
						int id_func)
{
  int				len;
  int				i;

  i = len = 0;
  if (core->options[OPT_TIME])
    len += print_time(core, len);
  len += fprintf(core->fd, "Syscall %s(", g_list_functions[id_func].name);
  while (i < g_list_functions[id_func].nb_arg)
    {
      if (i > 0)
	len += fprintf(core->fd, ", ");
      if (core->options[OPT_IS_TRUE])
	{
	  if (g_list_functions[id_func].param[i] != NULL)
	    len += (g_list_functions[id_func].param[i])(core,
		    get_registers(regs, i));
	}
      else
	len += fprintf(core->fd, "0x%llx", get_registers(regs, i));
      i++;
    }
  len += fprintf(core->fd, ")");
  return (len);
}

int		exec_function_strace(t_core *core,
				     int id_func,
				     const t_registers *regs,
				     const t_registers *regs_return)
{
  long long	ret;
  int		len;

  ret = get_registers(regs_return, -1);
  utils_syscall(core, id_func);
  len = print_arguments(core, regs, id_func);
  len += print_equal(core, len);
  if (core->options[OPT_IS_TRUE])
    {
      if (ret >= 0)
      {
	if (g_list_functions[id_func].type != NULL)
	  len += (g_list_functions[id_func].type)(core, ret);
      }
      else
	len += display_ret_value(core, ret);
    }
  else
    len += fprintf(core->fd, "0x%llx", ret);
  len += fprintf(core->fd, "\n");
  return (len);
}
