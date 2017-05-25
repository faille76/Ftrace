/*
** get_path.c for get path in /src/
**
** Made by Frederic Oddou
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Tue Apr 11 13:54:03 2017 Frederic Oddou
** Last update Sun May  7 14:41:05 2017 Frederic Oddou
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "strace.h"

/*
** Try to find if the path given exists.
*/

static bool	is_match(const char *bin_path)
{
  if (!access(bin_path, R_OK | F_OK | X_OK))
    return (true);
  return (false);
}

/*
** Separate the PATH from the environment and try every combinaison.
*/

static bool	find_good_path(t_core *core, char *env_path, const char *bin)
{
  char		*token;

  token = strtok(env_path, ":");
  while (token != NULL)
    {
      bzero(core->bin_path, BUFFER_SIZE);
      strncpy(core->bin_path, token, BUFFER_SIZE);
      strncat(core->bin_path, "/", BUFFER_SIZE);
      strncat(core->bin_path, bin, BUFFER_SIZE);
      core->bin_path[BUFFER_SIZE - 1] = '\0';
      if (is_match(core->bin_path))
	return (true);
      token = strtok(NULL, ":");
    }
  return (false);
}

/*
** Main function to find the good path.
*/

bool		get_binary_path(t_core *core, const char *bin)
{
  char		*env_path;

  bzero(core->bin_path, BUFFER_SIZE);
  if (bin == NULL)
    return (NULL);
  if (!strncmp(bin, "/", 1) || strstr(bin, "/") || strstr(bin, "./"))
    {
      strncpy(core->bin_path, bin, BUFFER_SIZE);
      core->bin_path[BUFFER_SIZE - 1] = '\0';
      return (is_match(core->bin_path));
    }
  else if (!strchr(bin, '/'))
    {
      if ((env_path = getenv("PATH")) == NULL)
	return (NULL);
      return (find_good_path(core, env_path, bin));
    }
  return (false);
}
