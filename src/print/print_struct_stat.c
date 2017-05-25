/*
** print_struct_stat.c for struct stat in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 15 17:30:58 2017 Frederic Oddou
** Last update Sat Apr 15 17:46:13 2017 Frederic Oddou
*/

#include <sys/stat.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <string.h>
#include "strace.h"

static void			fill_struct(t_core *core,
					    long long value,
					    unsigned int size,
					    void *var)
{
  unsigned int			i;
  long long			ret;

  i = 0;
  while (i < size)
    {
      if ((ret = ptrace(PTRACE_PEEKDATA, core->pid, value + i, 0)) == -1)
	return ;
      memcpy(var + i, &ret,
	     size < sizeof(unsigned long) ? size : sizeof(unsigned long));
      i += sizeof(unsigned long);
    }
}

int				print_struct_stat(t_core *core,
						  long long value)
{
  struct stat			var;
  int				len;

  memset(&var, 0, sizeof(var));
  fill_struct(core, value, sizeof(var), &var);
  len = fprintf(core->fd, "{st_mode=%u, st_size=%ld, ...}",
		var.st_mode, var.st_size);
  return (len);
}
