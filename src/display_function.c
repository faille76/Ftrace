/*
** display_function.c for display in /src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun Apr  2 14:33:31 2017 Frederic ODDOU
** Last update Sun May  7 13:43:20 2017 Frederic Oddou
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <string.h>
#include <sys/reg.h>
#include "strace.h"

static void		entering_function(t_core *core,
					  unsigned long long stack_ptr,
					  t_elf_value *val,
					  enum e_type_func type)
{
  t_stackpointer	*ptr;

  if (core->options[OPT_DOTFILE] &&
      (ptr = get_last_stack_ptr(core, 0)) != NULL)
    add_to_link(core, ptr->func, val->name, type);
  if (core->options[OPT_COUNTER])
    add_nb_call_func(core, val->value, val->name);
  add_stack_ptr(core, stack_ptr, val->value, val->name);
  if (core->options[OPT_TIME])
    print_time(core, 0);
  fprintf(core->fd, "Entering function %s at 0x%lx\n", val->name, val->value);
}

static bool	display_dynamic_function_strace(t_core *core,
						t_registers *regs,
						unsigned long long stack_ptr)
{
  int		i;

  i = 0;
  while (core->elf.dynval && core->elf.dynval[i].name != NULL)
    {
      if (core->elf.dynval[i].value == regs->rip &&
	  !get_name_strace(core->elf.dynval[i].name))
	{
	  entering_function(core, stack_ptr, &core->elf.dynval[i], FUNC_DYN);
	  return (true);
	}
      i++;
    }
  return (false);
}

static bool	display_symbol_function_strace(t_core *core,
					       t_registers *regs,
					       unsigned long long stack_ptr)
{
  int		i;

  i = 0;
  while (core->elf.symval && core->elf.symval[i].name != NULL)
    {
      if (core->elf.symval[i].value == regs->rip &&
	  !get_name_strace(core->elf.symval[i].name))
	{
	  entering_function(core, stack_ptr, &core->elf.symval[i],
			    FUNC_SYMBOL);
      	  return (true);
	}
      i++;
    }
  return (false);
}

static void		display_intern_function_strace(t_core *core,
						       t_registers *regs,
						       unsigned long long
						       stack_ptr)
{
  t_stackpointer	*ptr;

  if (!display_dynamic_function_strace(core, regs, stack_ptr) &&
      !display_symbol_function_strace(core, regs, stack_ptr))
    {
      if ((ptr = get_last_stack_ptr(core, 0)) != NULL &&
	  ptr->ptr_stack == stack_ptr)
	{
	  if (core->options[OPT_TIME])
	    print_time(core, 0);
	  fprintf(core->fd, "Leaving function %s at 0x%llx\n",
		  ptr->func, ptr->value);
	  delete_stack_ptr(core);
	}
    }
}

void			display_function_strace(t_core *core,
						t_registers *regs,
						t_registers *regs_return)
{
  int			id_func;
  unsigned long long	instruction;

  if ((id_func = get_rax_strace(regs->orig_rax)) != TYPE_END)
    exec_function_strace(core, id_func, regs, regs_return);
  else
    {
      instruction = ptrace(PTRACE_PEEKTEXT, core->pid, regs->rsp, 0);
      display_intern_function_strace(core, regs, instruction);
    }
}
