#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incl/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# define FT_CHAR 1
# define FT_STRING 2
# define FT_TAB 9
# define FT_SPACE 32
# define FT_SINGLE_QUOTE 39
# define FT_DOUBLE_QUOTE 34
# define FT_DOLLAR_SIGN 36
# define FT_HASHTAG	35
# define FT_GREATER 62
# define FT_LESSER 60
# define FT_QUESTION_MARK 63 //check in future
# define FT_MINUS 45
# define FT_EQUAL 61
# define FT_PIPE 124
# define FT_WILDCARD 42 	//talk about this in the future - bonus
# define FT_L_PAR 40		//talk about this in the future - bonus
# define FT_R_PAR 41		//talk about this in the future - bonus
# define FT_AMPERSAND 38 	//talk about this in the future - bonus
# define FT_TILDE 126		//futuristic stuff, i dont know
# define FT_EXCL_MARK 33	//futuristic stuff, i dont know

typedef struct s_word
{
	void	*address;
	int		type;
}			t_word;

void	ft_signal_setup(void);
int		lexor(t_list **list, char *args);
int		parser(void);
// void	executor(t_shell *shell);

#endif