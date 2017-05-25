/*
** print_flags_open.c for flags open in /src/print/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr 28 17:03:38 2017 Frederic Oddou
** Last update Fri Apr 28 18:19:43 2017 Frederic Oddou
*/

#include <stdio.h>
#include <sys/socket.h>
#include "strace.h"

static t_flag	g_list_flags_domain[] = {
  {AF_UNIX, "AF_UNIX"},
  {AF_LOCAL, "AF_LOCAL"},
  {AF_INET, "AF_INET"},
  {AF_INET6, "AF_INET6"},
  {AF_IPX, "AF_IPX"},
  {AF_NETLINK, "AF_NETLINK"},
  {AF_X25, "AF_X25"},
  {AF_AX25, "AF_AX25"},
  {AF_ATMPVC, "AF_ATMPVC"},
  {AF_APPLETALK, "AF_APPLETALK"},
  {AF_PACKET, "AF_PACKET"},
  {0, NULL}
};

static t_flag	g_list_flags_type[] = {
  {SOCK_STREAM, "SOCK_STREAM"},
  {SOCK_CLOEXEC, "SOCK_CLOEXEC"},
  {SOCK_DGRAM, "SOCK_DGRAM"},
  {SOCK_RDM, "SOCK_RDM"},
  {SOCK_PACKET, "SOCK_PACKET"},
  {SOCK_NONBLOCK, "SOCK_NONBLOCK"},
  {0, NULL}
};

int		print_flags_socket_domain(t_core *core, long long value)
{
  int		i;
  int		len;
  int		display;

  i = display = len = 0;
  while (g_list_flags_domain[i].name != NULL)
    {
      if (value == g_list_flags_domain[i].flag)
	{
	  if (display)
	    len += fprintf(core->fd, "|");
	  len += fprintf(core->fd, "%s", g_list_flags_domain[i].name);
	  display++;
	  break ;
	}
      i++;
    }
  return (len);
}

int		print_flags_socket_type(t_core *core, long long value)
{
  int		i;
  int		len;
  int		display;

  i = display = len = 0;
  while (g_list_flags_type[i].name != NULL)
    {
      if (value & g_list_flags_type[i].flag)
	{
	  if (display)
	    len += fprintf(core->fd, "|");
	  len += fprintf(core->fd, "%s", g_list_flags_type[i].name);
	  display++;
	}
      i++;
    }
  return (len);
}
