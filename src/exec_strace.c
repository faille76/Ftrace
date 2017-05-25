/*
** exec_strace.c for exec in /src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Mar 31 12:15:43 2017 Frederic ODDOU
** Last update Fri Apr  7 00:04:20 2017 Frederic Oddou
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "strace.h"

/*
** After creating the son, we transfer the output to null in order to not see.
** We execute the program after said that we allow the tracing.
*/

static void			exec_son_strace(t_core *core)
{
  int				fd;

  if ((fd = open("/dev/null", O_WRONLY)) == -1)
    exit(EXIT_FAILURE);
  if (dup2(fd, STDOUT_FILENO) == -1 || dup2(fd, STDERR_FILENO) == -1)
    exit(EXIT_FAILURE);
  if (ptrace(PTRACE_TRACEME, core->pid, 0, 0) == -1)
    {
      perror("ptrace failed.\n");
      exit(EXIT_FAILURE);
    }
  if (execvp(core->bin_path, core->av) < 0)
    {
      perror("execvp failed.\n");
      exit(EXIT_FAILURE);
    }
  exit(EXIT_FAILURE);
}

/*
** Execute step by step the program and check the signals.
*/

static int			exec_father_strace(t_core *core)
{
  int				status;
  int				ret;
  struct user_regs_struct	regs;
  struct user_regs_struct	regs_return;

  waitpid(core->pid, &status, 0);
  ret = EXIT_FAILURE;
  while (WIFSTOPPED(status))
    {
      if (ptrace(PTRACE_GETREGS, core->pid, 0, &regs) == -1)
	return (ret);
      if (ptrace(PTRACE_SINGLESTEP, core->pid, NULL, NULL) == -1)
      	return (ret);
      waitpid(core->pid, &status, WCONTINUED);
      if (WIFSTOPPED(status) && (WSTOPSIG(status) != SIGTRAP))
	display_signal(core, status);
      ret = WEXITSTATUS(status);
      if (ptrace(PTRACE_GETREGS, core->pid, 0, &regs_return) == -1)
	return (ret);
      display_function_strace(core, &regs, &regs_return);
    }
  return (ret);
}

/*
** Create the son or attach an exist process.
*/

bool		exec_strace(t_core *core)
{
  int		ret_value;

  if ((core->pid = fork()) < 0)
    {
      perror("fork failed.\n");
      return (false);
    }
  else if (core->pid == 0)
    exec_son_strace(core);
  if ((ret_value = exec_father_strace(core)) != -1)
    fprintf(core->fd, "+++ exited with %d +++\n", (unsigned char)ret_value);
  return (ret_value);
}
