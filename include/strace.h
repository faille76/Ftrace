/*
** strace.h for strace in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Mar 31 10:51:23 2017 Frederic ODDOU
** Last update Sun May  7 14:31:12 2017 Frederic Oddou
*/

#pragma once

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/user.h>
#include <elf.h>

#define TYPE_END -1
#define GET_SIZE(x) 	(sizeof(x) / sizeof(*x))
#define BUFFER_SIZE	4096

#define GET_SYMTAB(var)	(Elf64_Sym *)((char *)core->elf.ehdr	\
				      + var->sh_offset)
#define GET_STRTAB(var)	(char *)core->elf.ehdr	\
  + core->elf.shdr[var->sh_link].sh_offset;
#define SIZE_SYM(var)	(var->sh_size / sizeof(Elf64_Sym))

enum e_type_func
{
  FUNC_SYSCALL,
  FUNC_SYMBOL,
  FUNC_DYN,
};

enum e_option
{
  OPT_IS_TRUE,
  OPT_TIME,
  OPT_COUNTER,
  OPT_DOTFILE,
  OPT_END,
};

typedef struct		s_call_func
{
  long			value;
  const char		*name;
  int			nb_call;
}			t_call_func;

typedef struct		s_stackpointer
{
  unsigned long long	ptr_stack;
  unsigned long long	value;
  const char		*func;
}			t_stackpointer;

typedef struct		s_link
{
  const char		*n1;
  const char		*n2;
  size_t		nb;
  enum e_type_func	type;
}			t_link;

typedef struct		s_errno_type
{
  int			type;
  const char		*name;
}			t_errno_type;

typedef struct		s_elf_value
{
  unsigned long		value;
  char			*name;
}			t_elf_value;

typedef struct		s_elf
{
  Elf64_Ehdr		*ehdr;
  Elf64_Shdr		*shdr;
  Elf64_Shdr		*symshdr;
  Elf64_Shdr		*dynshdr;
  Elf64_Addr		pltaddr;
  t_elf_value		*symval;
  t_elf_value		*dynval;
  off_t			size;
}			t_elf;

typedef struct		s_core
{
  FILE			*fd;
  FILE			*dot_file;
  pid_t			pid;
  bool			options[OPT_END];
  int			padding;
  int			ac;
  char			**av;
  char			bin_path[BUFFER_SIZE];
  t_elf			elf;
  t_stackpointer	*stack_ptr;
  t_call_func		*call_func;
  t_link		*link;
}			t_core;

typedef struct		s_list_functions
{
  unsigned long long	id;
  const char		*name;
  int			(*type)(t_core *core, long long value);
  int			nb_arg;
  int			(*param[6])(t_core *core, long long value);
}			t_list_functions;

typedef struct user_regs_struct t_registers;

typedef struct		s_flag
{
  int			flag;
  const char		*name;
}			t_flag;

/*
** @get_path.c
** Get the path from the path environment.
*/

bool		get_binary_path(t_core *core, const char *bin);

/*
** Folder elf
*/

bool		elf_open_file(t_core *core);

/*
** exec_strace.c
*/

bool		exec_strace(t_core *core);

/*
** display_function.c
*/

void		display_function_strace(t_core *core,
					t_registers *regs,
					t_registers *regs_return);

/*
** @get_registers.c
** Get the parameters and return value for the actual architecture.
*/

long long	get_registers(const t_registers *regs,
			      int i);

/*
** Folder print
*/

int		print_char_pointer(t_core *core, long long value);
int		print_pointer(t_core *core, long long value);
int		print_base8(t_core *core, long long nb);
int		print_number(t_core *core, long long value);
int		print_time(t_core *core, long long len);
int		print_equal(t_core *core, long long value);
int		print_struct_stat(t_core *core, long long value);
int		print_flags_open(t_core *core, long long value);
int		print_flags_access(t_core *core, long long value);
int		print_flags_arch_prctl(t_core *core, long long value);
int		print_flags_lseek(t_core *core, long long value);
int		print_flags_mprotect(t_core *core, long long value);
int		print_flags_mmap_prot(t_core *core, long long value);
int		print_flags_mmap(t_core *core, long long value);
int		print_flags_socket_type(t_core *core, long long value);
int		print_flags_socket_domain(t_core *core, long long value);

/*
** @func_syscall.c
** After the syscall found, we can display the arguments and return value.
** The function can also execute the features.
*/

int		exec_function_strace(t_core *core,
				     int id_func,
				     const t_registers *regs,
				     const t_registers *regs_return);

/*
** @stack_ptr.c
** After each call of function, we add an element in order to create a tree.
** We could know the ptr on the stack.
*/

t_stackpointer	*get_last_stack_ptr(const t_core *core, int c);
void		delete_stack_ptr(t_core *core);
bool		add_stack_ptr(t_core *core,
			      unsigned long long ptr_stack,
			      unsigned long long value,
			      const char *func);

/*
** @list_functions.c
** Contains the syscall array.
** Function to find the id if the syscall exist.
*/

extern const t_list_functions g_list_functions[];
int		get_rax_strace(unsigned long long rax);
bool		get_name_strace(const char *func);

/*
** @list_errno.c
** Contains the array of every errno define.
** Print the return value and the error message if errno is set.
*/

int		display_ret_value(const t_core *core, int ret);

/*
** @call_function.c
** After each call of function, we add an element on the list call_func.
** This feature calcul the number of time that a function is called.
*/

void		show_call_func(const t_core *core);
bool		add_nb_call_func(t_core *core, long value, const char *name);

/*
** @link.c
** This feature add every link knowing in order to create a big binary tree.
*/

bool		add_to_link(t_core *core, const char *n1, const char *n2,
			    enum e_type_func type);

/*
** @display_graph.c
** We write on a file in order to create a .dot file.
*/

void		display_link(const t_core *core);

/*
** @display_signal.c
** If we got a signal number, we print the name from the signal list.
*/

void		display_signal(const t_core *core, int signal);
