/*
** list_errno.c for list errno in /src/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Apr  7 16:50:36 2017 Frederic Oddou
** Last update Fri Apr 28 23:37:23 2017 Frederic Oddou
*/

#include <errno.h>
#include <string.h>
#include "strace.h"

static const t_errno_type	g_errno_type[] = {
  {EPERM, "EPERM"},
  {ENOENT, "ENOENT"},
  {ESRCH, "ESRCH"},
  {EINTR, "EINTR"},
  {EIO, "EIO"},
  {ENXIO, "ENXIO"},
  {E2BIG, "E2BIG"},
  {ENOEXEC, "ENOEXEC"},
  {EBADF, "EBADF"},
  {ECHILD, "ECHILD"},
  {EAGAIN, "EAGAIN"},
  {ENOMEM, "ENOMEM"},
  {EACCES, "EACCES"},
  {EFAULT, "EFAULT"},
  {ENOTBLK, "ENOTBLK"},
  {EBUSY, "EBUSY"},
  {EEXIST, "EEXIST"},
  {EXDEV, "EXDEV"},
  {ENODEV, "ENODEV"},
  {ENOTDIR, "ENOTDIR"},
  {EISDIR, "EISDIR"},
  {EINVAL, "EINVAL"},
  {ENFILE, "ENFILE"},
  {EMFILE, "EMFILE"},
  {ENOTTY, "ENOTTY"},
  {ETXTBSY, "ETXTBSY"},
  {EFBIG, "EFBIG"},
  {ENOSPC, "ENOSPC"},
  {ESPIPE, "ESPIPE"},
  {EROFS, "EROFS"},
  {EMLINK, "EMLINK"},
  {EPIPE, "EPIPE"},
  {EDOM, "EDOM"},
  {ERANGE, "ERANGE"},
  {EDEADLK, "EDEADLK"},
  {ENAMETOOLONG, "ENAMETOOLONG"},
  {ENOLCK, "ENOLCK"},
  {ENOSYS, "ENOSYS"},
  {ENOTEMPTY, "ENOTEMPTY"},
  {ELOOP, "ELOOP"},
  {EWOULDBLOCK, "EWOULDBLOCK"},
  {ENOMSG, "ENOMSG"},
  {EIDRM, "EIDRM"},
  {ECHRNG, "ECHRNG"},
  {EL2NSYNC, "EL2NSYNC"},
  {EL3HLT, "EL3HLT"},
  {EL3RST, "EL3RST"},
  {ELNRNG, "ELNRNG"},
  {EUNATCH, "EUNATCH"},
  {ENOCSI, "ENOCSI"},
  {EL2HLT, "EL2HLT"},
  {EBADE, "EBADE"},
  {EBADR, "EBADR"},
  {EXFULL, "EXFULL"},
  {ENOANO, "ENOANO"},
  {EBADRQC, "EBADRQC"},
  {EBADSLT, "EBADSLT"},
  {EDEADLOCK, "EDEADLOCK"},
  {EBFONT, "EBFONT"},
  {ENOSTR, "ENOSTR"},
  {ENODATA, "ENODATA"},
  {ETIME, "ETIME"},
  {ENOSR, "ENOSR"},
  {ENONET, "ENONET"},
  {ENOPKG, "ENOPKG"},
  {EREMOTE, "EREMOTE"},
  {ENOLINK, "ENOLINK"},
  {EADV, "EADV"},
  {ESRMNT, "ESRMNT"},
  {ECOMM, "ECOMM"},
  {EPROTO, "EPROTO"},
  {EMULTIHOP, "EMULTIHOP"},
  {EDOTDOT, "EDOTDOT"},
  {EBADMSG, "EBADMSG"},
  {EOVERFLOW, "EOVERFLOW"},
  {ENOTUNIQ, "ENOTUNIQ"},
  {EBADFD, "EBADFD"},
  {EREMCHG, "EREMCHG"},
  {ELIBACC, "ELIBACC"},
  {ELIBBAD, "ELIBBAD"},
  {ELIBSCN, "ELIBSCN"},
  {ELIBMAX, "ELIBMAX"},
  {ELIBEXEC, "ELIBEXEC"},
  {EILSEQ, "EILSEQ"},
  {ERESTART, "ERESTART"},
  {ESTRPIPE, "ESTRPIPE"},
  {EUSERS, "EUSERS"},
  {ENOTSOCK, "ENOTSOCK"},
  {EDESTADDRREQ, "EDESTADDRREQ"},
  {EMSGSIZE, "EMSGSIZE"},
  {EPROTOTYPE, "EPROTOTYPE"},
  {ENOPROTOOPT, "ENOPROTOOPT"},
  {EPROTONOSUPPORT, "EPROTONOSUPPORT"},
  {ESOCKTNOSUPPORT, "ESOCKTNOSUPPORT"},
  {EOPNOTSUPP, "EOPNOTSUPP"},
  {EPFNOSUPPORT, "EPFNOSUPPORT"},
  {EAFNOSUPPORT, "EAFNOSUPPORT"},
  {EADDRINUSE, "EADDRINUSE"},
  {EADDRNOTAVAIL, "EADDRNOTAVAIL"},
  {ENETDOWN, "ENETDOWN"},
  {ENETUNREACH, "ENETUNREACH"},
  {ENETRESET, "ENETRESET"},
  {ECONNABORTED, "ECONNABORTED"},
  {ECONNRESET, "ECONNRESET"},
  {ENOBUFS, "ENOBUFS"},
  {EISCONN, "EISCONN"},
  {ENOTCONN, "ENOTCONN"},
  {ESHUTDOWN, "ESHUTDOWN"},
  {ETOOMANYREFS, "ETOOMANYREFS"},
  {ETIMEDOUT, "ETIMEDOUT"},
  {ECONNREFUSED, "ECONNREFUSED"},
  {EHOSTDOWN, "EHOSTDOWN"},
  {EHOSTUNREACH, "EHOSTUNREACH"},
  {EALREADY, "EALREADY"},
  {EINPROGRESS, "EINPROGRESS"},
  {ESTALE, "ESTALE"},
  {EUCLEAN, "EUCLEAN"},
  {ENOTNAM, "ENOTNAM"},
  {ENAVAIL, "ENAVAIL"},
  {EISNAM, "EISNAM"},
  {EREMOTEIO, "EREMOTEIO"},
  {EDQUOT, "EDQUOT"},
  {ENOMEDIUM, "ENOMEDIUM"},
  {EMEDIUMTYPE, "EMEDIUMTYPE"},
  {0, NULL}
};

/*
** Try to find a errno value.
** If the function doesn't find, we return NULL.
*/

static const char	*get_id_errno(int err_num)
{
  int			i;

  i = 0;
  while (g_errno_type[i].name != NULL)
    {
      if (err_num == g_errno_type[i].type)
	return (g_errno_type[i].name);
      i++;
    }
  return (NULL);
}

/*
** The function find the errno number if the return value is negative.
** If it is not an error, we write the return value.
*/

int		display_ret_value(const t_core *core, int ret)
{
  int		len;
  const char	*error_define;

  len = 0;
  if (ret < 0)
    {
      ret = -(ret);
      error_define = get_id_errno(ret);
      if (error_define == NULL)
	len += fprintf(core->fd, "-%d", -ret);
      else
	len += fprintf(core->fd, "-1 %s (%s)", error_define, strerror(ret));
    }
  else
    len += fprintf(core->fd, "%d", ret);
  return (len);
}
