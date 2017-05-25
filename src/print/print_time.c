/*
** print_time.c for print time in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr  8 10:07:40 2017 Frederic Oddou
** Last update Sat Apr 29 00:47:41 2017 Frederic Oddou
*/

#include <time.h>
#include <stdio.h>
#include "strace.h"

int			print_time(t_core *core,
				   long long len)
{
  struct tm		*now_time;
  time_t		now;

  now = 0;
  time(&now);
  if ((now_time = localtime(&now)) != NULL)
    {
      len += fprintf(core->fd, "%02d:%02d:%02d ", now_time->tm_hour,
		     now_time->tm_min, now_time->tm_sec);
    }
  return (len);
}
