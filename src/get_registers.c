/*
** get_registers.c for get registers in /src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun Apr  2 14:44:40 2017 Frederic ODDOU
** Last update Sun Apr  2 14:44:40 2017 Frederic ODDOU
*/

#include <sys/user.h>
#include <sys/reg.h>
#include "strace.h"

/*
** Return the parameters or return value for the x86_64 arch.
*/

long long		get_registers(const t_registers *regs,
				      int i)
{
  if (i == -1)
    return (regs->rax);
  else if (i == 0)
    return (regs->rdi);
  else if (i == 1)
    return (regs->rsi);
  else if (i == 2)
    return (regs->rdx);
  else if (i == 3)
    return (regs->r10);
  else if (i == 4)
    return (regs->r8);
  else if (i == 5)
    return (regs->r9);
  return (0);
}
