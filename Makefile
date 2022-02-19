CC			= gcc
CFLAGS		= -g3 -Wall -Wextra -Werror
RM			= rm -f
SRCD		= ./srcs/
SRC			=  main.c ft_lexor.c ft_parser.c ft_executor.c ft_initiator.c ft_echo_utils.c ft_builtins2.c ft_builtins.c ft_globlal_fun.c \
				ft_builtins_utils.c ft_cd_utils.c ft_lexor_utils.c ft_lexor_utils2.c ft_lexor_handlers.c ft_parser_utils.c utils.c \
				ft_free_linked_list.c ft_exit_utils.c ft_export_utils.c get_next_line.c get_next_line_utils.c ft_init_utils.c \
				pipex.c helper.c exit_handler.c ft_heredoc.c ft_signal_handler.c ft_get_path_mac.c #ft_get_path_linux.c

# Command to add the source folder prefix (instead of having it added manually to SRC)
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD		= $(OBJF:$(OBJD)%.o)

NAME		= minishell
HEADD		= ./incl/
HEADF		= minishell.h

LIBFTD		= ./libft/
LIBFT_OBJD	= objs
LIBFT_SRCD	= srcs/
LIBFTL		= libft.a

LIBFT_OBJF    = ${LIBFTD}${LIBFT_OBJD}/*.o
LIBFT_MAKE    = make -C ${LIBFTD}

#if to the respective c file in the source directory no matching o file in the object
#directory is available, then create it according to the following rules:
#Note: the object directory will only be created if not existing already. -p flag throws no errors when already there
$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

# $(NAME):	${OBJF}
# 			make libftmake
# 			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) $(HEADD)$(HEADF) $(LIBFTD)$(LIBFTL)
$(NAME):	${OBJF}
			make libftmake
			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) -L $(HEADD) $(LIBFTD)$(LIBFTL) -L /usr/local/lib -I /usr/local/include -lreadline


all:		${NAME}

libftmake:
			${LIBFT_MAKE}

clean:
			${RM} ${OBJD}*.o
			make -C ${LIBFTD} clean

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFTD}${LIBFTL}
			@${RM} ${HEADD}minishell.h.gch
			@${RM} ${HEADD}minishe11.h.gch
			@rm -rf minishell.dSYM

re:			fclean all

.PHONY:		all clean fclean re