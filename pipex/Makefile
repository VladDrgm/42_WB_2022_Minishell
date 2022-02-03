# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 22:16:45 by mamuller          #+#    #+#              #
#    Updated: 2021/11/15 22:16:45 by mamuller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
#CFLAGS		= -Wall -Wextra -Werror
CFLAGS		= 
RM			= rm -f
SRCD		= ./srcs/
SRC			= pipex.c helper.c test.c exit_handler.c
# Command to add the source folder prefix (instead of having it added manually to SRC)
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD		= $(OBJF:$(OBJD)%.o)

NAME		= pipex
HEADD		= ./incl/
HEADF		= pipex.h

LIBFTD		= ./libft/
LIBFT_OBJD	= objs
LIBFT_SRCD	= srcs/
LIBFTL		= libft.a
LIBFT_MAKE    = make -C ${LIBFTD}

#if to the respective c file in the source directory no matching o file in the object
#directory is available, then create it according to the following rules:
#Note: the object directory will only be created if not existing already. -p flag throws no errors when already there
$(OBJD)%.o: $(SRCD)%.c 
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

$(NAME):	${OBJF}
			make libftmake
			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) $(HEADD)$(HEADF) $(LIBFTD)$(LIBFTL) -L /usr/local/lib -I /usr/local/include -lreadline


all:		${NAME}

libftmake:
			${LIBFT_MAKE}

clean:		
			${RM} ${OBJF}
			make -C ${LIBFTD} clean

fclean:		clean
			${RM} ${NAME}
			${RM} ${HEADD}pipex.h.gch
			make -C ${LIBFTD} fclean

re:			fclean all

.PHONY:		all clean fclean re