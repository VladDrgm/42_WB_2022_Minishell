CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
SRCD		= ./srcs/
SRC			= ft_itoa.c ft_split.c ft_strtrim.c ft_memccpy.c ft_strdup.c ft_substr.c ft_strchr.c \
			ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strrchr.c ft_tolower.c \
			ft_toupper.c ft_calloc.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
			ft_memcmp.c ft_memmove.c ft_memset.c ft_strlcpy.c ft_isalpha.c ft_strnstr.c ft_bzero.c ft_atoi.c \
			ft_memcpy.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_lstdelone.c \
			ft_lstadd_front.c ft_lstnew.c ft_lstlast.c ft_lstsize.c ft_lstclear.c ft_lstadd_back.c \
			ft_lstiter.c ft_lstmap.c
# Command to add the source folder prefix (instead of having it added manually to SRC)
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF 		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD 		= $(OBJF:$(OBJD)%.o)

NAME		= libft.a
HEADD		= ./incl/
HEADF		= libft.h


#if to the respective c file in the source directory no matching o file in the object
#directory is available, then create it according to the following rules:
#Note: the object directory will only be created if not existing already. -p flag throws no errors when already there
$(OBJD)%.o: $(SRCD)%.c 
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

$(NAME):	${OBJF}
			ar rcs ${NAME} ${OBJF}


all:		${NAME}


clean:		
			${RM} ${OBJF}

fclean:		clean
			${RM} ${NAME}
			${RM} a.out

re:			fclean all

.PHONY:		all clean fclean re