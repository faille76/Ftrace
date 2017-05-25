##
## Makefile for make in /
##
## Made by Fredoddou
## Login   <fredoddou>
##
## Started on  Fri Mar 31 10:32:15 2017 Fredoddou
## Last update Fri Apr  7 16:54:11 2017 Frederic Oddou
##

ECHO	=	/bin/echo -e
DEFAULT	=	"\033[00m"
GREEN	=	"\033[0;32m"
TEAL	=	"\033[1;36m"
RED	=	"\033[0;31m"
BLUE	=	"\033[0;34m"

DIR_INC =	./include/
DIR_SRC =	./src/
DIR_PARSER =	$(DIR_SRC)parser/
DIR_PRINT =	$(DIR_SRC)print/
DIR_FUNC =	$(DIR_SRC)function/
DIR_ELF =	$(DIR_SRC)elf/

SRC 	=	$(DIR_SRC)main.c \
		$(DIR_PARSER)parser.c \
		$(DIR_PARSER)parser_types.c \
		$(DIR_PARSER)parser_arg_o.c \
		$(DIR_PARSER)parser_arg_a.c \
		$(DIR_PARSER)parser_arg_t.c \
		$(DIR_PARSER)parser_arg_s.c \
		$(DIR_PARSER)parser_arg_c.c \
		$(DIR_PARSER)parser_arg_dot.c \
		$(DIR_SRC)list_errno.c \
		$(DIR_SRC)get_path.c \
		$(DIR_SRC)call_function.c \
		$(DIR_SRC)exec_strace.c \
		$(DIR_SRC)get_registers.c \
		$(DIR_SRC)display_function.c \
		$(DIR_SRC)list_functions.c \
		$(DIR_SRC)func_syscall.c \
		$(DIR_SRC)stack_ptr.c \
		$(DIR_SRC)link.c \
		$(DIR_SRC)display_graph.c \
		$(DIR_SRC)display_signal.c \
		$(DIR_PRINT)print_char_pointer.c \
		$(DIR_PRINT)print_pointer.c \
		$(DIR_PRINT)print_base8.c \
		$(DIR_PRINT)print_number.c \
		$(DIR_PRINT)print_equal.c \
		$(DIR_PRINT)print_time.c \
		$(DIR_PRINT)print_flags_open.c \
		$(DIR_PRINT)print_flags_access.c \
		$(DIR_PRINT)print_flags_lseek.c \
		$(DIR_PRINT)print_flags_mmap.c \
		$(DIR_PRINT)print_flags_socket.c \
		$(DIR_PRINT)print_flags_mprotect.c \
		$(DIR_PRINT)print_flags_arch_prctl.c \
		$(DIR_PRINT)print_struct_stat.c \
		$(DIR_ELF)elf_open_file.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc -g

RM	=	rm -f

CFLAGS	+=	-Wextra \
		-Wall \
		-Werror \
		-I$(DIR_INC)

LDFLAGS	=

NAME	=	./ftrace

$(NAME):	$(OBJ)
		@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

all:		$(NAME)

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		$(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
		$(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

.PHONY:		all clean fclean re $(NAME) .c.o
