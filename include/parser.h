/*
** parser.h for parser in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Fri Mar 31 10:53:18 2017 Frederic ODDOU
** Last update Mon Apr 10 17:49:47 2017 Frederic Oddou
*/

#pragma once

#include <stdbool.h>
#include "strace.h"

/*
** SINGLE : -a
** DOUBLE : --argument
** ARG : -a value
** EQUAL : --argument=value
*/

#define F_N_STRICT_FORMAT	"-"
#define F_STRICT_FORMAT		"--"
#define L_F_N_STRICT_FORMAT	strlen(F_N_STRICT_FORMAT)
#define L_F_STRICT_FORMAT	strlen(F_STRICT_FORMAT)

#define START_ARG	"\t\033[31m"
#define END_ARG		"\033[0m"

enum			e_flags_strict
  {
    FLAG_SINGLE,
    FLAG_DOUBLE,
    FLAG_ARG,
    FLAG_EQUAL,
  };

typedef struct		s_parg
{
  char			*flag;
  bool			(*func)(t_core *core, char *str);
  enum e_flags_strict	type;
  char			*describe;
}			t_parg;

/*
** @parser.c
** Give all elements from the main function in order to fill the core struct.
*/

bool		parser(int ac, char **av, t_core *core);

/*
** Functions for each argument
*/

bool		parser_arg_o(t_core *core, char *str);
bool		parser_arg_a(t_core *core, char *str);
bool		parser_arg_s(t_core *core, char *str);
bool		parser_arg_t(t_core *core, char *str);
bool		parser_arg_c(t_core *core, char *str);
bool		parser_arg_dot(t_core *core, char *str);

/*
** @parser_types.c
*/
int		parser_find_single(char *str);
int		parser_find_argument(char *str);
int		parser_find_equal(char *str);
int		parser_find_double(char *str);

extern const t_parg	g_parg[];
